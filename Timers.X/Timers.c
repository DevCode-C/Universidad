/* 
 * File:   Timers.c
 * Author: Emmanuel
 *
 * Created on 4 de octubre de 2018, 07:48 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include "config.h"
#include <pic18f4550.h>

/*
 * 
 */
void interrupt interrupcione();
void main() {
    ADCON1=0b00001111;
    TRISD=0b00000000;
    PORTD=0b00000000;

    TMR0H=0x48;
    TMR0L=0xE5;

    T0CON=0b10010111;

    INTCONbits.GIE=1;
    INTCONbits.PEIE=1;
    RCONbits.IPEN=0;
    INTCONbits.T0IF=0;
    INTCON2bits.T0IP=1;
    INTCONbits.T0IE=1;

    while(1){
    }
}
void interrupt interrupcione(){
    if(INTCONbits.TMR0IF==1){
        PORTD +=1;
        TMR0H=0x48;
        TMR0L=0xE5;
        INTCONbits.TMR0IF=0;
        return;

    }


}

