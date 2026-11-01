#!/usr/bin/env python3
"""kha-web collector: bus log -> SQLite -> nodes.json for the status page.

  python tools/kha-web/kha_collector.py            # read what's new in the log, export, exit
  python tools/kha-web/kha_collector.py --follow   # then keep following it (like tail -F)
  python tools/kha-web/kha_collector.py --rebuild  # new database from all log files

Reads both gateway output formats: human (E1 via kha_serial_log.py on this PC, times without a date) and
proto (E0 via kha_listen's tap on blacksheep, full timestamps). Otherwise passive: with --probe it sends
one ident broadcast (FFE0) through the bridge at startup, so type, group and versions of every node are
known right away (stats replies don't carry them); at most once per hour.

The database persists (nodes don't reboot for weeks, so their last UP must outlive the rotated logs): a
start resumes where the last run stopped, by the log file's inode and offset, reading the rest of
bus.log.1 first if logrotate moved the file in between. The first start (or --rebuild) reads the rotated
files too. The export is written only when something changed, once the bus has been quiet for a moment.

The local log has times without a date: on a first read they are counted back from the file's
modification time (one day back at every midnight rollover), later ones continue from the last line.
All times are stored with their UTC offset.
"""
import argparse
import datetime
import gzip
import json
import os
import re
import socket
import sqlite3
import statistics
import time

WEB = os.path.dirname(os.path.abspath(__file__))
DEFAULT_LOG = os.path.normpath(os.path.join(WEB, "..", "kha-scripts", "logs", "serial.log"))

# board types of the kha protocol (type byte of UP / ident): protocol, not setup
TYPES = {
  0x02: "led-ikea-node", 0x03: "gateway-usb", 0x04: "relay-2x3-node", 0x05: "main", 0x06: "remote-node",
  0x07: "led-strip", 0xA0: "bgt-audio", 0xA1: "bgt-power", 0xA2: "bgt-dark", 0xA3: "bgt-guru",
  0xA4: "bgt-hsi", 0xA5: "bgt-kaox", 0xA6: "bgt-main", 0xA7: "bgt-preset", 0xA8: "bgt-rainbow",
}

STATS = ["rx", "rx_framing", "rx_overrun", "rx_buffer_full", "rx_start_unescaped", "rx_start_missing",
         "rx_len", "rx_crc", "tx", "tx_len", "tx_full"]
# stacks before the 2026-10-30 rework send 8 counters (no framing / overrun / buffer full)
STATS_OLD = ["rx", "rx_start_unescaped", "rx_start_missing", "rx_len", "rx_crc", "tx", "tx_len", "tx_full"]

CMD_IDENT_RES, CMD_UP, CMD_STATS_REQ, CMD_STATS_RES = 0xE1, 0xE2, 0xE5, 0xE6

DEFAULT_GURU_INTERVAL_S = 11 * 60
LOG_WINDOW_H = 24
QUIET_S = 3  # export once the log has been quiet this long
PROBE_MIN_S = 3600  # --probe: at most one ident broadcast per hour

# 15:59:33.905 KS 00 RX L10 FE1 TB7 (U) CE6 [STATS RES]    <FF000000 00000000 790000>
RE_TIME = re.compile(r"^(\d\d):(\d\d):(\d\d)\.(\d{3}) (.*)$")
# the server tap (kha_listen) writes full timestamps: 2026-11-01T15:59:33.905+01:00 KS 40 10E1B7E6...
RE_DATETIME = re.compile(r"^(\d{4}-\d\d-\d\dT\d\d:\d\d:\d\d\.\d{3}(?:[+-]\d\d:\d\d)?) (.*)$")

