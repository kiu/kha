#!/usr/bin/env python3
"""Flash bootloader + app onto one node via UPDI (Atmel-ICE) and restore its registers.

  python tools/kha-scripts/kha_updi.py                    # the dist/ builds in the repo
  python tools/kha-scripts/kha_updi.py --firmware <dir>   # hex files from a directory instead

One node per run, plug the Atmel-ICE into the node first. Steps:
  1. short UPDI session: lock state, USERROW if unlocked; the node reboots afterwards and its UP on the
     bus (seen through --local and, if given, --remote) identifies it even when it's locked
  2. chip erase (also unlocks), read USERROW (type, rev, address, group) and the chip serial
  3. write bootloader + app for that board type, the bootloader's fuses and the EEPROM image (registers
     from inventory/<address>.json made by kha_backup.py, 0x42 marker at 0xFF), each verified
  4. let it boot, then read back the boot / app version + CRC the node wrote into its EEPROM
  5. record serial and date in inventory/<address>.json and INVENTORY.local.md
It only asks when something doesn't fit (unknown node, mismatch, already flashed).
"""
import argparse
import datetime
import os
import sys
import time
import zlib

from intelhex import IntelHex
from pymcuprog.backend import Backend, SessionConfig
from pymcuprog.pymcuprog_errors import PymcuprogDeviceLockedError
from pymcuprog.toolconnection import ToolUsbHidConnection

import kha_backup
from kha_backup import Bridge, TYPES, add_bridge_args, bridge_address, load_node, save_node, write_inventory

DEVICE = "avr64dd32"

# MPLAB X project per board type; its build is <project>/dist/default/production/<name>.production.hex
BOOT = "kha-boot.X"
APPS = {
  0x02: "kha-nodes/kha-led-ikea/kha-led-ikea-node/kha-led-ikea-node.X",
  0x03: "kha-nodes/kha-gateway-usb/kha-gateway-usb.X",
  0x04: "kha-nodes/kha-relay-2x3/kha-relay-2x3-node/kha-relay-2x3-node.X",
  0x05: "kha-nodes/kha-main/kha-main.X",
  0x07: "kha-nodes/kha-led-strip/kha-led-strip.X",
  0xA0: "kha-bgt-subrack/kha-bgt-audio/kha-bgt-audio.X",
  0xA1: "kha-bgt-subrack/kha-bgt-power/kha-bgt-power.X",
  0xA2: "kha-bgt-subrack/kha-bgt-dark/kha-bgt-dark.X",
  0xA3: "kha-bgt-subrack/kha-bgt-guru/kha-bgt-guru.X",
  0xA4: "kha-bgt-subrack/kha-bgt-hsi/kha-bgt-hsi.X",
  0xA5: "kha-bgt-subrack/kha-bgt-kaox/kha-bgt-kaox.X",
  0xA6: "kha-bgt-subrack/kha-bgt-main/kha-bgt-main.X",
  0xA7: "kha-bgt-subrack/kha-bgt-preset/kha-bgt-preset.X",
  0xA8: "kha-bgt-subrack/kha-bgt-rainbow/kha-bgt-rainbow.X",
}
# REGISTER_SIZE, REGISTER_PRESET_WIDTH of each app (main.c): the new stack has register_size +
# (width + 1) * 16 registers (presets 0..15)
REGISTERS = {
  0x02: (6, 0), 0x03: (2, 0), 0x04: (12, 0), 0x05: (0, 0), 0x07: (4, 0), 0xA0: (3, 1), 0xA1: (8, 4),
  0xA2: (0, 1), 0xA3: (2, 0), 0xA4: (1, 3), 0xA5: (1, 1), 0xA6: (1, 0), 0xA7: (4, 0), 0xA8: (1, 3),
}

FLASH_SIZE = 0x10000
PAGE_SIZE = 0x200
APP_START = 0x4000
EEPROM_MAGIC_OFFSET = 0xFF  # KHA_STACK_EEPROM_MAGIC_OFFSET
EEPROM_MAGIC_OK = 0x42
EEPROM_IDENT = 0xEF  # boot version, boot CRC, app version, app CRC (4 bytes each) written by the node
HEX_FUSES = 0x820000  # where avr-gcc puts the fuses in a hex file
FUSES_WRITE = (0, 1, 2, 5, 6, 7, 8)  # WDTCFG BODCFG OSCCFG - - SYSCFG0 SYSCFG1 CODESIZE BOOTSIZE
BOOT_WAIT = 10  # bootloader countdown (4 s, old 6 s) + app init until the node wrote its EEPROM


def ask(question):
  """Yes only on an explicit y; without a terminal (stdin closed) every question is a no"""
  try:
    return input(question + " [y/N] ").strip().lower() == "y"
  except EOFError:
    print("(no answer: no)")
    return False


def stop(text):
  print("\nSTOP: " + text)
  sys.exit(1)


