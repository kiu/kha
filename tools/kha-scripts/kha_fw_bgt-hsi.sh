#!/bin/sh
if [ -z ${KHA_HOME+x} ]; then KHA_HOME="../.."; fi
${KHA_HOME}/tools/kha-scripts/kha_fw.py FF A4 41 ${KHA_HOME}/kha-bgt-subrack/kha-bgt-hsi/kha-bgt-hsi.X/dist/default/production/kha-bgt-hsi.X.production.hex
