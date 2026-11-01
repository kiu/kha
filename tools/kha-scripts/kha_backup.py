#!/usr/bin/env python3
"""Back up every node's registers over the bus (UPDI can't read the EEPROM of a locked node, and a chip
erase wipes it).

  python tools/kha-scripts/kha_backup.py [--local HOST[:PORT]] [--remote HOST[:PORT]] [--local-gateway XX]

Asks all nodes for their ident (FFE0), finds each node's register length by reading single bytes, reads
all registers and writes one JSON file per node into inventory/ plus an overview in INVENTORY.local.md (both
gitignored). Talks through the local bridge (--local, default 127.0.0.1:5005 = kha_serial_log.py). A node
can't be read through itself, so the gateway behind the local bridge is read through a second bridge
(--remote, e.g. kha_listen on another machine); without --remote it is skipped. Its address is taken
from its own TX lines, or --local-gateway.

The node's RAM copy (what it runs with right now, incl. switch states) goes into registers_ram; what
kha_updi.py restores (registers) comes from the REGISTER SETUP sheet in kha-protocol.ods. Differences
are listed.
"""
import argparse
import datetime
import json
import os
import re
import socket
import threading
import time
import xml.etree.ElementTree as ET
import zipfile

BRIDGE_PORT = 5005  # kha_serial_log.py and kha_listen.py

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.normpath(os.path.join(HERE, "..", ".."))
OUT_DIR = os.path.join(ROOT, "inventory")
SETUP_ODS = os.path.join(ROOT, "kha-protocol.ods")  # sheet REGISTER SETUP: the intended register values

REGISTER_MAX = 0xFF - 17  # KHA_STACK_EEPROM_REGISTER_LEN
CHUNK = 0x40  # below KHA_MSG_LEN_OPT_MAX - 1
TIMEOUT = 1.5

TYPES = {
  0x02: "led-ikea-node", 0x03: "gateway-usb", 0x04: "relay-2x3", 0x05: "main", 0x06: "remote",
  0x07: "led-strip", 0xA0: "bgt-audio", 0xA1: "bgt-power", 0xA2: "bgt-dark", 0xA3: "bgt-guru",
  0xA4: "bgt-hsi", 0xA5: "bgt-kaox", 0xA6: "bgt-main", 0xA7: "bgt-preset", 0xA8: "bgt-rainbow",
}

# human: "KS 00 RX L19 FB1 TE1 (U) CE1 [IDENT RES]    <A042F201 ...>"
RE_LINE = re.compile(r"RX L[0-9A-F]{2} F([0-9A-F]{2}) T([0-9A-F]{2}) \(.\) C([0-9A-F]{2}) .*<([0-9A-F ]*)>")
# proto: "KS 40 <len><from><to><cmd><payload><crc>" (received frames only)
RE_PROTO = re.compile(r"KS 40 ([0-9A-F]+)")
# the gateway's own frames: "KS 00 TX L05 FE1 TFF (B) CE0 [IDENT REQ]    <>" or proto "KS 50 05E1FFE0.."
RE_TX = re.compile(r"TX L[0-9A-F]{2} F([0-9A-F]{2}) T|KS 50 [0-9A-F]{2}([0-9A-F]{2})")


def bridge_address(text):
  """"host" or "host:port" -> (host, port)"""
  host, _, port = text.partition(":")
  return host, int(port) if port else BRIDGE_PORT


def add_bridge_args(parser):
  parser.add_argument("--local", default=os.environ.get("KHA_GATEWAY_LOCAL", "127.0.0.1"),
                      help="local bridge HOST[:PORT] (default 127.0.0.1:5005, env KHA_GATEWAY_LOCAL)")
  parser.add_argument("--remote", default=os.environ.get("KHA_GATEWAY_REMOTE"),
                      help="second bridge HOST[:PORT] to reach the local gateway itself (env KHA_GATEWAY_REMOTE)")


