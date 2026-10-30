# kha-scripts

Scripts for updating firmware via the bus

Uses [kha-gateway-usb](../../kha-nodes/kha-gateway-usb) and [kha-gateway-usb-service](../../kha-nodes/kha-gateway-usb-service)




## kha_fw.py

`kha_fw.py [--slow] <device address 01-FF> <board type> <board rev> <hex file>`, gateway from `KHA_GATEWAY`
(default 192.168.1.1, `127.0.0.1` for the local `kha_serial_log.py`).

- Before flashing it sends an ident request (FFE0 for a group or broadcast) and lists the nodes that match
  address/group, board type and rev.
- It waits for each node's bootloader UP after the reboot, then sends BOOT STAY. A matching node that missed
  the ident but sends an UP is added; a listed node without bootloader UP is reported (didn't reboot).
- After the final reboot it waits for each node's app UP and checks that it runs the app with the CRC of the
  hex file (CRC-32 over 0x4000..0xFFFE without the final XOR, as the node computes it at every boot).
  Nodes whose UP got lost are asked by ident. Exit code 1 if one fails.
- The replies come back over UDP: the bridge sends the gateway's lines to the last UDP sender for 60 s.
- Short pauses by default (~35 s for a 16-page app). `--slow` uses the original fixed pauses; they are
  also used when no node answers the ident, because the result can't be checked then.
