/*
 * File:   Practica4_14_02_19.c
 * Author: Emmanuel
 *
 * Created on 13 de febrero de 2019, 04:49 PM
 */
#include "config2.h"
#include <pic18f4550.h>
#include <stdio.h>
#include <stdlib.h>
#define _XTAL_FREQ 8000000
unsigned char dig[]={0,1,2,3,4,5,6,7,8,9};
unsigned int counter;
unsigned int cuenta;

static void interrupt timer0(void){ 
    if(INTCONbits.TMR0IF==1){
        INTCONbits.TMR0IF=0;
        TMR0=60;
        if(counter==40){
            cuenta++;
            PORTD=dig[cuenta];
            if(cuenta==9){
                cuenta=0;
            }
            counter=0;
        }
    }
  return;  
}
void main(void) {
    ADCON1=0x0F;
    TRISD=0x00;
    TRISCbits.RC0=0;
    TRISCbits.RC1=0;
    RCONbits.IPEN=0;
    T0CON=0b11010111;
    
    TMR0=60;
    INTCONbits.GIE=1;
    INTCONbits.TMR0IE=1;
    INTCONbits.TMR0IF=0;
    PORTD=0x00;
    cuenta=0;
    PORTD=dig[cuenta];
    while(1);
}
