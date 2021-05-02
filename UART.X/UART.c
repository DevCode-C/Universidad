/* 
 * File:   UART.c
 * Author: Emmanuel
 *
 * Created on 22 de octubre de 2018, 09:43 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <pic18f4550.h>
#include "config.h"

/*
 * 
 */
void main() {
    ADCON1=0b00001111;

    TRISD=0b00000000;
    TRISCbits.RC7=1;
    TRISCbits.RC6=0;

    TXSTA=0b00000000;
    BAUDCONbits.BRG16=0;
    SPBRG=77;

    RCSTA=0b10010000;

    while(1){
        while(!PIR1bits.RCIF);

        PORTD=RCREG;

    while(!TXSTAbits.TRMT);

    TXREG=PORTD+1;

    }


}

