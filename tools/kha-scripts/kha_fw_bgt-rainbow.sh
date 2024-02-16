#!/bin/sh
if [ -z ${KHA_HOME+x} ]; then KHA_HOME="../.."; fi
${KHA_HOME}/tools/kha-scripts/kha_fw.py FF A8 41 ${KHA_HOME}/kha-bgt-subrack/kha-bgt-rainbow/kha-bgt-rainbow.X/dist/default/production/kha-bgt-rainbow.X.production.hex
