/*
 * File:   Practica2_1.c
 * Author: Emmanuel
 *
 * Created on 3 de febrero de 2019, 05:37 PM
 */
#include "config2.h"
#include <pic18f4550.h>
#define _XTAL_FREQ 8000000

int suma(int s1, int s2);
int resta(int s1, int s2);
int mult(int s1, int s2);
int scv(int s1, int s2);
void main(void) {
    int D1,D2,R0;
    short int SEL;
    TRISD=0x00;//Declaración de puertos
    TRISB=0xFF;
    TRISCbits.RC0=1;
    TRISCbits.RC1=0;
    TRISCbits.RC2=0;
    INICIO://EL REGRESO CON GOTO
    LATD=0x00;
    LATB=0x00;
    LATCbits.LATC0=0;
    LATCbits.LATC1=0;
    LATCbits.LATC2=0;
    //SELECCIÓN DEL PRIMER DIGITO
    while(PORTCbits.RC0==1){
        D1=PORTB;
        LATD=D1;
    }
    LATCbits.LATC1=1;
    __delay_ms(500);
    LATD=0x00;
    LATCbits.LATC1=0;
    //SELECCIÓN DE SEGUNDO DIGITO
    while(PORTCbits.RC0==1){
        D2=PORTB;
        LATD=D2;
    }
    LATCbits.LATC1=1;
    __delay_ms(500);
    LATD=0x00;
    LATCbits.LATC1=0;
    SELECCION:
    while(PORTCbits.RC0==1){
        LATCbits.LATC2=1;
        SEL=PORTB;
    }
    LATCbits.LATC1=1;
    __delay_ms(500);
    LATCbits.LATC1=0;
    LATCbits.LATC2=0;
    switch(SEL){
        case 1: {R0=suma(D1,D2);
            if(R0>255){
                int i;
                for(i=0;i<255;i+=10){
                    PORTD=i;
                    __delay_ms(100);
                }
                goto INICIO;
            }
            else{PORTD=R0; goto INICIO;}
        }
    }
}
int suma(int s1, int s2){
    int x=0;
    x=s1+s2;
    return x;

}