#!/usr/bin/env python3

import sys
from optparse import OptionParser
from intelhex import IntelHex
from os import access, R_OK
from os.path import isfile
import os
import socket
from time import sleep

PAGE_SIZE = 512
PAGE_START = 32
PAGE_END = 128

PART_SIZE = 64

UDP_IP = "192.168.1.1"
UDP_PORT = 5005

def go():
  usage = "usage: %prog <device address 01-EF> <board type 01-FE> <board rev A-Z> <hex file>"
  parser = OptionParser(usage)
  (options, args) = parser.parse_args()
  if len(args) != 4:
    parser.error("incorrect number of arguments")

  device_addr = args[0].upper()
  board_type = args[1].upper()
  board_rev = args[2].upper()
  fn = args[3]

  if not isfile(fn) or not access(fn, R_OK):
    print('File doesnt exist or isnt readable.')
    return

  print("--- START {} ---\n".format(os.path.basename(fn)))
  sleep(2)

  sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM) # UDP
  sock.sendto(bytes("\n", 'ascii'), (UDP_IP, UDP_PORT))
  sleep(1)

  print("TX: F0 KHA_CMD_MANAGEMENT_TX_DISABLE")
  msg = "FFF0\n"
  sock.sendto(bytes(msg, 'ascii'), (UDP_IP, UDP_PORT))
  sleep(2)

  print("TX: FF KHA_CMD_MANAGEMENT_REBOOT")
  msg = "{}FF{}{}\n".format(device_addr, board_type, board_rev)
  sock.sendto(bytes(msg, 'ascii'), (UDP_IP, UDP_PORT))
  sleep(2)

  for i in range(0, 6):
    # stay
    print("TX: FD KHA_CMD_MANAGEMENT_BOOT_NOT_EXIT")
    msg = "{}FD{}{}\n".format(device_addr, board_type, board_rev)
    sock.sendto(bytes(msg, 'ascii'), (UDP_IP, UDP_PORT))
    sleep(1)

  print("TX: FC KHA_CMD_MANAGEMENT_BOOT_WIPE_FLASH")
  msg = "{}FC{}{}\n".format(device_addr, board_type, board_rev)
  sock.sendto(bytes(msg, 'ascii'), (UDP_IP, UDP_PORT))
  sleep(2)

  ih = IntelHex(fn)

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
      msg = msg + "\n"
      sock.sendto(bytes(msg, "ascii"), (UDP_IP, UDP_PORT))
      sleep(0.4)

    msg = "{}F9{}{}{}\n".format(device_addr, board_type, board_rev, "%0.2X" % page)
    sock.sendto(bytes(msg, "ascii"), (UDP_IP, UDP_PORT))
    sleep(0.4)  

  print("TX: FF KHA_CMD_MANAGEMENT_REBOOT")
  msg = "{}FF{}{}\n".format(device_addr, board_type, board_rev)
  sock.sendto(bytes(msg, 'ascii'), (UDP_IP, UDP_PORT))
  sleep(8)

  print("TX: F1 KHA_CMD_MANAGEMENT_TX_ENABLE")
  msg = "FFF1\n"
  sock.sendto(bytes(msg, 'ascii'), (UDP_IP, UDP_PORT))
  sleep(2)

  print("--- END {} ---\n".format(os.path.basename(fn)))


go()
