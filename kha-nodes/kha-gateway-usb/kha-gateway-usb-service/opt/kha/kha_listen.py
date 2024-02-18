#!/usr/bin/env python
import threading

import serial
import time
import re
from datetime import timedelta, datetime
from dateutil.relativedelta import relativedelta
import subprocess

import socket

PORT = '/dev/ttyUSB0'
UDP_IP = "0.0.0.0"
UDP_PORT = 5005
EXEC_SHUTDOWN_TIMER="ssh kiu@machariel.qnet c:\\\Windows\\\PSTools\\\psshutdown64.exe -h -c -t 30"
EXEC_ABORT="ssh kiu@machariel.qnet c:\\\Windows\\\PSTools\\\psshutdown64.exe -a"

ser = 0
sock = 0
last_shutdown = datetime.now() - relativedelta(years=10)

def run_cmd(cmd):
  subprocess.Popen(cmd, shell=True, stdin=subprocess.DEVNULL, stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)

def kha_decode(line):
    global last_shutdown

    if not line.startswith('KS 40 '):
      return

#    print(line, end="")

    if re.match("KS 40 06..FFED01..", line): #PRESET Shutdown
      last_shutdown = datetime.now()
      run_cmd(EXEC_SHUTDOWN_TIMER)
      return

    if re.match("KS 40 06..FFED00..", line): #PRESET Poweroff
      last_shutdown = datetime.now()
      run_cmd(EXEC_SHUTDOWN_TIMER)
      return

    if re.match("KS 40 06..FFED....", line): #PRESET Any
      if last_shutdown + timedelta(seconds = 30) > datetime.now():
        last_shutdown = datetime.now() - relativedelta(years=10)
        run_cmd(EXEC_ABORT)
      return

def init_serial():
  global ser
  try:
    ser = serial.Serial(PORT, 115200, timeout=1)
    ser.write(b"\n")
    ser.flush()
  except:
    print("Exception init_serial()")
    time.sleep(1)

def run_serial():
  global ser
  while True:
    try:
      kha_decode(ser.readline().decode("utf-8"))
    except:
      print("Exception run_serial()")
      time.sleep(1)
      init_serial()

def init_network():
  global sock
  try:
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    sock.bind((UDP_IP, UDP_PORT))
  except:
    print("Exception init_network()")
    time.sleep(1)

def run_network():
  global ser
  global sock
  while True:
    try:
      data, addr = sock.recvfrom(1024)
    except:
      print("Exception run_network() socket")
      time.sleep(1)
      init_network()
      continue

    try:
      ser.write(data)
      ser.flush()
      time.sleep(0.1)
    except:
      print("Exception run_network() serial")
      time.sleep(1)
      init_serial()

init_serial()
init_network()

t1 = threading.Thread(target=run_serial)
t1.start()

t2 = threading.Thread(target=run_network)
t2.start()