class Bridge:
  """One UDP bridge: sends commands, collects the gateway's RX lines it sends back"""
  def __init__(self, addr):
    self.addr = addr
    self.gateway = None  # address of the gateway behind this bridge, from its own TX lines
    self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    self.sock.bind(("", 0))
    self.lock = threading.Lock()
    self.seen = []  # (time, from, to, cmd, payload)
    threading.Thread(target=self.receive, daemon=True).start()

  def receive(self):
    while True:
      try:
        data, _ = self.sock.recvfrom(4096)
      except OSError:
        time.sleep(0.1)
        continue
      for line in data.decode("utf-8", "replace").splitlines():
        m = RE_TX.search(line)
        if m:
          self.gateway = int(m.group(1) or m.group(2), 16)
          continue
        m = RE_LINE.search(line)
        if m:
          frame = (int(m.group(1), 16), int(m.group(2), 16), int(m.group(3), 16),
                   bytes.fromhex(m.group(4).replace(" ", "")))
        else:
          m = RE_PROTO.search(line)
          if not m or len(m.group(1)) % 2:
            continue
          b = bytes.fromhex(m.group(1))
          if len(b) < 5 or b[0] != len(b):
            continue
          frame = (b[1], b[2], b[3], b[4:-1])
        with self.lock:
          self.seen.append((time.time(),) + frame)

  def send(self, msg):
    self.sock.sendto((msg + "\n").encode("ascii"), self.addr)

  def wait(self, since, cmd, sender, accept=lambda p: True, timeout=TIMEOUT):
    end = time.time() + timeout
    while time.time() < end:
      with self.lock:
        for t, f, _, c, p in self.seen:
          if t >= since and c == cmd and f == sender and accept(p):
            return p
      time.sleep(0.02)
    return None

  def read(self, addr, reg, length):
    """Register bytes, b"" if the node rejected the range, None without an answer"""
    # a reply belongs to this request if it starts at reg with the right length; an empty reply is the
    # node's error answer (late replies to earlier requests are ignored)
    accept = lambda p: len(p) == 0 or (p[0] == reg and len(p) == length + 1)
    for attempt in range(3):
      since = time.time()
      self.send("{:02X}D0{:02X}{:02X}".format(addr, reg, length))
      p = self.wait(since, 0xD1, addr, accept)
      if p is not None:
        return p[1:]
    return None


def register_len(bridge, addr):
  """Highest readable register + 1, found with single-byte reads"""
  if bridge.read(addr, 0, 1) in (b"", None):
    return 0
  lo, hi = 1, REGISTER_MAX  # lo is readable count, hi is unreadable count
  while hi - lo > 1:
    mid = (lo + hi) // 2
    r = bridge.read(addr, mid - 1, 1)
    if r is None:
      raise RuntimeError("{:02X}: no answer".format(addr))
    if r:
      lo = mid
    else:
      hi = mid
  return lo


def main():
  parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
  add_bridge_args(parser)
  parser.add_argument("--local-gateway", help="address of the gateway behind the local bridge "
                      "(default: from its own TX lines)")
  args = parser.parse_args()

  local = Bridge(bridge_address(args.local))
  remote = Bridge(bridge_address(args.remote)) if args.remote else None
  for bridge in (local, remote):
    if bridge:
      bridge.send("")  # register as reply target
  time.sleep(1)

  since = time.time()
  local.send("FFE0")
  time.sleep(4)
  with local.lock:
    idents = {f: p for t, f, _, c, p in local.seen if t >= since and c == 0xE1 and len(p) == 20}
  print("ident from {} nodes: {}".format(len(idents), " ".join("%02X" % a for a in sorted(idents))))

  local_gateway = int(args.local_gateway, 16) if args.local_gateway else local.gateway
  extra = []
  if local_gateway is None:
    print("local gateway's address unknown (no TX line seen, use --local-gateway): not backed up")
  elif remote is None:
    print("{:02X} (local gateway) not backed up: it can't be read through itself, use --remote".format(local_gateway))
  else:
    extra = [local_gateway]

  os.makedirs(OUT_DIR, exist_ok=True)
  nodes = []
  for addr in sorted(idents) + extra:
    if addr == local_gateway:
      bridge = remote
      since = time.time()
      remote.send("{:02X}E0".format(addr))
      p = remote.wait(since, 0xE1, addr, timeout=3)
      if p is None or len(p) != 20:
        print("{:02X}: no ident through {}".format(addr, remote.addr[0]))
        continue
      ident = p
    else:
      bridge, ident = local, idents[addr]
    n = register_len(bridge, addr)
    regs = b""
    for start in range(0, n, CHUNK):
      chunk = bridge.read(addr, start, min(CHUNK, n - start))
      if not chunk:
        raise RuntimeError("{:02X}: read {:02X}+{:02X} failed".format(addr, start, min(CHUNK, n - start)))
      regs += chunk
    node = {
      "address": "%02X" % addr,
      "type": "%02X" % ident[0], "type_name": TYPES.get(ident[0], "?"), "rev": "%02X" % ident[1],
      "group": "%02X" % ident[2], "mode": "app" if ident[3] else "bootloader",
      "boot_version": ident[4:8].hex().upper(), "boot_crc": ident[8:12].hex().upper(),
      "app_version": ident[12:16].hex().upper(), "app_crc": ident[16:20].hex().upper(),
      "register_len": n, "registers_ram": regs.hex().upper(),
      "read_at": datetime.datetime.now().isoformat(timespec="seconds"),
    }
    nodes.append(node)
    print("{address}: {type_name:14} group {group} app {app_version} regs {register_len:3}".format(**node))

  # what gets restored: the setup from kha-protocol.ods (the EEPROM defaults), not the RAM values (which
  # include switch states like power buttons that are on right now)
  setup = setup_registers(nodes)
  for node in nodes:
    ram = bytes.fromhex(node["registers_ram"])
    regs = setup.get(node["address"], bytes(len(ram)))  # not in the sheet: wipe state, all 00
    node["registers"] = regs.hex().upper()
    node["registers_source"] = "kha-protocol.ods REGISTER SETUP (wipe + setup)"
    diff = ["{:02X}: {:02X} -> {:02X}".format(i, ram[i], regs[i]) for i in range(len(ram)) if ram[i] != regs[i]]
    if diff:
      print("{}: RAM differs from the sheet, restoring the sheet: {}".format(node["address"], ", ".join(diff)))
    old = load_node(node["address"])
    for key in ("location", "position", "updi"):  # written by hand / by kha_updi.py, survive a new backup
      if old and key in old:
        node[key] = old[key]
    save_node(node)

  write_inventory()


