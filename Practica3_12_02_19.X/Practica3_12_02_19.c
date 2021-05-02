/*
 * File:   Practica3_12_02_19.c
 * Author: Emmanuel
 *
 * Created on 10 de febrero de 2019, 09:13 PM
 */

#include "config2.h"
#include <pic18f4550.h>
#define _XTAL_FREQ 8000000

unsigned char Nombre[]={0x4F,0x15,0x15,0x77,0x15,0x3E,0x4F,0x0E};
unsigned char codigo[]={0x6D,0x06,0x5B,0x7E,0x7F,0x79,0x06,0x5F,0x5F};
unsigned char sorpresa[]={0x40,0x60,0x70,0x78,0x7C,0x7E};
void main(void){
    TRISD=0x00;
    TRISBbits.TRISB0=1;
    TRISBbits.TRISB1=1;
    TRISBbits.TRISB2=1;        
    short int contador;
    short int sel=0;
    short int out=0;
    PORTBbits.RB0=0;
    PORTBbits.RB1=0;
    PORTBbits.RB2=0;
    PORTD=0x00;


    while(1){
        if(PORTBbits.RB0==0 && PORTBbits.RB1==1 && PORTBbits.RB2==1){sel=1;}
        if(PORTBbits.RB0==1 && PORTBbits.RB1==0 && PORTBbits.RB2==1){sel=2;}
        if(PORTBbits.RB0==1 && PORTBbits.RB1==1 && PORTBbits.RB2==0){sel=3;}
        switch(sel){
            case 1: {out=0;
                while(1){
                    for(contador=0;contador<8;contador++){
                        PORTD=Nombre[contador];
                        __delay_ms(1000);
                        if(PORTBbits.RB0==1 && PORTBbits.RB1==0 && PORTBbits.RB2==1){
                            sel=2;
                            out=1;
                            break;
                        }
                        if(PORTBbits.RB0==1 && PORTBbits.RB1==1 && PORTBbits.RB2==0){
                            sel=3;
                            out=1;
                            break;
                        }   
                    }if(out==1)break;
                    
                }break;
            }
            case 2: {out=0;
                while(1){sel=0;
                    for(contador=0;contador<9;contador++){
                        PORTD=codigo[contador];
                        __delay_ms(1000);
                        if(PORTBbits.RB0==0 && PORTBbits.RB1==1 && PORTBbits.RB2==1){
                            sel=1;
                            out=1;
                            break;
                        }
                        if(PORTBbits.RB0==1 && PORTBbits.RB1==1 && PORTBbits.RB2==0){
                            sel=3;
                            out=1;
                            break;
                        }   
                    }if(out==1)break;
                }   
            }
            case 3: {out=0;
                while(1){
                    for(contador=0;contador<6;contador++){
                        PORTD=sorpresa[contador];
                        __delay_ms(500);
                        if(PORTBbits.RB0==0 && PORTBbits.RB1==1 && PORTBbits.RB2==1){
                            sel=1;
                            out=1;
                            break;
                        }
                        if(PORTBbits.RB0==1 && PORTBbits.RB1==0 && PORTBbits.RB2==1){
                            sel=2;
                            out=1;
                            break;
                        }   
                    }if(out==1)break;
                }
            }
        }
    }
}

