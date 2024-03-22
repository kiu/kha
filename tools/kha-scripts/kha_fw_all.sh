#!/bin/sh
if [ -z ${KHA_HOME+x} ]; then KHA_HOME="../.."; fi

${KHA_HOME}/tools/kha-scripts/kha_fw_gateway-usb.sh
${KHA_HOME}/tools/kha-scripts/kha_fw_led-ikea-node.sh
${KHA_HOME}/tools/kha-scripts/kha_fw_led-strip.sh
${KHA_HOME}/tools/kha-scripts/kha_fw_relay-2x3-node.sh
${KHA_HOME}/tools/kha-scripts/kha_fw_main-node.sh

${KHA_HOME}/tools/kha-scripts/kha_fw_bgt-audio.sh
${KHA_HOME}/tools/kha-scripts/kha_fw_bgt-dark.sh
${KHA_HOME}/tools/kha-scripts/kha_fw_bgt-guru.sh
${KHA_HOME}/tools/kha-scripts/kha_fw_bgt-hsi.sh
${KHA_HOME}/tools/kha-scripts/kha_fw_bgt-kaox.sh
${KHA_HOME}/tools/kha-scripts/kha_fw_bgt-main.sh
${KHA_HOME}/tools/kha-scripts/kha_fw_bgt-power.sh
${KHA_HOME}/tools/kha-scripts/kha_fw_bgt-preset.sh
${KHA_HOME}/tools/kha-scripts/kha_fw_bgt-rainbow.sh
${KHA_HOME}/tools/kha-scripts/kha_fw_bgt-strip.sh
