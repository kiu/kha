#ifndef LED_GENERIC_H
#define	LED_GENERIC_H

#ifdef	__cplusplus
extern "C" {
#endif

#define LED_ADDR_SELECTION 0x00

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
#define ANIM_W_MAX 0xFF
#define ANIM_W_OVF false

#ifdef	__cplusplus
}
#endif

#endif

