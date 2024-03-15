#!/bin/sh
if [ -z ${KHA_HOME+x} ]; then KHA_HOME="../.."; fi
${KHA_HOME}/tools/kha-scripts/kha_fw.py D0 05 41 ${KHA_HOME}/kha-nodes/kha-main/kha-main.X/dist/default/production/kha-main.X.production.hex
