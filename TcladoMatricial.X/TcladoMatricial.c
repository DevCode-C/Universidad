/* 
 * File:   TcladoMatricial.c
 * Author: Emmanuel
 *
 * Created on 7 de noviembre de 2018, 11:58 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <pic18f4550.h>
#include "config.h"


/*
 * 
 */
void PWM(){

}

 unsigned char lectura(){
    unsigned char valor='0';
    PORTB=0xFE;
        if(PORTBbits.RB4==0){valor = '*';}
        if(PORTBbits.RB5==0){valor = '0';}
        if(PORTBbits.RB6==0){valor = '#';}
        if(PORTBbits.RB7==0){valor = 'D';}
    PORTB=0xFD;
        if(PORTBbits.RB4==0){valor = '7';}
        if(PORTBbits.RB5==0){valor = '8';}
        if(PORTBbits.RB6==0){valor = '9';}
        if(PORTBbits.RB7==0){valor = 'C';}
    PORTB=0xFB;
        if(PORTBbits.RB4==0){valor = '4';}
        if(PORTBbits.RB5==0){valor = '5';}
        if(PORTBbits.RB6==0){valor = '6';}
        if(PORTBbits.RB7==0){valor = 'B';}
    PORTB=0xF7;
        if(PORTBbits.RB4==0){valor = '1';}
        if(PORTBbits.RB5==0){valor = '2';}
        if(PORTBbits.RB6==0){valor = '3';}
        if(PORTBbits.RB7==0){valor = 'A';}
    return valor;
}

 
 void main() {
    //TECLADO
    unsigned char dato = 0;
    ADCON2=0b00001110;
    ADCON0=0b00000000;
    INTCON2bits.RBPU=0;
    TRISB=0xF0;
    TRISD=0x00;
    //PWM Puerto 17 CCP1
    PR2=0x05;
    TRISCbits.RC2=0;
    CCP1CON=0x0C;
    T2CON=0x07;
    CCPR1L=0x00;
    CCP1CONbits.DC1B1=0;
    CCP1CONbits.DC1B0=0;


    //PWM Puerto 16 CCP2
    
     //dato = lectura();

     while(1){
         dato = lectura();
         switch(dato){
             case '1' : {PORTD=0x01;
                        CCPR1L=0x00;
                        CCP1CONbits.DC1B1=1;
                        CCP1CONbits.DC1B0=1;
                        }
             break;

             case '2' : {PORTD=0x02;
                        CCPR1L=0x01;
                        CCP1CONbits.DC1B1=0;
                        CCP1CONbits.DC1B0=1;}
             break;

             case '3' : {PORTD=0x03;
                        CCPR1L=0x02;
                        CCP1CONbits.DC1B1=0;
                        CCP1CONbits.DC1B0=0;}
             break;

             case '4' : {PORTD=0x04;
                        CCPR1L=0x02;
                        CCP1CONbits.DC1B1=1;
                        CCP1CONbits.DC1B0=0;}
             break;

             case '5' : {PORTD=0x05;
                        CCPR1L=0x03;
                        CCP1CONbits.DC1B1=0;
                        CCP1CONbits.DC1B0=1;}
             break;

             case '6' : {PORTD=0x06;
                        CCPR1L=0x03;
                        CCP1CONbits.DC1B1=1;
                        CCP1CONbits.DC1B0=1;}
             break;

             case '7' : {PORTD=0x07;
                        CCPR1L=0x04;
                        CCP1CONbits.DC1B1=1;
                        CCP1CONbits.DC1B0=0;}
             break;

             case '8' : {PORTD=0x08;
                        CCPR1L=0x05;
                        CCP1CONbits.DC1B1=0;
                        CCP1CONbits.DC1B0=0;}
             break;

             case '9' : {PORTD=0x09;
                        CCPR1L=0x05;
                        CCP1CONbits.DC1B1=1;
                        CCP1CONbits.DC1B0=1;}
             break;

             case 'A' : {PORTD=0x0A;
                        CCPR1L=0x00;
                        CCP1CONbits.DC1B1=0;
                        CCP1CONbits.DC1B0=0;}
             break;

             case 'B' : {PORTD=0x0B;}
             break;
         }
     }
   
}