# gateway output, human format (E1 here)
RE_FRAME = re.compile(r"^KS [0-9A-F]{2} (RX|TX) L([0-9A-F]{2}) F([0-9A-F]{2}) T([0-9A-F]{2}) \(.\) C([0-9A-F]{2}) .*<([0-9A-F ]*)>")
RE_DECODE_ERROR = re.compile(r"^KS [0-9A-F]{2} LOG (RX Decode failed.*)$")
# gateway output, proto format (E0): KS 40 / KS 50 + the frame (len from to cmd payload crc), and the
# stack's log entries as KS <id> <v1> <v2> <v3>; ids from KHA_STACK_LOG_* in kha-stack.h
RE_PROTO_FRAME = re.compile(r"^KS (40|50) ([0-9A-F]+)$")
RE_PROTO_LOG = re.compile(r"^KS ([0-9A-F]{2}) ([0-9A-F]{2}) ([0-9A-F]{2}) ([0-9A-F]{2})$")
PROTO_DECODE_ERRORS = {  # same texts as the human format
  0x41: "RX Decode failed, un-escaped START found", 0x42: "RX Decode failed, no START found",
  0x43: "RX Decode failed, exceeding length: {1} ({2})", 0x44: "RX Decode failed, CRC expected {1} but read {2}",
}


def parse_frame(text):
  """(direction, from, to, cmd, payload) of a frame line in either format, else None."""
  m = RE_FRAME.match(text)
  if m:
    direction, _, src, dst, cmd, payload = m.groups()
    return direction, src, dst, int(cmd, 16), bytes.fromhex(payload.replace(" ", ""))
  m = RE_PROTO_FRAME.match(text)
  if m:
    raw = bytes.fromhex(m.group(2)) if len(m.group(2)) % 2 == 0 else b""
    if len(raw) >= 5 and raw[0] == len(raw):
      return ("RX" if m.group(1) == "40" else "TX"), "%02X" % raw[1], "%02X" % raw[2], raw[3], raw[4:-1]
  return None


def decode_error(text):
  """Text of a gateway decode error line in either format, else None."""
  m = RE_DECODE_ERROR.match(text)
  if m:
    return m.group(1)
  m = RE_PROTO_LOG.match(text)
  if m and int(m.group(1), 16) in PROTO_DECODE_ERRORS:
    return PROTO_DECODE_ERRORS[int(m.group(1), 16)].format(*m.groups())
  return None


