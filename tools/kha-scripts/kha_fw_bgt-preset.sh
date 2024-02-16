#!/bin/sh
if [ -z ${KHA_HOME+x} ]; then KHA_HOME="../.."; fi
${KHA_HOME}/tools/kha-scripts/kha_fw.py FF A7 41 ${KHA_HOME}/kha-bgt-subrack/kha-bgt-preset/kha-bgt-preset.X/dist/default/production/kha-bgt-preset.X.production.hex
