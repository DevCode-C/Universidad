/* 
 * File:   PWMR.c
 * Author: Emmanuel
 *
 * Created on 3 de noviembre de 2018, 09:59 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "config.h"
#include <pic18f4550.h>

/*
 * 
 */
unsigned char adch, adchl;
void main() {
    ADCON1=0b00001110;
    TRISAbits.RA0=1;
    TRISCbits.RC2=0;

    ADCON2=0b00001110;
    ADCON0=0b00000011;

    PR2=0b11111111;
    T2CON=0b00000111;

    CCP1CON=0b00001100;

    CCPR1L=0b00000000; //EL duty
    CCP1CONbits.DC1B1=0;//EL duty
    CCP1CONbits.DC1B0=0;//EL duty

    INTCONbits.GIE=1;
    INTCONbits.PEIE=1;
    RCONbits.IPEN=0;

    PIR1bits.TMR2IF=0;
    IPR1bits.TMR2IP=1;
    PIE1bits.TMR2IE=1;


    while(1){
        while(ADCON0bits.DONE);
        adch=ADRESH;
        adchl=ADRESL;
        ADCON0bits.GO=1;

    }

}

void interrupt interrupciones(){
    if(PIR1bits.TMR2IF==1){
        CCPR1L=adch;
        if(adchl&0x80==0x80)
            CCP1CONbits.DC1B1=1;
        else
            CCP1CONbits.DC1B1=0;
        if(adchl&0x40==0x40)
            CCP1CONbits.DC1B0=1;
        else
            CCP1CONbits.DC1B0=0;

        PIR1bits.TMR2IF=0;
        return;
    }
}