/*
 * File:   Practica4.c
 * Author: Emmanuel
 *
 * Created on 16 de febrero de 2019, 09:00 PM
 */
#include "Config1.h"
#include <pic18f4550.h>
#define _XTAL_FREQ 8000000
void puertos(){
    ADCON1=0x0F;
    TRISD=0x00;
    TRISAbits.RA0=0;
    TRISAbits.RA1=0;
    TRISAbits.RA2=0;
    TRISAbits.RA3=0;
    TRISBbits.RB0=1;
    TRISBbits.RB1=1;
    TRISBbits.RB2=1;
    TRISBbits.RB3=1;
}
void timer(){
    INTCONbits.GIE=0;
    T0CONbits.T08BIT=1;
    T0CONbits.T0CS=0;
    T0CONbits.T0SE=0;
    T0CONbits.T0PS=0b111;
    T0CONbits.TMR0ON=1;
    T0CONbits.PSA=0;
    INTCONbits.TMR0IE=1;
    INTCONbits.TMR0IF=0;
    INTCONbits.PEIE=1;
    INTCONbits.GIE=1;
}
long int cont=0;
short int cont1=9;
int numero[]={0x7E,0x30,0x6D,0x79,0x3B,0x5B,0x5F,0x71,0xFF,0xF3};
void main(void) {
    puertos();
    timer();
    TMR0=60;
    PORTD=0;
    while(1);
    
}
void __interrupt() tcInt(void){
    if(INTCONbits.TMR0IF==1){
        
        TMR0=60;
        INTCONbits.TMR0IF=0;
        cont++;
        if(cont==40){         
            PORTD=numero[cont1];
            cont1--;  
            if(cont1<0){
                cont1=9;
                
            }
            cont=0;
        }
    }
}