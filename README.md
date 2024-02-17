# kha

Overengineered Modular RS-485 Multi-Master 19" Subrack Home Control

<img src="kha-banner.jpg" width="800"/>

## Repository

<sup>Hint: "bgt" is German for [Baugruppenträger](https://de.wikipedia.org/wiki/Baugruppentr%C3%A4ger) translating to subrack assembly</sup>

- [datasheets](datasheets/): Datasheets of used components and rack dimensions / layouts
- [kha-bgt-misc](kha-bgt-misc/): Generic subrack modules
- [kha-bgt-rack](kha-bgt-rack/): 19" rack assembly
- [kha-bgt-subrack](kha-bgt-subrack/): Subrack modules
- [kha-boot.X](kha-boot.X/): Bootloader used by all devices ([main.c](kha-boot.X/main.c))
- [kha-common.X](kha-common.X/): Protocol stack used by all devices ([kha-stack.c](kha-common.X/kha-stack.c) [kha-stack.h](kha-common.X/kha-stack.h) [kha-constants.h](kha-common.X/kha-constants.h))
- [kha-nodes](kha-nodes/): Bus nodes
- [superseded](superseded/): Superseded ideas and failed hardware revisions
- [tools](tools/): Helper scripts to e.g. generate userrow data
- [kha-bom-collection.pdf](kha-bom-collection.pdf)/[.ods](kha-bom-collection.ods): Not exactly a Bill-of-Materials rather a collection of most components used
- [kha-protocol.pdf](kha-protocol.pdf)/[.ods](kha-protocol.ods): Protocol stack definitions

## Photos

<img src="kha-banner2.jpg" width="800"/>

<img src="kha-led-ikea-kallax-photo.jpg" width="800"/>

<img src="kha-relay-2x3-box-photo.jpg" width="800"/>

## Misc

- All PCBs use [eAVR](https://github.com/kiu/eAVR/) as connector for AVR flashing
- It all started simple with [lightdesk](https://github.com/kiu/lightdesk/)

## Todo

- Node: Infra-red and 433Mhz remote control node
- Node: LED Strip node
- Node: LED marquee node
- Node: IrDA bridge (bridging the bus through a window)
- Stack: Combine queued TX commands into single burst?
- Stack: Merge similiar queued TX commands into single command?
- Stack: Process TX commands as incoming RX commands?

## Regrets

- Terrible collision detection / avoidance
- Buck converter capacitor generates audible noise

# License

This project is licensed under the Creative Commons Attribution-NonCommercial 3.0 Unported (CC BY-NC 3.0) license.
