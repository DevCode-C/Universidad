/* 
 * File:   ADC.c
 * Author: Emmanuel
 *
 * Created on 25 de septiembre de 2018, 07:54 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include "config.h"
#include <pic18f4550.h>


/*
 * 
 */
void main() {

   ADCON1=0b00001110;

   TRISA=0x01;
   TRISD=0x00;

   ADCON2=0b00001110;

   ADCON0=0b00000011;

   while(1){
       while(ADCON0bits.DONE);
       PORTD=ADRESH;

       ADCON0bits.DONE=1;


   }
   
}