class Collector:
  # what the collector remembers between lines, besides the nodes; kept in the meta table
  RUNTIME = ("pending", "poll_times", "guru_requests", "local_gateway", "last_change", "last_line",
             "proto")

  def __init__(self, db_path, config, rebuild=False):
    self.config = config
    if rebuild and os.path.exists(db_path):
      os.remove(db_path)
    self.db = sqlite3.connect(db_path)
    self.db.executescript("""
      CREATE TABLE IF NOT EXISTS node (addr TEXT PRIMARY KEY, type INTEGER, rev INTEGER, grp INTEGER,
        mode INTEGER, boot_version TEXT, boot_crc TEXT, app_version TEXT, app_crc TEXT,
        last_seen TEXT, last_up TEXT, missing_since TEXT, stats TEXT, stats_at TEXT);
      CREATE TABLE IF NOT EXISTS event (t TEXT, addr TEXT, kind TEXT, detail TEXT);  -- up, missing, back
      CREATE TABLE IF NOT EXISTS stats (t TEXT, addr TEXT, counters TEXT);
      CREATE TABLE IF NOT EXISTS gateway_log (t TEXT, gateway TEXT, text TEXT);
      CREATE TABLE IF NOT EXISTS meta (key TEXT PRIMARY KEY, value TEXT);  -- runtime state, log position
      CREATE INDEX IF NOT EXISTS event_t ON event (t);
      CREATE INDEX IF NOT EXISTS gateway_log_t ON gateway_log (t);
    """)
    self.nodes = {}  # addr -> dict, mirrors the node table
    for row in self.db.execute("SELECT * FROM node"):
      n = dict(zip([d[0] for d in self.db.execute("SELECT * FROM node LIMIT 0").description], row))
      n["stats"] = json.loads(n["stats"]) if n["stats"] else None
      self.nodes[n["addr"]] = n
    self.pending = {}  # addr -> time of the guru's unanswered stats request
    self.poll_times = {}  # addr -> times of the guru's stats requests (for the interval)
    self.guru_requests = {}  # sender -> number of unicast stats requests (the guru sends the most)
    self.local_gateway = None  # sender of our own TX lines: the gateway whose log this is
    self.last_change = None  # time of the last line that changed something (= "generated")
    self.last_line = None  # time of the last line read (dates of lines without one continue from it)
    self.proto = False  # the gateway prints the proto format
    runtime = self.meta("runtime")
    for k in self.RUNTIME:
      if runtime and k in runtime:
        setattr(self, k, runtime[k])
    self.position = self.meta("position")  # {"inode", "offset"} of the log file read last

  def meta(self, key, value=None):
    if value is None:
      row = self.db.execute("SELECT value FROM meta WHERE key = ?", (key,)).fetchone()
      return json.loads(row[0]) if row else None
    self.db.execute("INSERT OR REPLACE INTO meta VALUES (?,?)", (key, json.dumps(value)))

  def commit(self, position):
    """Store the runtime state and how far the log has been read, in one transaction with the data."""
    self.poll_times = {a: ts[-5:] for a, ts in self.poll_times.items()}
    self.meta("runtime", {k: getattr(self, k) for k in self.RUNTIME})
    self.meta("position", position)
    self.position = position
    self.db.commit()

  # node state ----------------------------------------------------------------

  def node(self, addr):
    if addr not in self.nodes:
      self.nodes[addr] = {"addr": addr, "type": None, "rev": None, "grp": None, "mode": None,
                          "boot_version": None, "boot_crc": None, "app_version": None, "app_crc": None,
                          "last_seen": None, "last_up": None, "missing_since": None,
                          "stats": None, "stats_at": None}
    return self.nodes[addr]

  def save(self, n):
    cols = list(n)
    vals = [json.dumps(n[c]) if c == "stats" and n[c] is not None else n[c] for c in cols]
    self.db.execute(f"INSERT OR REPLACE INTO node ({','.join(cols)}) VALUES ({','.join('?' * len(cols))})", vals)

  def event(self, t, addr, kind, detail=""):
    self.db.execute("INSERT INTO event VALUES (?,?,?,?)", (t, addr, kind, detail))

  # one log line ----------------------------------------------------------------

  def line(self, t, text):
    """t: ISO time of the line, text: the rest after the time. Returns True if a node changed."""
    # a gateway with both outputs on prints every frame twice (human first): once proto lines show up,
    # the human ones (log id 00) are skipped, or each request would look like the guru's retry
    if RE_PROTO_FRAME.match(text) or RE_PROTO_LOG.match(text):
      self.proto = True
    elif self.proto and text.startswith("KS 00 "):
      return False
    error = decode_error(text)
    if error:
      if self.local_gateway:
        self.db.execute("INSERT INTO gateway_log VALUES (?,?,?)", (t, self.local_gateway, error))
        return True
      return False
    frame = parse_frame(text)
    if not frame:
      return False
    direction, src, dst, cmd, data = frame
    if direction == "TX":
      self.local_gateway = src

    # TX OFF (flashing) isn't special: nodes that don't answer then are shown missing, which is true
    if cmd == CMD_STATS_REQ and dst not in ("FF", "00") and int(dst, 16) < 0xF0:
      self.guru_requests[src] = self.guru_requests.get(src, 0) + 1
      # like the guru: only nodes that answered before can go missing (its scans ask all of 01-EF)
      known = dst in self.nodes and self.nodes[dst]["last_seen"]
      if src == self.guru() and known:
        self.poll_times.setdefault(dst, []).append(t)
        # the guru retries once: a second request while the first is unanswered = missing
        if dst in self.pending:
          n = self.node(dst)
          if not n["missing_since"]:
            n["missing_since"] = self.pending[dst]
            self.event(t, dst, "missing")
            self.save(n)
            return True
        else:
          self.pending[dst] = t

    if src in ("00", "FF"):
      return False
    # anything from a node: it's alive
    n = self.node(src)
    n["last_seen"] = t
    self.pending.pop(src, None)
    if n["missing_since"]:
      n["missing_since"] = None
      self.event(t, src, "back")

    if cmd in (CMD_UP, CMD_IDENT_RES) and len(data) == 20:
      n["type"], n["rev"], n["grp"], n["mode"] = data[0], data[1], data[2], data[3]
      n["boot_version"], n["boot_crc"] = data[4:8].hex().upper(), data[8:12].hex().upper()
      n["app_version"], n["app_crc"] = data[12:16].hex().upper(), data[16:20].hex().upper()
      if cmd == CMD_UP:
        n["last_up"] = t
        self.event(t, src, "up", "app" if data[3] else "bootloader")
    elif cmd == CMD_STATS_RES and len(data) in (len(STATS), len(STATS_OLD)):
      keys = STATS if len(data) == len(STATS) else STATS_OLD
      n["stats"] = {k: data[keys.index(k)] if k in keys else None for k in STATS}
      n["stats_at"] = t
      self.db.execute("INSERT INTO stats VALUES (?,?,?)", (t, src, json.dumps(n["stats"])))
    self.save(n)
    return True

  def guru(self):
    return max(self.guru_requests, key=self.guru_requests.get) if self.guru_requests else None

  def guru_interval_s(self):
    # time between the guru's requests to the same node, retries (< 1 min) left out
    gaps = []
    for times in self.poll_times.values():
      ts = [datetime.datetime.fromisoformat(x) for x in times[-20:]]
      gaps += [(b - a).total_seconds() for a, b in zip(ts, ts[1:]) if (b - a).total_seconds() > 60]
    return round(statistics.median(gaps)) if gaps else DEFAULT_GURU_INTERVAL_S

  # export ----------------------------------------------------------------------

  def export(self, path):
    generated = self.last_change
    places = {c["addr"]: c for c in self.config.get("nodes", [])}
    order = {c["addr"]: i for i, c in enumerate(self.config.get("nodes", []))}
    since = (datetime.datetime.fromisoformat(generated) - datetime.timedelta(hours=LOG_WINDOW_H)).isoformat()
    out = []
    for addr in sorted(self.nodes, key=lambda a: (order.get(a, 999), a)):
      n = self.nodes[addr]
      place = places.get(addr, {})
      fw = lambda v, c: {"version": n[v], "crc": n[c]} if n[v] else None
      node = {
        "addr": addr, "name": place.get("name"), "section": place.get("section"),
        "type": "%02X" % n["type"] if n["type"] is not None else "??",
        "type_name": TYPES.get(n["type"]), "rev": chr(n["rev"]) if n["rev"] else "?",
        "group": "%02X" % n["grp"] if n["grp"] is not None else "?",
        "mode": None if n["mode"] is None else ("app" if n["mode"] else "bootloader"),
        "boot": fw("boot_version", "boot_crc"), "app": fw("app_version", "app_crc"),
        "last_seen": n["last_seen"], "last_up": n["last_up"], "missing_since": n["missing_since"],
        "stats": n["stats"] or {k: None for k in STATS}, "stats_at": n["stats_at"],
      }
      errors = sum(v for k, v in (n["stats"] or {}).items() if k not in ("rx", "tx") and v)
      if addr == self.local_gateway:
        node["log"] = [{"t": t, "text": text} for t, text in self.db.execute(
          "SELECT t, text FROM gateway_log WHERE gateway = ? AND t >= ? ORDER BY t DESC", (addr, since))]
        errors += len(node["log"])
      elif n["type"] == 0x03:
        node["log"] = None  # another gateway: its log isn't on this machine
      node["state"] = ("missing" if n["missing_since"] else "unknown" if not n["stats"] and not n["app_version"]
                       else "errors" if errors else "ok")
      out.append(node)

    # generated without the milliseconds
    data = {"generated": generated[:19] + generated[23:], "mock": False, "guru": self.guru(),
            "guru_interval_s": self.guru_interval_s(),
            "log_window_h": LOG_WINDOW_H, "stats_keys": STATS, "sections": self.config.get("sections", []),
            "nodes": out}
    os.makedirs(os.path.dirname(path), exist_ok=True)
    with open(path + ".tmp", "w", encoding="utf-8") as f:
      json.dump(data, f, indent=1)
    os.replace(path + ".tmp", path)


