/*
 * File:   Practica7_Interrupciones.c
 * Author: Emmanuel
 *
 * Created on 30 de abril de 2019, 03:57 PM
 */
#include "config2.h"
#include <pic18f4550.h>
#define _XTAL_FREQ 8000000
#include <math.h>
#include <stdio.h>
short int num=2;
void main(void) {
    ADCON1=0x0F;
    TRISD=0x00;
    TRISBbits.TRISB0=1;
    TRISBbits.TRISB1=1;
    TRISBbits.TRISB7=0;
    INTCONbits.GIE=1;
    RCONbits.IPEN=1;
    INTCONbits.GIEH=1;
    INTCONbits.GIEL=1;
    INTCONbits.INT0E=1;
    INTCONbits.INT0F=0;
    INTCON3bits.INT1E=1;
    INTCON3bits.INT1F=0;
    INTCON3bits.INT1IP=0;
    INTCON2bits.INTEDG0=0;
    INTCON2bits.INTEDG1=0;
    LATD=0x00;
    int sal=0;
    while(1){
        for(int i =0;i<8;i++){
            sal=pow(num,i);
            LATD=sal;
            __delay_ms(400);
        }
    }
}
void __interrupt(high_priority) isr(void){
    int sal=0;
    if(INTCONbits.INT0IF==1){
        INTCONbits.INT0F=0;
        int i=0;
        LATD=0;
        while(PORTBbits.RB0==0){
            for(i=7;i>=0;i--){
                sal=pow(num,i);
                LATD=sal;
                __delay_ms(400);
                if(PORTBbits.RB0==1){
                    break;
                    LATD=0x00;
                }
            }
        }
        LATD=0x00;
    }
}
void __interrupt(low_priority) lwp(void){
    if(INTCON3bits.INT1F==1){
        INTCON3bits.INT1F=0;
        int i=0;
        LATD=0;
        while(PORTBbits.RB1==0){
            LATD=0x0F;
            __delay_ms(300);
            LATD=0xF0;
            __delay_ms(300);
        }
        LATD=0x00;
    }
}