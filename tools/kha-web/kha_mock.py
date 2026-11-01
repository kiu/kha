#!/usr/bin/env python3
"""Mock data for the kha-web status page, in the shape the collector will export.

  python tools/kha-web/kha_mock.py              # writes tools/kha-web/webroot/data/mock.json (page: ?mock)
  python tools/kha-web/kha_mock.py --all-stale  # nobody answered for 40 min (guru / E0 silent)

Real node list (cable order), versions and CRCs; a few scenarios so every state shows up: one node
missing, one with errors and a recent reboot, one whose versions are still unknown, one with an old
bootloader, one that isn't in
the config (new address, unknown board type).
"""
import argparse
import datetime
import json
import os
import random

HERE = os.path.dirname(os.path.abspath(__file__))
OUT = os.path.join(HERE, "webroot", "data")

BOOT = ("6AE4E368", "B06CC2B5")
APPS = {  # board type: (name, app version, app CRC)
  0x02: ("led-ikea-node", "6AE4E925", "2765CD61"), 0x03: ("gateway-usb", "6AE60A5A", "9FFF521B"),
  0x04: ("relay-2x3-node", "6AE4E928", "90D5DFBA"), 0x05: ("main", "6AE603CA", "8F680272"),
  0x07: ("led-strip", "6AE5D15F", "239EC741"), 0xA0: ("bgt-audio", "6AE4E916", "824F650B"),
  0xA1: ("bgt-power", "6AE4E91E", "6543BC9A"), 0xA2: ("bgt-dark", "6AE4E918", "D35E4C91"),
  0xA3: ("bgt-guru", "6AE4E919", "AC190C41"), 0xA4: ("bgt-hsi", "6AE4E91A", "B820F5DE"),
  0xA5: ("bgt-kaox", "6AE4E91C", "7677A155"), 0xA6: ("bgt-main", "6AE602EE", "9C4809B2"),
  0xA7: ("bgt-preset", "6AE4E91F", "8EDC6E7A"), 0xA8: ("bgt-rainbow", "6AE4E921", "4337F577"),
}

SECTIONS = [
  {"id": "house", "label": "Living room"},
  {"id": "subrack", "label": "Subrack"},
  {"id": "machines", "label": "Gateways"},
  {"id": "bedroom", "label": "Bedroom"},
][::-1]

# cable order as walked from the C3 end: (address, type, rev, group, name, section); shown reversed, so
# the subrack reads like the real one (main left, guru right)
NODES = [
  ("C3", 0x02, "C", "F1", "Ikea east", "house"), ("C4", 0x04, "A", "F4", "Relay north", "house"),
  ("C2", 0x02, "C", "F1", "Ikea north", "house"), ("C1", 0x02, "C", "F1", "Ikea west", "house"),
  ("C0", 0x02, "C", "F1", "Ikea south", "house"), ("C5", 0x04, "A", "F4", "Relay south", "house"),
  ("C7", 0x07, "A", "F5", "LED desk", "house"),
  ("B7", 0xA3, "A", "00", "Guru", "subrack"), ("B6", 0xA2, "A", "00", "Dark", "subrack"),
  ("B2", 0xA0, "B", "F2", "Aux out", "subrack"), ("B1", 0xA0, "B", "F2", "Aux in", "subrack"),
  ("BA", 0xA8, "A", "00", "Rainbow", "subrack"), ("B9", 0xA4, "A", "00", "HSI", "subrack"),
  ("BC", 0xA1, "A", "F3", "Strip", "subrack"), ("B8", 0xA5, "A", "00", "Kaox", "subrack"),
  ("B4", 0xA1, "A", "F3", "Pwr 03", "subrack"), ("B5", 0xA1, "A", "F3", "Pwr 02", "subrack"),
  ("B3", 0xA1, "A", "F3", "Pwr 01", "subrack"), ("BB", 0xA7, "A", "00", "Preset", "subrack"),
  ("B0", 0xA6, "A", "00", "Main", "subrack"),
  ("E0", 0x03, "B", "00", "blacksheep", "machines"), ("E1", 0x03, "B", "00", "machariel", "machines"),
  ("D0", 0x05, "A", "00", "Main bed", "bedroom"), ("C6", 0x07, "A", "F5", "LED bed", "bedroom"),
][::-1]

STATS = ["rx", "rx_framing", "rx_overrun", "rx_buffer_full", "rx_start_unescaped", "rx_start_missing",
         "rx_len", "rx_crc", "tx", "tx_len", "tx_full"]
GURU = "B7"
GURU_INTERVAL_S = 11 * 60


def iso(t):
  return t.isoformat(timespec="seconds")


