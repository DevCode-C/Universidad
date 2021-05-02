/*
 * File:   Practica10_Servo.c
 * Author: Emmanuel
 *
 * Created on 6 de abril de 2019, 07:23 PM
 */
#include "config2.h"
#include <pic18f4550.h>
#define _XTAL_FREQ 12000000
void main(void) {
    INTCONbits.GIE=0;
    INTCONbits.PEIE = 1;
    INTCONbits.TMR0IE=1;
    INTCONbits.TMR0IF=0;
    T0CONbits.T0CS=0;
    T0CONbits.T0PS=0b111;
    T0CONbits.PSA=0;
    TMR0=21;
    INTCONbits.GIE=1;
    TRISBbits.RB7=1;
    TRISBbits.RB6=1;
    TRISBbits.RB5=1;
    TRISDbits.TRISD2=0;
    LATDbits.LATD2=0;
    PORTBbits.RB7=0;
    PORTBbits.RB6=0;
    PORTBbits.RB5=0;
    while(1){
    }
}

void __interrupt() timer0(void){
    if(INTCONbits.TMR0IF==1){
        if(PORTBbits.RB7==1 && PORTBbits.RB6==1 && PORTBbits.RB5==0){//180 GRADOS
            LATDbits.LATD2=1;
            __delay_ms(1);
            LATDbits.LATD2=0;
            TMR0=33;
            INTCONbits.TMR0IF=0;
        }
        else if(PORTBbits.RB7==1 && PORTBbits.RB6==0 && PORTBbits.RB5==1){
            LATDbits.LATD2=1;
            __delay_ms(1.5);
            LATDbits.LATD2=0;
            TMR0=39;
            INTCONbits.TMR0IF=0;
        }
        else if(PORTBbits.RB7==0 && PORTBbits.RB6==1 && PORTBbits.RB5==1){
            LATDbits.LATD2=1;
            __delay_ms(2);
            LATDbits.LATD2=0;
            TMR0=45;
            INTCONbits.TMR0IF=0;
        }
        else{
            TMR0=21;
            INTCONbits.TMR0IF=0;
        }
    }
}