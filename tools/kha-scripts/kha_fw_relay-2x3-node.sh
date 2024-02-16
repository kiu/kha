#!/bin/sh
if [ -z ${KHA_HOME+x} ]; then KHA_HOME="../.."; fi
${KHA_HOME}/tools/kha-scripts/kha_fw.py F4 04 41 ${KHA_HOME}/kha-nodes/kha-relay-2x3/kha-relay-2x3-node/kha-relay-2x3-node.X/dist/default/production/kha-relay-2x3-node.X.production.hex
