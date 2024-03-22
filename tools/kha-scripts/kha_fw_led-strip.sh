#!/bin/sh
if [ -z ${KHA_HOME+x} ]; then KHA_HOME="../.."; fi
${KHA_HOME}/tools/kha-scripts/kha_fw.py F5 07 41 ${KHA_HOME}/kha-nodes/kha-led-strip/kha-led-strip.X/dist/default/production/kha-led-strip.X.production.hex
