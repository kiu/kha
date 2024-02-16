#!/usr/bin/env python

import sys
from optparse import OptionParser
from intelhex import IntelHex

DATA_MAX_LEN = (32 - 4)

def run():
  usage = "usage: %prog <board type 02-FE> <board rev A-Z> <device address 02-EF> <device group 00,F1-FE> [data]"
  parser = OptionParser(usage)
  (options, args) = parser.parse_args()
  if len(args) < 4:
    parser.error("incorrect number of arguments")
  if len(args) == 5 and (len(args[4]) > ((DATA_MAX_LEN) * 2)):
    parser.error("data is too long")
  if len(args) > 5:
    parser.error("incorrect number of arguments")

  board_type = args[0].upper()
  board_rev = args[1].upper()
  device_addr = args[2].upper()
  device_group = args[3].upper()

  data = [0] * (DATA_MAX_LEN)

  if len(args) == 5:
    data_bin = bytes.fromhex(args[4])
    print(data_bin)
    i = 0
    for d in data_bin:
      data[i] = d
      i = i + 1
    print(data)
    
  ih = IntelHex()
  ih[0] = int(board_type, 16)
  ih[1] = ord(board_rev)
  ih[2] = int(device_addr, 16)
  ih[3] = int(device_group, 16)
  i = 4
  for d in data:
    ih[i] = d
    i = i + 1

  fn = "kha-userrow_BT{0}_BR{1}_DA{2}_DG{3}.hex".format(board_type, board_rev, device_addr, device_group)
  ih.tofile(fn, format="hex")

  print("--- Raw content ---")
  ih.dump()

  print("--- Decoded content ---")
  print("Board Type:     {0:02X}".format(ih[0]))
  print("Board Rev:      {0:c}".format(ih[1]))
  print("Device Address: {0:02X}".format(ih[2]))
  print("Device Group:   {0:02X}".format(ih[3]))
  print("Data:           {0}".format(ih.gets(0x04, DATA_MAX_LEN).hex().upper()))

if __name__ == '__main__':
    run()
