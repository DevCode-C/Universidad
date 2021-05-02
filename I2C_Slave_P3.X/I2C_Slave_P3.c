/*
 * File:   I2C_Slave_P3.c
 * Author: Emmanuel
 *
 * Created on 10 de mayo de 2019, 11:18 PM
 */
#include "config2.h"
#include <pic18f4550.h>
#define _XTAL_FREQ 12000000
#include "I2C_Slave.h"
unsigned char nor[6],Jac[6],Mas[6];
short int input,output,temp;
void normal_Suite(int Vector);
void jacuzzi_Suite(int Vector);
void master_Suite(int Vector);
void main(void) {
    I2C_Slave_Init(0x30);
    ADCON1=0x0F;
    while(1){
    }
}
void __interrupt() isr(void){
    if(SSPIF == 1){
       SSPCON1bits.CKP = 0;
       if((SSPCON1bits.SSPOV) || (SSPCON1bits.WCOL)){
            temp = SSPBUF;            
            SSPCON1bits.SSPOV = 0; 
            SSPCON1bits.WCOL = 0;   
            SSPCON1bits.CKP = 1;
        }
        if(!SSPSTATbits.D_nA && !SSPSTATbits.R_nW) {
            temp = SSPBUF;
            while(!BF);
            input = SSPBUF;
            SSPCON1bits.CKP = 1;
            SSPM3 = 0;
        }
        else if(!SSPSTATbits.D_nA && SSPSTATbits.R_nW){
            temp = SSPBUF;
            BF = 0;
            SSPBUF = output ;
            SSPCON1bits.CKP = 1;
            while(SSPSTATbits.BF);
        }
       
       SSPIF = 0;
    }
}
void Normal(int Vector){
    
}