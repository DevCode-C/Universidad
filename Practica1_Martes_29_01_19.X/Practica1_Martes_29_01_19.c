/*
 * File:   Practica1_Martes_29_01_19.c
 * Author: Emmanuel
 *
 * Created on 28 de enero de 2019, 07:34 PM
 */
#include <pic18f4550.h>
#include "Config1.h"
#include <stdio.h>
#include <stdlib.h>
#define _XTAL_FREQ 8000000

void main(void) {
    ADCON1=0b00001111;
    TRISD=0x00;
    LATD=0x00;
 
    TRISCbits.RC2=0;
    CCP1CON=0x0C;
    PR2=62;
    T2CON=0x07;
    CCPR1L=0x00;
    CCP1CONbits.DC1B1=0;
    CCP1CONbits.DC1B0=0;
    while(1){
        short int i;
        for(i=0;i<=62;i+=6){
            __delay_ms(300);
            CCPR1L=i;
            CCP1CONbits.DC1B1=1;
            CCP1CONbits.DC1B0=1;
            //__delay_ms(100);
            LATD=i;
        
        
        }
    
    
    
    }
}






 /*  while(1){
        LATD=0x00;
        __delay_ms(100);
        LATD=0xFF;
        __delay_ms(100);
    
    }
  */