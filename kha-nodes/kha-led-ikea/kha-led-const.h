/* 
 * File:   kha-constants-rx4.h
 * Author: kiu
 *
 * Created on March 25, 2023, 11:53 PM
 */

#ifndef KHA_CONSTANTS_RX4_H
#define	KHA_CONSTANTS_RX4_H

#ifdef	__cplusplus
extern "C" {
#endif

#define KHA_LED_MSG_SIZE_MIN 4 // len + addr + cmd + crc
#define KHA_LED_MSG_SIZE_MAX 8 // len + addr + cmd + 4 opt + crc

#define KHA_LED_MSG_START 0x42
#define KHA_LED_MSG_START_CONFIRM 0x99
#define KHA_LED_MSG_START_ESCAPE 0x66

#define KHA_LED_CMD_SET_HSI 0x01
#define KHA_LED_CMD_IDENT 0x02
#define KHA_LED_CMD_SET_RGBW 0x03

#define KHA_LED_ADDR_NONE 0x00
#define KHA_LED_ADDR_BROADCAST 0xFF

#ifdef	__cplusplus
}
#endif

#endif	/* KHA_CONSTANTS_RX4_H */