# reading the log -------------------------------------------------------------------

def parse_time(line):
  """(aware datetime, rest) for the server tap's lines, (time, rest) for the local log's, else (None, None)."""
  m = RE_DATETIME.match(line)
  if m:
    t = datetime.datetime.fromisoformat(m.group(1))
    return (t if t.tzinfo else t.astimezone()), m.group(2)
  m = RE_TIME.match(line)
  if not m:
    return None, None
  h, mi, s, ms, rest = m.groups()
  return datetime.time(int(h), int(mi), int(s), int(ms) * 1000), rest


def iso(t):
  return t.isoformat(timespec="milliseconds")


def read_lines(path, offset=0):
  """Complete lines from offset on, and the offset after them. Rotated .gz files are read whole."""
  if path.endswith(".gz"):
    with gzip.open(path, "rb") as f:
      raw = f.read()
    return raw.decode("utf-8", "replace").splitlines(), None
  with open(path, "rb") as f:
    if os.fstat(f.fileno()).st_size < offset:  # truncated: start over
      offset = 0
    f.seek(offset)
    raw = f.read()
  end = raw.rfind(b"\n") + 1  # an unfinished last line is read with the next batch
  return raw[:end].decode("utf-8", "replace").splitlines(), offset + end


def process(c, lines, anchor=None):
  """Feed lines to the collector. Lines without a date continue from the last line's date (one day on at
  every midnight); with an anchor (file mtime, on a first read) they are dated back from it instead."""
  parsed = [(t, rest) for t, rest in map(parse_time, lines) if t]
  if anchor and any(not isinstance(t, datetime.datetime) for t, _ in parsed):
    day, later, dated = anchor.date(), None, []
    for t, rest in reversed(parsed):
      if isinstance(t, datetime.datetime):
        day, later = t.date(), t.time()
        dated.append((t, rest))
        continue
      if later and t > later:  # going back past midnight
        day -= datetime.timedelta(days=1)
      later = t
      dated.append((datetime.datetime.combine(day, t).astimezone(), rest))
    parsed = dated[::-1]
  changed = False
  for t, rest in parsed:
    if not isinstance(t, datetime.datetime):
      last = datetime.datetime.fromisoformat(c.last_line) if c.last_line else datetime.datetime.now().astimezone()
      day = last.date() + datetime.timedelta(days=1 if t < last.time() else 0)
      t = datetime.datetime.combine(day, t).astimezone()
    c.last_line = iso(t)
    if c.line(c.last_line, rest):
      c.last_change, changed = c.last_line, True
  return changed


