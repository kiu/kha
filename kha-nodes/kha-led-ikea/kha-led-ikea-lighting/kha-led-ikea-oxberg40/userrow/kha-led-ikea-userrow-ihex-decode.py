#!/usr/bin/env python

import sys
from optparse import OptionParser
from os import access, R_OK
from os.path import isfile
from intelhex import IntelHex

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
  print("Device Address: {0:02X}".format(ih[0]))
  print("Hardware Board: {0}".format(ih.getsz(0x02).decode("utf-8")))
  print("Hardware Revision: {0:c}".format(ih[1]))

if __name__ == '__main__':
    run()
