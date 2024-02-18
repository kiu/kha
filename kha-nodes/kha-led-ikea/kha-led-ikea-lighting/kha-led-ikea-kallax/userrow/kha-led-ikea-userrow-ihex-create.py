#!/usr/bin/env python

import sys
from optparse import OptionParser
from intelhex import IntelHex

def run():
  usage = "usage: %prog <device address 01-FE> <hw board> <hw revision A-Z>"
  parser = OptionParser(usage)
  (options, args) = parser.parse_args()
  if len(args) < 2:
    parser.error("incorrect number of arguments")
  if len(args) > 3:
    parser.error("incorrect number of arguments")

  device_addr = args[0]
  hw_rev = args[2]
  hw_board = args[1]

  ih = IntelHex()
  ih[0] = int(device_addr,16)
  ih[1] = ord(hw_rev)
  ih.putsz(0x02, hw_board)

  fn = "kha-userrow_{0}_{1}_{2}.hex".format(hw_board, hw_rev, device_addr)
  ih.tofile(fn, format="hex")

  print("--- Raw content ---")
  ih.dump()

  print("--- Decoded content ---")
  print("Device Address: {0:02X}".format(ih[0]))
  print("Hardware Board: {0}".format(ih.getsz(0x02).decode("utf-8")))
  print("Hardware Revision: {0:c}".format(ih[1]))

if __name__ == '__main__':
    run()