class Updi:
  """Atmel-ICE sessions; every session holds the node in reset, it boots when the session ends"""
  def __init__(self):
    self.connect()

  def connect(self):
    self.backend = Backend()
    self.backend.connect_to_tool(ToolUsbHidConnection(tool_name="atmelice"))

  def start(self, unlock=False):
    config = SessionConfig(DEVICE)
    config.special_options = {"chip-erase-locked-device": True} if unlock else {}
    self.backend.start_session(config)

  def end(self):
    self.backend.end_session()

  def chip_erase(self, locked):
    """Chip erase, also unlocks. The unlock option stays set in the Atmel-ICE for the rest of the
    connection (every following session would erase again) and the chip doesn't answer in the same
    session after the erase: so a fresh connection afterwards."""
    self.start(unlock=locked)
    self.backend.erase()
    try:
      self.end()
    except Exception:
      pass
    try:
      self.backend.disconnect_from_tool()
    except Exception:
      pass
    self.connect()

  def read(self, memory, offset=0, length=0):
    return bytes(self.backend.read_memory(memory, offset, length)[0].data)

  def write(self, memory, data, offset=0):
    self.backend.write_memory(bytearray(data), memory, offset)
    if not self.backend.verify_memory(bytearray(data), memory, offset):
      stop("verify of {} at {:#x} failed".format(memory, offset))


def hex_file(project, firmware):
  """The project's dist/ build, or the file of the same name in the --firmware directory"""
  name = os.path.basename(project) + ".production.hex"
  if firmware:
    path = os.path.join(firmware, name)
  else:
    path = os.path.join(kha_backup.ROOT, project, "dist", "default", "production", name)
  if not os.path.isfile(path):
    stop("missing " + path)
  return path


def flash_image(boot_file, app_file):
  """Bootloader + app, flash addresses only (fuses / lock bits in the hex files are left out)"""
  image = IntelHex()
  image.padding = 0xFF  # erased flash
  for path in (boot_file, app_file):
    src = IntelHex(path)
    for start, end in src.segments():
      if end <= FLASH_SIZE:
        for a in range(start, end):
          image[a] = src[a]
  return image


def app_crc(image):
  """What the node computes at boot: CRC-32 over 0x4000..0xFFFF without the final XOR"""
  data = bytes(image.tobinarray(start=APP_START, end=FLASH_SIZE - 1))  # gaps = padding 0xFF
  return zlib.crc32(data) ^ 0xFFFFFFFF


def pages(image):
  """(offset, data) per flash segment, padded to whole pages"""
  for start, end in image.segments():
    start, end = start - start % PAGE_SIZE, end + (-end) % PAGE_SIZE
    yield start, bytes(image.tobinarray(start=start, end=end - 1))


def eeprom_image(node, board_type):
  regs = bytes.fromhex(node["registers"])
  size, width = REGISTERS[board_type]
  expected = size + (width + 1) * 16
  if len(regs) > expected:
    stop("{} has {} registers, the firmware only {}".format(node["address"], len(regs), expected))
  regs += bytes(expected - len(regs))  # a missing preset slot starts disabled
  image = bytearray(b"\xff" * 256)
  image[:len(regs)] = regs
  image[EEPROM_MAGIC_OFFSET] = EEPROM_MAGIC_OK
  return image


def bus_ups(bridges, since, timeout):
  """{address: UP payload} seen on any bridge"""
  end = time.time() + timeout
  found = {}
  while time.time() < end:
    for bridge in bridges:
      with bridge.lock:
        for t, f, _, c, p in bridge.seen:
          if t >= since and c == 0xE2 and len(p) == 20:
            found[f] = p
    if found and time.time() > since + 2:
      break
    time.sleep(0.1)
  return found


def describe(addr, board_type, rev, group):
  return "{:02X} {} (type {:02X} rev {:02X}) group {:02X}".format(
    addr, TYPES.get(board_type, "unknown type"), board_type, rev, group)


