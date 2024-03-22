#!/bin/sh
if [ -z ${KHA_HOME+x} ]; then KHA_HOME="../.."; fi
${KHA_HOME}/tools/kha-scripts/kha_fw.py BC A9 41 ${KHA_HOME}/kha-bgt-subrack/kha-bgt-strip/kha-bgt-strip.X/dist/default/production/kha-bgt-strip.X.production.hex

