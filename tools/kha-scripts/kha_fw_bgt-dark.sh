#!/bin/sh
if [ -z ${KHA_HOME+x} ]; then KHA_HOME="../.."; fi
${KHA_HOME}/tools/kha-scripts/kha_fw.py FF A2 41 ${KHA_HOME}/kha-bgt-subrack/kha-bgt-dark/kha-bgt-dark.X/dist/default/production/kha-bgt-dark.X.production.hex