def ods_rows(path, sheet):
  """Rows of one sheet of an .ods file as lists of cell texts"""
  ns = {"table": "urn:oasis:names:tc:opendocument:xmlns:table:1.0",
        "text": "urn:oasis:names:tc:opendocument:xmlns:text:1.0"}
  t = "{%s}" % ns["table"]
  root = ET.fromstring(zipfile.ZipFile(path).read("content.xml"))
  for table in root.iter(t + "table"):
    if table.get(t + "name") != sheet:
      continue
    for row in table.iter(t + "table-row"):
      cells = []
      for cell in row:
        if cell.tag in (t + "table-cell", t + "covered-table-cell"):
          text = " ".join("".join(p.itertext()) for p in cell.iter("{%s}p" % ns["text"]))
          cells += [text] * min(int(cell.get(t + "number-columns-repeated", "1")), 50)
      yield cells
  return


def setup_registers(nodes):
  """{address: register bytes} after the commands in the REGISTER SETUP sheet (wipe = all 00, D5 writes;
  group addresses apply to all backed-up nodes of that group)"""
  by_address = {n["address"]: n for n in nodes}
  groups = {}
  for n in nodes:
    groups.setdefault(n["group"], []).append(n["address"])
  regs = {}
  for row in ods_rows(SETUP_ODS, "REGISTER SETUP"):
    if len(row) < 2 or not row[0].lower().startswith("kha-"):
      continue
    commands = []
    for token in row[1].split():
      if re.fullmatch(r"[0-9A-F]{2}D[5EF][0-9A-F]*", token):
        commands.append(token)
      elif commands:
        commands[-1] += token  # a write split by a space
    for c in commands:
      to, cmd, data = c[:2], c[2:4], bytes.fromhex(c[4:])
      for a in (groups.get(to, []) if to >= "F0" else [to]):
        if a not in by_address:
          print("{}: in the setup sheet but not on the bus".format(a))
          continue
        if cmd == "DF" or a not in regs:
          regs[a] = bytearray(by_address[a]["register_len"])
        if cmd == "D5":
          regs[a][data[0]:data[0] + len(data) - 1] = data[1:]
  return {a: bytes(r) for a, r in regs.items()}


def node_path(address):
  return os.path.join(OUT_DIR, address + ".json")


def load_node(address):
  path = node_path(address)
  if not os.path.exists(path):
    return None
  with open(path) as f:
    return json.load(f)


def save_node(node):
  os.makedirs(OUT_DIR, exist_ok=True)
  with open(node_path(node["address"]), "w") as f:
    json.dump(node, f, indent=2)


def write_inventory():
  """INVENTORY.local.md from all inventory/*.json (the JSON files are the source: edit locations there)"""
  names = sorted(f for f in os.listdir(OUT_DIR) if re.fullmatch(r"[0-9A-F]{2}\.json", f))
  nodes = [load_node(f[:-5]) for f in names]
  nodes.sort(key=lambda n: (n.get("position", 999), n["address"]))
  lines = [
    "# kha – inventory", "",
    "Local, gitignored. Generated from `inventory/<address>.json` by `kha_backup.py` (register backup "
    "over the bus) and `kha_updi.py` (UPDI flash: serial, date). Edit locations and positions in the "
    "JSON files. Pos = order along the bus cable, from one end (C3) to the other (C6). Boot / App "
    "before = read over the bus at the backup.", "",
    "| Pos | Address | Type | Rev | Group | Boot before | App before | Registers | Location | Serial | UPDI "
    "| App CRC now |",
    "|---|---|---|---|---|---|---|---|---|---|---|---|",
  ]
  for n in nodes:
    updi = n.get("updi", {})
    lines.append("| {} | {} | {} ({}) | {} | {} | {} | {} | {} | {} | {} | {} | {} |".format(
      n.get("position", ""), n["address"], n["type_name"], n["type"],
      "{} ({})".format(chr(int(n["rev"], 16)), n["rev"]), n["group"],
      n["boot_version"], n["app_version"], n["register_len"], n.get("location", ""),
      updi.get("serial", ""), updi.get("flashed_at", ""), updi.get("app_crc", "")))
  with open(os.path.join(ROOT, "INVENTORY.local.md"), "w", encoding="utf-8") as f:
    f.write("\n".join(lines) + "\n")
  print("wrote INVENTORY.local.md ({} nodes)".format(len(nodes)))


if __name__ == "__main__":
  main()
