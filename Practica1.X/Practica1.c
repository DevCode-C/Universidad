/*
 * File:   Practica1.c
 * Author: Emmanuel
 *
 * Created on 26 de enero de 2019, 06:25 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <pic18f4550.h>
#include "configuracion_1.h"
#define _XTAL_FREQ 12000000
 
void main(void) {
    ADCON1=0x0F;
    TRISDbits.TRISD0=0;
    LATDbits.LATD0=0;
    while(1){
        LATDbits.LATD0=~LATDbits.LATD0;
        __delay_ms(500);
    }
}