def main():
  parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
  parser.add_argument("--firmware", help="directory with the hex files (same names as the dist/ builds) "
                      "instead of the repo's dist/ builds")
  parser.add_argument("--force", action="store_true", help="flash even if the inventory says it's done")
  parser.add_argument("--no-bus", action="store_true", help="don't listen on the bridges")
  add_bridge_args(parser)
  parser.add_argument("--probe", action="store_true", help="only identify the node (step 1), write nothing")
  parser.add_argument("--location", help="location for the inventory (else asked, Enter skips)")
  parser.add_argument("--expect", help="address of the node you're plugged into, when the probe can't see it "
                      "(e.g. a locked node whose UP no gateway can read); checked against USERROW")
  args = parser.parse_args()

  bridges = []
  if not args.no_bus:
    bridges = [Bridge(bridge_address(a)) for a in (args.local, args.remote) if a]
  for bridge in bridges:
    bridge.send("")  # register as reply target

  updi = Updi()

  # 1. probe: lock state and, if readable, USERROW; the node reboots when the session ends
  print("--- probe")
  locked = False
  userrow = None
  try:
    updi.start()
    print("target voltage ok, device id {}".format(updi.backend.read_device_id()[::-1].hex().upper()))
    userrow = updi.read("user_row", 0, 4)
  except PymcuprogDeviceLockedError:
    locked = True
  finally:
    try:
      updi.end()
    except Exception:
      pass
  since = time.time()
  print("locked" if locked else "unlocked, USERROW " + userrow.hex().upper())

  ups = bus_ups(bridges, since, 4) if bridges else {}
  for a, p in sorted(ups.items()):
    print("UP on the bus: " + describe(a, p[0], p[1], p[2]) + (" (app)" if p[3] else " (bootloader)"))

  if args.probe:
    return

  expected = None
  if userrow:
    expected = userrow[2]
  elif len(ups) == 1:
    expected = list(ups)[0]
  elif args.expect:
    expected = int(args.expect, 16)
    print("not seen on the bus, expecting {:02X} (--expect)".format(expected))
  if expected is None:
    if not ask("node not identified before the erase (no or several UPs). Erase anyway?"):
      sys.exit(1)
  else:
    node = load_node("%02X" % expected)
    if node is None:
      stop("{:02X} has no register backup in inventory/ (run kha_backup.py while it's on the bus)".format(expected))
    if "flashed_at" in node.get("updi", {}) and not args.force:
      if not ask("{:02X} was already flashed ({}). Again?".format(expected, node["updi"]["flashed_at"])):
        sys.exit(1)

  # 2. erase, identify
  print("--- erase")
  updi.chip_erase(locked)
  updi.start()
  userrow = updi.read("user_row", 0, 32)
  serial = updi.read("signatures", 0x10, 16).hex().upper()
  fuses_before = updi.read("fuses")
  board_type, rev, addr, group = userrow[0], userrow[1], userrow[2], userrow[3]
  print("USERROW: " + describe(addr, board_type, rev, group) + ", serial " + serial)
  if expected is not None and addr != expected:
    if not ask("USERROW says {:02X}, the probe said {:02X}. Flash as {:02X}?".format(addr, expected, addr)):
      stop("node is erased, run again")
  node = load_node("%02X" % addr)
  if node is None:
    stop("{:02X} has no register backup in inventory/ (node is erased)".format(addr))
  if int(node["type"], 16) != board_type or int(node["rev"], 16) != rev:
    if not ask("inventory says type {} rev {}, USERROW {:02X} {:02X}. Continue?".format(
        node["type"], node["rev"], board_type, rev)):
      stop("node is erased, run again")
  if board_type not in APPS:
    stop("no app for type {:02X}".format(board_type))

  boot_file = hex_file(BOOT, args.firmware)
  app_file = hex_file(APPS[board_type], args.firmware)
  image = flash_image(boot_file, app_file)
  crc = app_crc(image)
  fuses = bytes(IntelHex(boot_file)[HEX_FUSES + i] for i in range(9))
  eeprom = eeprom_image(node, board_type)

  # 3. write
  print("--- write {} + {} (app crc {:08X})".format(os.path.basename(boot_file), os.path.basename(app_file), crc))
  for offset, data in pages(image):
    updi.write("flash", data, offset)
    print("flash {:#06x}..{:#06x} ok".format(offset, offset + len(data) - 1))
  for i in FUSES_WRITE:
    if fuses_before[i] != fuses[i]:
      updi.write("fuses", bytes([fuses[i]]), i)
      print("fuse {} {:02X} -> {:02X} ok".format(i, fuses_before[i], fuses[i]))
  updi.write("eeprom", eeprom)
  print("eeprom ok ({} registers + marker)".format(len(bytes.fromhex(node["registers"]))))
  since = time.time()
  updi.end()

  # 4. boot, check what the node wrote
  print("--- boot ({} s)".format(BOOT_WAIT))
  time.sleep(BOOT_WAIT)
  updi.start()
  ident = updi.read("eeprom", EEPROM_IDENT, 16)
  updi.end()
  node_crc = int.from_bytes(ident[12:16], "big")
  print("node wrote: boot {} crc {}, app {} crc {:08X}".format(
    ident[0:4].hex().upper(), ident[4:8].hex().upper(), ident[8:12].hex().upper(), node_crc))
  for a, p in sorted(bus_ups(bridges, since, 1).items() if bridges else []):
    if a == addr:
      print("UP on the bus: app crc {}".format(p[16:20].hex().upper()))
  if node_crc != crc:
    stop("app CRC {:08X}, expected {:08X}: the app didn't run".format(node_crc, crc))

  # 5. record
  node["updi"] = {
    "serial": serial, "flashed_at": datetime.datetime.now().isoformat(timespec="minutes"),
    "firmware": args.firmware or "dist", "boot": os.path.basename(boot_file),
    "app": os.path.basename(app_file), "app_crc": "%08X" % crc, "locked_before": locked,
    "fuses_before": fuses_before.hex().upper(),
  }
  location = args.location
  if location is None:
    try:
      location = input("location (Enter to skip): ").strip()
    except EOFError:
      location = ""
  if location:
    node["location"] = location
  save_node(node)
  write_inventory()
  print("\nOK: {:02X} flashed, unplug the Atmel-ICE".format(addr))


if __name__ == "__main__":
  main()
