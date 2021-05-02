/* 
 * File:   TecladoMatricial.c
 * Author: Emmanuel
 *
 * Created on 3 de noviembre de 2018, 07:39 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <pic18f4550.h>
#include "config.h"
#include "teclado.h"


void main() {
    char tecla=0;
    teclado_init();
    
    TRISB=0xF0;

    char tecla=0;
    tecla= teclado_getc();
    while(1){
    if(tecla!=0){
        switch(tecla){
            case '1':TRISDbits.RD0=0;break;
            case '2':TRISDbits.RD1=0;break;
            case '3':TRISDbits.RD1=1;break;
            case '4':TRISDbits.RD1=1;break;
            case '5':TRISDbits.RD1=1;break;
            case '6':TRISDbits.RD1=1;break;
            case '7':TRISDbits.RD1=1;break;
            case '8':TRISDbits.RD1=1;break;
            case '9':TRISDbits.RD1=1;break;
            case '*':TRISDbits.RD1=1;break;
            default :TRISD=0xFF;break;

        }
    }
    }
    return;
}

