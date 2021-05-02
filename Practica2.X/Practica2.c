/*
 * File:   Practica2.c
 * Author: Emmanuel
 *
 * Created on 3 de febrero de 2019, 12:02 AM
 */
#include <pic18f4550.h>
#include "config2.h"
#define _XTAL_FREQ 8000000

unsigned int numero1=0;
unsigned int numero2=0;
unsigned int resultado=0;
unsigned int operacion=0;

unsigned int suma();

void main(void) {
    ADCON1=0x0F;
 
 TRISD=0x00;
 TRISB=0xFF;
 
 TRISCbits.TRISC0=1;
 TRISCbits.TRISC1=0;
 TRISCbits.TRISC2=0;


 INICIO:
 LATD=0x00;
 LATB=0x00;
 LATCbits.LATC0=0;
 LATCbits.LATC1=0;   
 
// primer digito
  while(PORTCbits.RC0==1){
        numero1=PORTB;
        LATD=numero1;   
    }
    LATCbits.LATC1=1;
    __delay_ms(500);
    LATD=0x00;
    LATCbits.LATC1=0;
  
  // Segundo digito
  while(PORTCbits.RC0==1){
        numero2=PORTB;
        LATD=numero2;
    } 
     LATCbits.LATC1=1;
     __delay_ms(500);
     LATD=0x00;
     LATCbits.LATC1=0;
  
  
  operacion2:
  // seleccion de la operacion
  while(PORTCbits.RC0==1){
            operacion=PORTB;
            LATCbits.LATC2=1;
    }
        LATCbits.LATC1=1;
        __delay_ms(500);
        LATCbits.LATC1=0;
        LATCbits.LATC2=0;
  
  
 switch(operacion){
        case 1: { 
            
                resultado=numero1+numero2;
                    if(resultado>255){
                        int i;
                        for(i=0;i<=255;i+=10){
                            LATD=i;
                            __delay_ms(100);
                        }
                        goto INICIO;
                    }
                    else {
                        __delay_ms(100);
                        LATD=resultado;
                        __delay_ms(1000);
                        goto INICIO;
                    }
        }
                

        case 2: {resultado=numero1-numero2;
                    
                    while(PORTCbits.RC0==1){LATD=resultado;
                    }}
                    
                    __delay_ms(1000);
                goto INICIO;
        }
            
        case 4: {PORTD=0;break;}
        case 8: {PORTD=0;break;}
        default:{
            LATD=255;
            __delay_ms(1000);
            LATD=0;
            goto operacion2;}
}     