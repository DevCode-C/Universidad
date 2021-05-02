/*
 * File:   Servo.c
 * Author: Emmanuel
 *
 * Created on 19 de abril de 2019, 11:52 PM
 */
#include "config2.h"
#include <pic18f4550.h>
#define _XTAL_FREQ 12000000

void Servo_init(void);
void Servo_init(void){
    INTCONbits.GIE=0;
    INTCONbits.PEIE = 1;
    INTCONbits.TMR0IE=1;
    INTCONbits.TMR0IF=0;
    T0CONbits.T0CS=0;
    T0CONbits.T0PS=0b111;
    T0CONbits.PSA=0;
    TMR0=21;
    INTCONbits.GIE=1;
}

