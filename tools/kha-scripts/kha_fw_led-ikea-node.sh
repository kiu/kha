#!/bin/sh
if [ -z ${KHA_HOME+x} ]; then KHA_HOME="../.."; fi
${KHA_HOME}/tools/kha-scripts/kha_fw.py F1 02 43 ${KHA_HOME}/kha-nodes/kha-led-ikea/kha-led-ikea-node/kha-led-ikea-node.X/dist/default/production/kha-led-ikea-node.X.production.hex
