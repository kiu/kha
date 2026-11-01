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
  hex file (CRC-32 over 0x4000..0xFFFF without the final XOR, as the node computes it at every boot;
  stacks before the full-CRC change stopped at 0xFFFE). Nodes whose UP got lost are asked by ident. A
  lost bootloader UP is accepted when the app CRC changed to the new one. Exit code 1 if one fails.
- The replies come back over UDP: the bridge sends the gateway's lines to the last UDP sender for 60 s.
- Short pauses by default (~35 s for a 16-page app). `--slow` uses the original fixed pauses; they are
  also used when no node answers the ident, because the result can't be checked then.

## kha_backup.py

`kha_backup.py [--local HOST[:PORT]] [--remote HOST[:PORT]] [--local-gateway XX]`: backs up every node's
registers over the bus through the local bridge (default 127.0.0.1:5005). The gateway behind it can't be
read through itself: it needs a second bridge (`--remote`, or `KHA_GATEWAY_REMOTE`), otherwise it's skipped. Finds each node's register length with single-byte reads, writes one JSON file per
node into `inventory/` and an overview into `INVENTORY.local.md` (both gitignored). What `kha_updi.py`
restores comes from the REGISTER SETUP sheet in `kha-protocol.ods` (wipe + setup commands per node); the
RAM values read over the bus are kept as `registers_ram` and differences are listed (switch states like
power buttons that are on right now). Location and UPDI data already in a JSON file are kept.
