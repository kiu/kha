#!/bin/sh
if [ -z ${KHA_HOME+x} ]; then KHA_HOME="../.."; fi
${KHA_HOME}/tools/kha-scripts/kha_fw.py F2 A0 42 ${KHA_HOME}/kha-bgt-subrack/kha-bgt-audio/kha-bgt-audio.X/dist/default/production/kha-bgt-audio.X.production.hex

