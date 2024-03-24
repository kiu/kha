#!/bin/sh
if [ -z ${KHA_HOME+x} ]; then KHA_HOME="../.."; fi
${KHA_HOME}/tools/kha-scripts/kha_fw.py D1 06 41 ${KHA_HOME}/kha-nodes/kha-remote/kha-remote-node.X/dist/default/production/kha-remote-node.X.production.hex

