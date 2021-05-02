/* 
 * File:   PWMCristrian.c
 * Author: Emmanuel
 *
 * Created on 15 de noviembre de 2018, 08:32 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <pic18f4550.h>
#include "config.h"

/*
 * 
 */
void main() {

    ADCON2=0b00001110;
    ADCON0=0b00000000;

    //PWM Puerto 17 CCP1
    PR2=0x61;
    TRISCbits.RC2=0;
    CCP1CON=0x0C;
    T2CON=0x07;

    CCPR1L=0x29;

    CCP1CONbits.DC1B1=0;
    CCP1CONbits.DC1B0=0;

    while(1);
}

