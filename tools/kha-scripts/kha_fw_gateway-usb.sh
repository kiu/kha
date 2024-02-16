#!/bin/sh
#echo NO REMOTE UPDATE FOR $0
#exit
if [ -z ${KHA_HOME+x} ]; then KHA_HOME="../.."; fi
${KHA_HOME}/tools/kha-scripts/kha_fw.py E1 03 42 ${KHA_HOME}/kha-nodes/kha-gateway-usb/kha-gateway-usb.X/dist/default/production/kha-gateway-usb.X.production.hex
