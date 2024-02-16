#!/bin/sh
if [ -z ${KHA_HOME+x} ]; then KHA_HOME="../.."; fi
${KHA_HOME}/tools/kha-scripts/kha_fw.py FF A5 41 ${KHA_HOME}/kha-bgt-subrack/kha-bgt-kaox/kha-bgt-kaox.X/dist/default/production/kha-bgt-kaox.X.production.hex
