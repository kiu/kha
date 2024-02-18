/* 
 * File:   main.h
 * Author: kiu
 *
 * Created on January 27, 2024, 12:49 PM
 */

#ifndef MAIN_H
#define	MAIN_H

#ifdef	__cplusplus
extern "C" {
#endif

#define IKEA_ADDR_SELECTION 0x00
#define IKEA_ADDR_HUE 0x01
#define IKEA_ADDR_SATURATION 0x02
#define IKEA_ADDR_INTENSE 0x03
#define IKEA_ADDR_ANIM_ENABLED 0x04
#define IKEA_ADDR_ANIM_SPEED 0x05
#define IKEA_ADDR_ANIM_WIDTH 0x06
#define IKEA_ADDR_IDENT 0x07
#define IKEA_ADDR_LAYOUT_AMOUNT 0x08
#define IKEA_ADDR_LAYOUT_ORIENTATION 0x09
#define IKEA_ADDR_LAYOUT_LOW_AMOUNT 0x0A
#define IKEA_ADDR_LAYOUT_LOCATION 0x0B

    enum IKEA_MODE {
        IKEA_SELECTION_OFF, IKEA_SELECTION_LOW, IKEA_SELECTION_GRADIENT, IKEA_SELECTION_FULL, IKEA_SELECTION_INIT
    };

#define HSI_H_INIT 0x00
#define HSI_H_MIN 0x00
#define HSI_H_MAX 0xFF
#define HSI_H_OVF true

#define HSI_S_INIT 0x00
#define HSI_S_MIN 0x00
#define HSI_S_MAX 0xFF
#define HSI_S_OVF false

#define HSI_I_INIT 0xFF
#define HSI_I_MIN 0x00
#define HSI_I_MAX 0xFF
#define HSI_I_OVF false

#define ANIM_E_INIT false

#define ANIM_S_INIT 0x00
#define ANIM_S_MIN 0x00
#define ANIM_S_MAX 0xFF
#define ANIM_S_OVF false

#define ANIM_W_INIT 0x00
#define ANIM_W_MIN 0x00
#define ANIM_W_MAX 0x20
#define ANIM_W_OVF false

#ifdef	__cplusplus
}
#endif

#endif	/* MAIN_H */

