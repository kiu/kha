#!/usr/bin/env python

import sys
from optparse import OptionParser
from os import access, R_OK
from os.path import isfile
from intelhex import IntelHex

DATA_MAX_LEN = (32 - 4)

def run():
  usage = "usage: %prog <intel hex file>"
  parser = OptionParser(usage)
  (options, args) = parser.parse_args()
  if len(args) != 1:
    parser.error("incorrect number of arguments")
  fn = args[0]

  if not isfile(fn) or not access(fn, R_OK):
    sys.exit('File doesnt exist or isnt readable.')

  ih = IntelHex()
  ih.loadhex(fn)

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

