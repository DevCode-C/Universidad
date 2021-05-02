/*
 * File:   Practica10_05_04_19.c
 * Author: Emmanuel
 *
 * Created on 5 de abril de 2019, 10:17 PM
 */

#include "config2.h"
#include <pic18f4550.h>
#include <stdio.h>
#define _XTAL_FREQ 12000000
#include "flex_lcd.h"
void teclado(void);
void InitKeyboar(void);
void main(void) {
    OSCCONbits.SCS=0b00;
    ADCON1=0x0F;
    //Inicio();
    TRISCbits.TRISC2=0;
    CCP1CON=0x0C;
    PR2=187;
    T2CON=0b00000111;
     T2CONbits.TOUTPS=0b0011;
    CCPR1L=0x00;
    CCP1CONbits.DC1B1=0;
    CCP1CONbits.DC1B0=0;
    while(1){
       //
    CCPR1L=0b01011101;
    CCP1CONbits.DC1B1=1;
    CCP1CONbits.DC1B0=1;
        // teclado();
    }
   
}
