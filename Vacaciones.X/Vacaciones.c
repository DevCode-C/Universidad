/* 
 * File:   Vacaciones.c
 * Author: Emmanuel
 *
 * Created on 28 de diciembre de 2018, 04:47 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "config.h"
#include <pic18f4550.h>

/*
 * 
 */
void main() {
    ADCON1=0x0F;
    TRISD=0x00;
    PORTD=0XFF;
    
    while(1);
}

