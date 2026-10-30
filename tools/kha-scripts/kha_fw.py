#!/usr/bin/env python3

import sys
from optparse import OptionParser
from intelhex import IntelHex
from os import access, R_OK
from os.path import isfile
import os
import re
import socket
import threading
import time
import zlib
from time import sleep

PAGE_SIZE = 512
PAGE_START = 32
PAGE_END = 128

PART_SIZE = 64

# app CRC as the node computes it at every boot (kha_stack_crc32_flash_and_store): CRC-32 over
# 0x4000..0xFFFE, without the final XOR
APP_START = 0x4000
APP_END = 0xFFFF

UDP_IP = os.environ.get("KHA_GATEWAY", "192.168.1.1")
UDP_PORT = 5005

# pauses in seconds: fast (default, waits for the nodes' UP messages, only used when the nodes answered
# the ident before) and slow (the original fixed pauses, no replies needed)
TIMING = {
  "fast": {"part": 0.12, "page": 0.2},
  "slow": {"part": 0.4, "page": 0.4},
}
BOOT_UP_TIMEOUT = 5 # reboot -> bootloader UP
APP_UP_TIMEOUT = 15 # reboot -> bootloader UP -> bootloader timeout (~7 s) -> app UP
LATE_UP = 0.5 # after the last expected UP, wait this long for UPs of nodes that missed the ident

CMD_IDENT_RESPONSE = 0xE1
CMD_UP = 0xE2

# gateway output, human: "KS 00 RX L19 FB1 TE1 (U) CE1 [IDENT RES]    <A042F201 ... 489DC5B9>"
RE_HUMAN = re.compile(r"RX L[0-9A-F]{2} F([0-9A-F]{2}) T[0-9A-F]{2} \(.\) C(E[12]) .*<([0-9A-F ]+)>")
# gateway output, proto: "KS 40 <len><from><to><cmd><payload><crc>"
RE_PROTO = re.compile(r"KS 40 ([0-9A-F]+)")


def app_crc(ih):
  data = bytes(ih[a] for a in range(APP_START, APP_END))
  return zlib.crc32(data) ^ 0xFFFFFFFF


class Node:
  """Ident response / UP payload: type, rev, group, mode (1 = app), versions and CRCs"""
  def __init__(self, p):
    self.type, self.rev, self.group, self.app = p[0], p[1], p[2], p[3] != 0
    self.app_version = int.from_bytes(p[12:16], "big")
    self.app_crc = int.from_bytes(p[16:20], "big")


def parse(line):
  """(cmd, from, Node) for ident responses and UP messages, else None"""
  m = RE_HUMAN.search(line)
  if m:
    cmd, addr, p = int(m.group(2), 16), int(m.group(1), 16), bytes.fromhex(m.group(3).replace(" ", ""))
  else:
    m = RE_PROTO.search(line)
    if not m or len(m.group(1)) % 2:
      return None
    b = bytes.fromhex(m.group(1))
    if len(b) < 24:
      return None
    cmd, addr, p = b[3], b[1], b[4:24]
  if cmd not in (CMD_IDENT_RESPONSE, CMD_UP) or len(p) != 20:
    return None
  return cmd, addr, Node(p)


class Bus:
  """Sends to the bridge and collects the ident responses and UP messages it sends back"""
  def __init__(self):
    self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM) # UDP
    self.sock.bind(("", 0)) # the bridge sends the gateway's lines back to this port
    self.lock = threading.Lock()
    self.seen = [] # (time, cmd, addr, Node)
    threading.Thread(target=self.receive, daemon=True).start()

  def send(self, msg):
    self.sock.sendto(bytes(msg + "\n", "ascii"), (UDP_IP, UDP_PORT))

  def receive(self):
    while True:
      try:
        data, _ = self.sock.recvfrom(4096)
      except OSError:
        sleep(0.1)
        continue
      for line in data.decode("utf-8", "replace").splitlines():
        r = parse(line)
        if r:
          with self.lock:
            self.seen.append((time.time(), *r))

  def messages(self, cmd, since):
    """{addr: Node} of the latest <cmd> messages since <since>"""
    with self.lock:
      return {a: n for t, c, a, n in self.seen if c == cmd and t >= since}

  def ident(self, to, wait):
    since = time.time()
    self.send("{}E0".format(to))
    sleep(wait)
    return self.messages(CMD_IDENT_RESPONSE, since)

  def wait_up(self, since, nodes, app, timeout, matches):
    """Wait for UP messages (bootloader or app) of all <nodes>; matching nodes that weren't expected are
    added. Returns {addr: Node}"""
    end = time.time() + timeout
    done_at = None
    while time.time() < end:
      ups = {a: n for a, n in self.messages(CMD_UP, since).items() if n.app == app}
      for a, n in ups.items():
        if a not in nodes and matches(a, n):
          nodes.append(a)
          print("  {:02X}: not in the ident before, flashed anyway".format(a))
      if all(a in ups for a in nodes):
        if done_at is None:
          done_at = time.time()
        if time.time() - done_at >= LATE_UP:
          break
      sleep(0.05)
    return {a: n for a, n in self.messages(CMD_UP, since).items() if n.app == app and a in nodes}


def show(addr, node):
  if node is None:
    return "{:02X}: NO REPLY".format(addr)
  return "{:02X}: app {:08X} crc {:08X}{}".format(addr, node.app_version, node.app_crc, "" if node.app else " (bootloader)")


