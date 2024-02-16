#!/bin/sh
if [ -z ${KHA_HOME+x} ]; then KHA_HOME="../.."; fi
${KHA_HOME}/tools/kha-scripts/kha_fw.py FF A3 41 ${KHA_HOME}/kha-bgt-subrack/kha-bgt-guru/kha-bgt-guru.X/dist/default/production/kha-bgt-guru.X.production.hex
