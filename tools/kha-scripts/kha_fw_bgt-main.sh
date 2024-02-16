#!/bin/sh
if [ -z ${KHA_HOME+x} ]; then KHA_HOME="../.."; fi
${KHA_HOME}/tools/kha-scripts/kha_fw.py FF A6 41 ${KHA_HOME}/kha-bgt-subrack/kha-bgt-main/kha-bgt-main.X/dist/default/production/kha-bgt-main.X.production.hex