def rotated(path):
  """Rotated logrotate files, oldest first: bus.log.7.gz ... bus.log.2.gz, bus.log.1."""
  found = []
  for name in os.listdir(os.path.dirname(path) or "."):
    m = re.fullmatch(re.escape(os.path.basename(path)) + r"\.(\d+)(\.gz)?", name)
    if m:
      found.append((int(m.group(1)), os.path.join(os.path.dirname(path), name)))
  return [p for _, p in sorted(found, reverse=True)]


def catch_up(c, path):
  """Read whatever is new since the stored position, across a rotation; commit. Returns True on changes."""
  if not os.path.exists(path):
    return False
  inode = os.stat(path).st_ino
  pos = c.position
  changed = False
  if pos is None:  # first start: everything there is, oldest first
    for p in rotated(path):
      lines, _ = read_lines(p)
      changed |= process(c, lines, datetime.datetime.fromtimestamp(os.path.getmtime(p)).astimezone())
    lines, offset = read_lines(path)
    changed |= process(c, lines, datetime.datetime.fromtimestamp(os.path.getmtime(path)).astimezone())
  elif pos["inode"] == inode:
    lines, offset = read_lines(path, pos["offset"])
    changed |= process(c, lines)
  else:  # rotated since: the rest of the old file (now .1), then the new one
    old = path + ".1"
    if os.path.exists(old) and os.stat(old).st_ino == pos["inode"]:
      lines, _ = read_lines(old, pos["offset"])
      changed |= process(c, lines)
    else:
      print(f"{path}: rotated more than once since the last read, lines in between are skipped", flush=True)
    lines, offset = read_lines(path)
    changed |= process(c, lines)
  if changed or pos is None or offset != pos["offset"] or inode != pos["inode"]:
    c.commit({"inode": inode, "offset": offset})
  return changed