def main():
  ap = argparse.ArgumentParser()
  ap.add_argument("--all-stale", action="store_true", help="no node answered for 40 min")
  args = ap.parse_args()
  random.seed(42)
  now = datetime.datetime.now().replace(microsecond=0)
  broadcast_reboot = now - datetime.timedelta(days=1, hours=17, minutes=25)  # everyone rebooted then

  nodes = []
  for i, (addr, btype, rev, group, name, section) in enumerate(NODES):
    type_name, app_version, app_crc = APPS[btype]
    last_seen = now - datetime.timedelta(seconds=random.randint(20, GURU_INTERVAL_S))
    stats = {k: 0 for k in STATS}
    stats["rx"] = 255  # saturates: every node hears all traffic
    stats["tx"] = random.randint(6, 40)
    node = {
      "addr": addr, "name": name, "section": section,
      "type": "%02X" % btype, "type_name": type_name, "rev": rev, "group": group, "mode": "app",
      "boot": {"version": BOOT[0], "crc": BOOT[1]},
      "app": {"version": app_version, "crc": app_crc},
      "state": "ok", "last_seen": iso(last_seen), "missing_since": None,
      "last_up": iso(broadcast_reboot + datetime.timedelta(seconds=1 + i * 0.3)),
      "stats": stats, "stats_at": iso(last_seen),
    }
    nodes.append(node)
  by = {n["addr"]: n for n in nodes}

  # scenarios
  c5 = by["C5"]  # missing: the guru asked twice, no reply for 34 min
  c5["state"] = "missing"
  c5["last_seen"] = iso(now - datetime.timedelta(minutes=45))
  c5["stats_at"] = c5["last_seen"]
  c5["missing_since"] = iso(now - datetime.timedelta(minutes=34))

  b2 = by["B2"]  # rebooted 2 h ago, garbage while it came up
  b2["state"] = "errors"
  b2["last_up"] = iso(now - datetime.timedelta(hours=2, minutes=7))
  b2["stats"].update(rx=0x4C, rx_start_missing=0x1A, rx_framing=2, tx=3)

  b0 = by["B0"]  # one overrun, otherwise fine
  b0["state"] = "errors"
  b0["stats"]["rx_overrun"] = 1

  bb = by["BB"]  # no UP / ident seen yet: versions unknown
  bb["boot"] = bb["app"] = None
  bb["last_up"] = None

  c4 = by["C4"]  # still runs an older app than the other relay node
  c4["app"] = {"version": "6AE4B1C0", "crc": "5E17A2D4"}

  b3 = by["B3"]  # missed the UPDI round: still the old bootloader
  b3["boot"] = {"version": "65D0B423", "crc": "B15BDE5A"}

  b9 = by["B9"]  # answered the guru last time, but longer ago than one poll interval
  b9["last_seen"] = iso(now - datetime.timedelta(seconds=int(GURU_INTERVAL_S * 1.8)))
  b9["stats_at"] = b9["last_seen"]

  # a node that isn't in the config: new address, board type not in the protocol's type list. It sent its
  # UP 40 min ago, so the collector knows ident and versions, but no name, place or type name.
  new = {
    "addr": "C9", "name": None, "section": None,
    "type": "0B", "type_name": None, "rev": "A", "group": "00", "mode": "app",
    "boot": {"version": BOOT[0], "crc": BOOT[1]}, "app": {"version": "6AE6A0B1", "crc": "1D2E3F40"},
    "state": "ok", "last_seen": iso(now - datetime.timedelta(minutes=4)), "missing_since": None,
    "last_up": iso(now - datetime.timedelta(minutes=40)),
    "stats": dict({k: 0 for k in STATS}, rx=0xC4, tx=5), "stats_at": iso(now - datetime.timedelta(minutes=4)),
  }
  nodes.append(new)

  if args.all_stale:  # the guru stopped polling (or E0 / the collector went silent)
    for n in nodes:
      if n["state"] != "missing":
        n["last_seen"] = n["stats_at"] = iso(now - datetime.timedelta(minutes=40, seconds=random.randint(0, 600)))

  # gateways: only error lines of their log are published (no register writes, TX on / off ...: they show
  # activity). Only the gateway attached to this server has a log (E0 on blacksheep); others: log None.
  b2_up = datetime.datetime.fromisoformat(b2["last_up"])
  e0 = by["E0"]
  e0["log"] = sorted([
    {"t": iso(b2_up - datetime.timedelta(seconds=1)), "text": "RX Decode failed, no START found"},
    {"t": iso(b2_up - datetime.timedelta(seconds=1)), "text": "RX Decode failed, no START found"},
    {"t": iso(b2_up), "text": "RX Decode failed, CRC expected 1E but read 3A"},
    {"t": iso(now - datetime.timedelta(minutes=3)), "text": "RX Decode failed, un-escaped START found"},
  ], key=lambda e: e["t"], reverse=True)
  e0["state"] = "errors"  # decode errors within the last 24 h
  by["E1"]["log"] = None

  os.makedirs(OUT, exist_ok=True)
  data = {"generated": iso(now), "mock": True, "guru": GURU, "guru_interval_s": GURU_INTERVAL_S,
          "log_window_h": 24, "stats_keys": STATS, "sections": SECTIONS, "nodes": nodes}
  path = os.path.join(OUT, "mock.json")
  with open(path + ".tmp", "w", encoding="utf-8") as f:
    json.dump(data, f, indent=1)
  os.replace(path + ".tmp", path)
  stale = os.path.join(OUT, "gateway-log.json")  # earlier mock layout
  if os.path.exists(stale):
    os.remove(stale)
  print("wrote {} nodes to {}".format(len(nodes), os.path.normpath(path)))


if __name__ == "__main__":
  main()
