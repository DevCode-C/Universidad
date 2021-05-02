/* 
 * File:   jueves.c
 * Author: Emmanuel
 *
 * Created on 6 de septiembre de 2018, 07:49 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <pic18f4550.h>
#include "config.h"



void main() {
    ADCON1=0b00001111;

    TRISB=0b11111111;

    TRISD=0b00000000;

    while(1){
        PORTD=PORTB;
    }

}