def probe(c, target):
  """One ident broadcast through the UDP bridge; the replies arrive through the log like any traffic."""
  # at most once per PROBE_MIN_S: a crash loop (Restart=always) must not flood the bus with broadcasts;
  # the time is stored before sending, so a crash right after it counts too
  now = datetime.datetime.now().astimezone()
  last = c.meta("last_probe")
  if last and (now - datetime.datetime.fromisoformat(last)).total_seconds() < PROBE_MIN_S:
    print(f"probe skipped: last probe at {last}", flush=True)
    return
  c.meta("last_probe", now.isoformat(timespec="seconds"))
  c.db.commit()
  host, port = target.rsplit(":", 1)
  try:
    with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as s:
      s.sendto(b"FFE0\n", (host, int(port)))
    print(f"probe: FFE0 sent to {target}", flush=True)
  except OSError as e:
    print(f"probe to {target} failed: {e}", flush=True)


def main():
  ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
  ap.add_argument("--log", default=DEFAULT_LOG, help="bus log (default: kha-scripts/logs/serial.log)")
  ap.add_argument("--db", default=os.path.join(WEB, "kha.db"))
  ap.add_argument("--out", default=os.path.join(WEB, "webroot", "data", "nodes.json"))
  ap.add_argument("--config", default=os.path.join(WEB, "config.json"), help="names, places, order (optional)")
  ap.add_argument("--follow", action="store_true", help="keep following the log")
  ap.add_argument("--rebuild", action="store_true", help="start a new database from the log files")
  ap.add_argument("--probe", metavar="HOST:PORT", help="send one FFE0 through this UDP bridge at startup "
                  "(kha_listen / kha_serial_log.py: 127.0.0.1:5005)")
  args = ap.parse_args()

  config = {}
  if os.path.exists(args.config):
    with open(args.config, encoding="utf-8") as f:
      config = json.load(f)
  c = Collector(args.db, config, args.rebuild)
  t0 = time.monotonic()
  resumed = c.position is not None
  catch_up(c, args.log)
  if args.probe:
    probe(c, args.probe)
  if c.last_change:
    c.export(args.out)
  print(f"{'resumed' if resumed else 'read'} {args.log} in {time.monotonic() - t0:.1f} s: {len(c.nodes)} nodes, "
        f"guru {c.guru()} every {c.guru_interval_s()} s, data up to {c.last_change}, gateway {c.local_gateway}",
        flush=True)
  if not args.follow:
    return
  # export once the log has been quiet for QUIET_S: one write per burst (guru round), none while idle
  dirty, quiet_since = False, time.monotonic()
  while True:
    if catch_up(c, args.log):
      dirty, quiet_since = True, time.monotonic()
    elif dirty and time.monotonic() - quiet_since >= QUIET_S:
      c.export(args.out)
      dirty = False
      print(f"{datetime.datetime.now():%H:%M:%S} exported (data {c.last_change[11:19]})", flush=True)
    time.sleep(0.5)


if __name__ == "__main__":
  main()