def go():
  usage = "usage: %prog [--slow] <device address 01-FF> <board type 01-FE> <board rev A-Z> <hex file>"
  parser = OptionParser(usage)
  parser.add_option("--slow", action="store_true", default=False,
                    help="original fixed pauses (used anyway when the nodes don't answer the ident)")
  (options, args) = parser.parse_args()
  if len(args) != 4:
    parser.error("incorrect number of arguments")

  device_addr = args[0].upper()
  board_type = args[1].upper()
  board_rev = args[2].upper()
  fn = args[3]

  if not isfile(fn) or not access(fn, R_OK):
    print('File doesnt exist or isnt readable.')
    return 1

  ih = IntelHex(fn)
  crc = app_crc(ih)

  target = int(device_addr, 16)

  def matches(addr, node):
    """Does the reboot / flash command for <device_addr> <type> <rev> reach this node?"""
    if node.type != int(board_type, 16) or node.rev != int(board_rev, 16):
      return False
    return target == 0xFF or (target >= 0xF0 and node.group == target) or addr == target

  print("--- START {} (app crc {:08X}) ---\n".format(os.path.basename(fn), crc))

  bus = Bus()
  bus.send("")
  sleep(1)

  # ident before: which nodes will be flashed (FFE0 when the target is a group or broadcast)
  found = bus.ident(device_addr if target < 0xF0 else "FF", 1.5 if target < 0xF0 else 4)
  nodes = sorted(a for a, n in found.items() if matches(a, n))
  if nodes:
    print("before:")
    for a in nodes:
      print("  " + show(a, found[a]))
  else:
    print("before: no ident replies from matching nodes, the result can't be checked")

  fast = nodes and not options.slow
  if options.slow:
    print("slow timing")
  elif fast:
    print("fast timing")
  else:
    print("fast timing needs ident replies, using slow timing")
  timing = TIMING["fast" if fast else "slow"]
  print()

  started = time.time()

  print("TX: F0 KHA_CMD_MANAGEMENT_TX_DISABLE")
  bus.send("FFF0")
  sleep(2)

  print("TX: FF KHA_CMD_MANAGEMENT_REBOOT")
  since = time.time()
  bus.send("{}FF{}{}".format(device_addr, board_type, board_rev))
  if fast:
    # every node sends a bootloader UP after the reboot, then BOOT STAY keeps it in the bootloader
    booted = bus.wait_up(since, nodes, False, BOOT_UP_TIMEOUT, matches)
    for i in range(0, 2):
      print("TX: FD KHA_CMD_MANAGEMENT_BOOT_NOT_EXIT")
      bus.send("{}FD{}{}".format(device_addr, board_type, board_rev))
      sleep(0.3)
  else:
    sleep(2)
    for i in range(0, 6):
      # stay
      print("TX: FD KHA_CMD_MANAGEMENT_BOOT_NOT_EXIT")
      bus.send("{}FD{}{}".format(device_addr, board_type, board_rev))
      sleep(1)
    booted = {a: n for a, n in bus.messages(CMD_UP, since).items() if not n.app}
  for a in nodes:
    if a not in booted:
      print("  {:02X}: no bootloader UP, didn't reboot?".format(a))

  print("TX: FC KHA_CMD_MANAGEMENT_BOOT_WIPE_FLASH")
  bus.send("{}FC{}{}".format(device_addr, board_type, board_rev))
  sleep(2)

  for page in range(PAGE_START, PAGE_END):

    print("Page: {} / {}".format(page, PAGE_END))
    check_all_FF = 1
    for p in range(0, PAGE_SIZE):
      if (ih[page * PAGE_SIZE + p] != 0xFF):
        check_all_FF = 0
        break;
    if check_all_FF:
      continue

    for part in range(0, (int)(PAGE_SIZE / PART_SIZE)):
      addr = (page * PAGE_SIZE) + (part * PART_SIZE)
      msg = "{}FA{}{}{}".format(device_addr, board_type, board_rev, "%0.2X" % part)
      for pos in range(0, PART_SIZE):
        msg = msg + ("%0.2X" % ih[addr + pos])
      bus.send(msg)
      sleep(timing["part"])

    bus.send("{}F9{}{}{}".format(device_addr, board_type, board_rev, "%0.2X" % page))
    sleep(timing["page"])

  print("TX: FF KHA_CMD_MANAGEMENT_REBOOT")
  since = time.time()
  bus.send("{}FF{}{}".format(device_addr, board_type, board_rev))
  if fast:
    # bootloader UP, the bootloader times out, app UP with the CRC of the new flash content
    up = bus.wait_up(since, nodes, True, APP_UP_TIMEOUT, matches)
  else:
    sleep(8)
    up = {a: n for a, n in bus.messages(CMD_UP, since).items() if n.app}

  print("TX: F1 KHA_CMD_MANAGEMENT_TX_ENABLE")
  bus.send("FFF1")
  sleep(1)

  print("--- END {} ({:.0f} s) ---\n".format(os.path.basename(fn), time.time() - started))

  if not nodes:
    return 0

  # after: every node must have rebooted and run the app with the CRC of the hex file; nodes whose app UP
  # got lost are asked by ident
  ok = True
  print("after:")
  for a in nodes:
    node = up.get(a)
    source = "UP"
    for attempt in range(0, 3):
      if node:
        break
      node = bus.ident("%0.2X" % a, 1.5).get(a)
      source = "ident"
    good = a in booted and node is not None and node.app and node.app_crc == crc
    ok = ok and good
    note = "" if a in booted else ", no bootloader UP"
    print("  {} {} ({}{})".format(show(a, node), "OK" if good else "FAILED", source, note))
  if not ok:
    print("\nFAILED: flash again, with --slow if it happens again")
  return 0 if ok else 1


sys.exit(go())
