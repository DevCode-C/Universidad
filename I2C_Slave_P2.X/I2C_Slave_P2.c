/*
 * File:   I2C_Slave_P2.c
 * Author: Emmanuel
 *
 * Created on 6 de mayo de 2019, 05:18 PM
 */
#include <pic16f887.h>
#include "Config_16F.h"
#define _XTAL_FREQ 12000000
#include "I2C_Slave.h"
void teclado(void);//Prototipo de la función teclado
unsigned char valor;//Variable para el teclado matricial
unsigned char caracter;//Variable para paso de la viariable "valor" a la variable "caracter"
short int input, output, temp, temp_c;
void main(void) {
    I2C_Slave_Init(0x20);
    ANSEL=0x00;
    ANSELH=0x00;
    OPTION_REG=1;
    TRISB=0xF0;
    PORTB=0x00;
    TRISEbits.TRISE0=0;
    TRISEbits.TRISE1=0;
    TRISEbits.TRISE2=1;
    RE0=0;RE1=0;RE2=0;
    PORTEbits.RE2=1;
    while(TRUE){
        switch(input){
            case 0x01:{
                if(PORTEbits.RE2==1){
                    while(valor != '*'){
                        teclado();
                        if(valor == '1' || valor== '2' || valor== '3'){
                            output=valor;
                        }
                    }
                    while(PORTEbits.RE2==1){
                        PORTEbits.RE0=1;
                        PORTEbits.RE1=1;
                    }
                }
                output=0;PORTEbits.RE0=0;PORTEbits.RE1=0;input=0;valor=0;
                break;
            }
//            case 0x02:{
//                if(PORTEbits.RE2==1){temp_c=0;
//                    while(valor != '*'){
//                        teclado();
//                       if((valor >= '0') && (valor <= '9')){
//                            temp_c+=valor;
//                            output=temp_c;
//                        }
//                    }
//                    if(valor=='*'){
//                        PORTEbits.RE0=1;
//                        PORTEbits.RE1=1;
//                    }
//                }
//                break;
//            }
        }
    }
}

void teclado(void){//Función teclado
    valor=0;
    PORTB=0xF0;
    if(PORTB != 0xF0){
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
    }
    PORTB = 0xF0;
    while (PORTB != 0xF0);
}
void __interrupt() isr(void){
    if(SSPIF == 1){
       SSPCONbits.CKP = 0;
       if((SSPCONbits.SSPOV) || (SSPCONbits.WCOL)){
            temp = SSPBUF;            
            SSPCONbits.SSPOV = 0; 
            SSPCONbits.WCOL = 0;   
            SSPCONbits.CKP = 1;
        }
        if(!SSPSTATbits.D_nA && !SSPSTATbits.R_nW) {
            temp = SSPBUF;
            while(!BF);
            input = SSPBUF;
            SSPCONbits.CKP = 1;
            SSPM3 = 0;
        }
        else if(!SSPSTATbits.D_nA && SSPSTATbits.R_nW){
            temp = SSPBUF;
            BF = 0;
            SSPBUF = output ;
            SSPCONbits.CKP = 1;
            while(SSPSTATbits.BF);
        }
       
       SSPIF = 0;
    }

}