/*
 * File:   Proyecto_SSE_23_05_19.c
 * Author: Emmanuel
 *
 * Created on 23 de mayo de 2019, 01:22 PM
 */
#include "config2.h"
#include <pic18f4550.h>
#define _XTAL_FREQ 12000000
#include "UART.h"
unsigned char datos;
unsigned char envio;
unsigned char tabla[9]={0x47,0x3E,0x0E,0x0E, 0x47,0x05,0x6F,0x6F};
void main(void) {
    ADCON1=0x0F;
    UART_Init(9600);
    TRISB=0x00;
    TRISAbits.TRISA0=0;
    TRISAbits.TRISA1=0;
    TRISAbits.TRISA2=0;
    TRISAbits.TRISA3=0;
    LATB=0x00;
    LATAbits.LATA0=0;
    LATAbits.LATA1=0;
    LATAbits.LATA2=0;
    LATAbits.LATA3=0;
    int count;
    datos=0;
    while(TRUE){
        count=45;
        if(datos==250){
             while(count){
                LATB=tabla[0];
                LATAbits.LATA3=1;
                __delay_ms(5);
                LATAbits.LATA3=0;

                LATB=tabla[1];
                LATAbits.LATA2=1;
                __delay_ms(5);
                LATAbits.LATA2=0;

                LATB=tabla[3];
                LATAbits.LATA1=1;
                __delay_ms(5);
                LATAbits.LATA1=0;

                LATB=tabla[2];
                LATAbits.LATA0=1;
                __delay_ms(5);
                LATAbits.LATA0=0;
                count--;
            }
        }
        else{
            while(count){
                LATB=tabla[4];
                LATAbits.LATA3=1;
                __delay_ms(5);
                LATAbits.LATA3=0;

                LATB=tabla[5];
                LATAbits.LATA2=1;
                __delay_ms(5);
                LATAbits.LATA2=0;

                LATB=tabla[6];
                LATAbits.LATA1=1;
                __delay_ms(5);
                LATAbits.LATA1=0;

                LATB=tabla[7];
                LATAbits.LATA0=1;
                __delay_ms(5);
                LATAbits.LATA0=0;
                count--;
            }
        }
    }
}
void __interrupt() isr(void){
    if(PIR1bits.RCIF==1){
        datos=UART_Rx();
        LATAbits.LA5=1;
        __delay_ms(100);
        PIR1bits.RCIF=0;
    }
    LATAbits.LATA5=0;
    
}
