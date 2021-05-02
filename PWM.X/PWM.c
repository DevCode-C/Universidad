/* 
 * File:   PWM.c
 * Author: Emmanuel
 *
 * Created on 18 de octubre de 2018, 07:56 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include "config.h"
#include <pic18f4550.h>

/*
 * 
 */
unsigned char adch,adc1;

void main() {
    //Configuración de los puertos
    ADCON1=0b00001110;
    //Configurar elpuerto AN0 como entrada analogica
    TRISAbits.RA0=1;
    //Configurar RC2 como salida
    TRISCbits.RC2=0;
    //Configuramos el modulo ADC
    ADCON2=0b00001110;
    ADCON0=0b00000011;

    //Cantidad de pulsos necesarios para desbordar el timer 256
    PR2=0b11111111;

    T2CON=0b00000111;
    CCP1CON=0b00001100;

    CCPR1L=0b00000000;
    CCP1CONbits.DC1B1;
    CCP1CONbits.DC1B0;


    INTCONbits.GIE=1;
    INTCONbits.PEIE=1;

    RCONbits.IPEN=0;

    PIR1bits.TMR2IF=0;
    IPR1bits.TMR2IP=1;
    PIE1bits.TMR2IE=1;

    while(1){
        while(ADCON0bits.DONE);
        adch=ADRESH;
        adc1=ADRESL;


        ADCON0bits.GO=1;
    }



}
void interrupciones(){
    if(PIR1bits.TMR2IF==1){
        CCPR1L=adch;
        if(adc1&0x80==0x80)
            CCP1CONbits.DC1B1=1;
        else
            CCP1CONbits.DC1B1=0;
        if(adc1&0x40==0x40)
            CCP1CONbits.DC1B0=1;
        else
            CCP1CONbits.DC1B0=0;

        PIR1bits.TMR2IF=0;
        return;

    }






}
