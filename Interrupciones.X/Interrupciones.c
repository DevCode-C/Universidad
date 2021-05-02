/* 
 * File:   Interrupciones.c
 * Author: Emmanuel
 *
 * Created on 13 de septiembre de 2018, 08:06 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <pic18f4550.h>
#include "Interrupciones.h"

/*
 * 
 */

void main() {
    ADCON1=0b00001111;
    TRISB=0b00000011;
    TRISD=0b00000000;
    PORTD=0b11000011;
    INTCON2bits.INTEDG0=0;
    INTCON2bits.INTEDG1=0;
    INTCONbits.INT0E=1;
    INTCON3bits.INT1IE=1;
    INTCON3bits.INT1IP=1;
    INTCONbits.GIE=1;
    INTCONbits.PEIE=1;
    RCONbits.IPEN=0;

    while(1){
    }
    
}

void Interrupciones(){
    if(INTCONbits.INT0IF==1){
        PORTD=0b00111100;
        INTCONbits.INT0IF=0;
        return;
    }
    if(INTCON3bits.INT1F==1){
        PORTD=0b10101010;
        INTCON3bits.INT1F=0;
        return;
    }


}

