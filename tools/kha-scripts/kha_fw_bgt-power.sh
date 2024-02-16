#!/bin/sh
if [ -z ${KHA_HOME+x} ]; then KHA_HOME="../.."; fi
${KHA_HOME}/tools/kha-scripts/kha_fw.py F3 A1 41 ${KHA_HOME}/kha-bgt-subrack/kha-bgt-power/kha-bgt-power.X/dist/default/production/kha-bgt-power.X.production.hex
