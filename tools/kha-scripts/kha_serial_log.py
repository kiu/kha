#!/usr/bin/env python3
"""Log bridge for kha-gateway-usb on a Windows/Linux PC.

Owns the gateway's serial port (only one program can open it on Windows) and appends every line,
prefixed with the PC time, to a log file that any number of readers can follow live:

  python tools/kha-scripts/kha_serial_log.py              # finds the CH340 by USB VID/PID
  Get-Content -Wait -Tail 30 tools/kha-scripts/logs/serial.log

Lines to send to the gateway (hex: <to><cmd><opt...>, e.g. "FFE5") come from:
  - this window (type and press Enter)
  - lines appended to tools/kha-scripts/logs/commands.txt
  - UDP datagrams on 127.0.0.1:5005, like kha_listen.py, so kha_fw.py works locally:
      KHA_GATEWAY=127.0.0.1 python tools/kha-scripts/kha_fw.py ...
    the last UDP sender gets the gateway's lines back for 60 s (kha_fw.py ident check)

Survives gateway resets and unplugging: it reconnects as soon as the port comes back.
"""
import argparse
import datetime
import os
import queue
import socket
import sys
import threading
import time

import serial
from serial.tools import list_ports

VID, PID = 0x1A86, 0x7523  # CH340 on kha-gateway-usb
BAUD = 115200
UDP_IP = "127.0.0.1"
UDP_PORT = 5005
REPLY_TIMEOUT = 60  # seconds the last UDP sender gets the gateway's lines back
HERE = os.path.dirname(os.path.abspath(__file__))
LOG_DIR = os.path.join(HERE, "logs")


def find_port():
  for p in list_ports.comports():
    if p.vid == VID and p.pid == PID:
      return p.device
  return None


def stamp():
  return datetime.datetime.now().strftime("%H:%M:%S.%f")[:-3]


class Bridge:
  def __init__(self, log_path, port):
    self.port = port
    self.log = open(log_path, "a", encoding="utf-8", buffering=1)
    self.ser = None
    self.commands = queue.Queue()
    self.lock = threading.Lock()
    self.udp = None
    self.reply_addr = None
    self.reply_until = 0

  def emit(self, text):
    line = "{} {}".format(stamp(), text)
    with self.lock:
      print(line, flush=True)
      self.log.write(line + "\n")

  # --- command sources -------------------------------------------------------

  def watch_stdin(self):
    for line in sys.stdin:
      self.commands.put(line.strip())

  def watch_file(self, path):
    open(path, "a").close()
    pos = os.path.getsize(path)  # only new lines
    while True:
      size = os.path.getsize(path)
      if size < pos:
        pos = 0  # file was truncated
      if size > pos:
        with open(path, encoding="utf-8", errors="replace") as f:
          f.seek(pos)
          data = f.read()
          pos = f.tell()
        for line in data.splitlines():
          self.commands.put(line.strip())
      time.sleep(0.2)

  def watch_udp(self):
    self.udp = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    self.udp.bind((UDP_IP, UDP_PORT))
    while True:
      data, addr = self.udp.recvfrom(1024)
      self.reply_addr, self.reply_until = addr, time.time() + REPLY_TIMEOUT
      for line in data.decode("ascii", "replace").splitlines() or [""]:
        self.commands.put(line.strip())

  def reply(self, text):
    if self.reply_addr is None or time.time() > self.reply_until:
      return
    try:
      self.udp.sendto((text + "\n").encode("utf-8"), self.reply_addr)
    except OSError:
      pass

  def send(self, line):
    if self.ser is None:
      self.emit("--- not connected, dropped '{}'".format(line))
      return
    self.ser.write(line.encode("ascii") + b"\n")
    self.ser.flush()
    if line:
      self.emit(">>> {}".format(line))
    time.sleep(0.1)  # same pacing as kha_listen.py

  def drain_commands(self):
    while not self.commands.empty():
      self.send(self.commands.get())

  # --- serial ----------------------------------------------------------------

  def run(self, commands_path):
    threading.Thread(target=self.watch_stdin, daemon=True).start()
    threading.Thread(target=self.watch_file, args=(commands_path,), daemon=True).start()
    threading.Thread(target=self.watch_udp, daemon=True).start()
    self.emit("--- kha serial log, UDP {}:{}, commands file {}".format(UDP_IP, UDP_PORT, commands_path))

    waiting = False
    while True:
      port = self.port or find_port()
      if port is None:
        if not waiting:
          self.emit("--- waiting for the gateway (USB VID 1A86 / PID 7523)")
          waiting = True
        self.drain_commands()
        time.sleep(0.5)
        continue
      try:
        self.ser = serial.Serial(port, BAUD, timeout=0.05)
      except serial.SerialException:
        time.sleep(0.5)
        continue
      waiting = False
      buf = b""
      self.emit("--- connected to {}".format(port))
      try:
        while True:
          self.drain_commands()
          data = self.ser.read(4096)
          if not data:
            continue
          buf += data
          *lines, buf = buf.split(b"\n")
          for raw in lines:
            text = raw.rstrip(b"\r").decode("utf-8", "replace")
            if text:
              self.emit(text)
              self.reply(text)
      except (serial.SerialException, OSError):
        self.emit("--- disconnected from {}".format(port))
      finally:
        try:
          self.ser.close()
        except Exception:
          pass
        self.ser = None
      time.sleep(0.5)


def main():
  ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
  ap.add_argument("--port", help="COM port (default: find the CH340 by VID/PID)")
  ap.add_argument("--log", default=os.path.join(LOG_DIR, "serial.log"), help="log file (appended)")
  ap.add_argument("--commands", default=os.path.join(LOG_DIR, "commands.txt"), help="command file")
  args = ap.parse_args()
  os.makedirs(os.path.dirname(os.path.abspath(args.log)), exist_ok=True)
  Bridge(args.log, args.port).run(args.commands)


if __name__ == "__main__":
  try:
    main()
  except KeyboardInterrupt:
    pass
