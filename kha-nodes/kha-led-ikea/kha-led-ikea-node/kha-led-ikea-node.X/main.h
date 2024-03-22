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

#define IKEA_ADDR_IDENT 0x07
#define IKEA_ADDR_LAYOUT_AMOUNT 0x08
#define IKEA_ADDR_LAYOUT_ORIENTATION 0x09
#define IKEA_ADDR_LAYOUT_LOW_AMOUNT 0x0A
#define IKEA_ADDR_LAYOUT_LOCATION 0x0B

enum IKEA_MODE {
    IKEA_SELECTION_OFF, IKEA_SELECTION_LOW, IKEA_SELECTION_GRADIENT, IKEA_SELECTION_FULL, IKEA_SELECTION_INIT
};
    
#ifdef	__cplusplus
}
#endif

#endif	/* MAIN_H */

