/* 
 * File:   uartss.c
 * Author: Emmanuel
 *
 * Created on 30 de octubre de 2018, 08:17 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <pic18f4550.h>
#include "config.h"

/*
 * 
 */
void main() {
    //Configuramos puertos como digitales
    ADCON1=0b00001111;
    //Puerto D como salida
    TRISD=0b00000000;
    //Configuramos los pines de TX y RX
    TRISCbits.RC7=1; //RX
    TRISCbits.RC6=0; //TX

    //Configuramos en modulo USART
    //Configuramos la trasmisiión

    //0b0xxxxxxx; No importa, dado que se usa comunicación asincrona
    //0bx0xxxxxx; Se usara una comunicacion de 8 bits
    //0bxx1xxxx; Se habilita la transmision
    //0bxxx0xxxx; Se usara modo asincrono
    //0bxxxx0xxx; Sin byte de terminacion
    //0bxxxxx0xx; Baja velocidad de comunicacion
    //Los demas bits son de lectura
    TXSTA=0b00100000;
    //Se usara solo 8 bits para configurar el baud rate
    BAUDCONbits.BRG16=0;
    //Configuramos el baud rate a 9600 baudios
    SPBRG=77;



    RCSTA=0b10010000;

    while(1){

        while(!PIR1bits.RCIF);
        PORTD=RCREG;

        while(!TXSTAbits.TRMT);

        TXREG=PORTD +1;

    }
  
}

