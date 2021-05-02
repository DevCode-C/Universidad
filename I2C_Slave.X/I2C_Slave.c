/*
 * File:   I2C_Slave.c
 * Author: Emmanuel
 *
 * Created on 23 de abril de 2019, 04:07 PM
 */

#include "config2.h"
#include <pic18f4550.h>
#define _XTAL_FREQ 12000000
#include <stdio.h>
#include "flex_lcd.h"
#include "I2C_Slave.h"
#include "ADC.h"
#include "Servo.h"
short z;
short int i,u;
unsigned char palabra[17];
unsigned char ADCS[17],Prom[17];
float datos=0x00;;
float Tp[12],Promedio;

void main(void) {
    //Interrupt_Prior(0);
    I2C_Slave_Init(0x10);
    Servo_init();
    ADC_Init(2);
    Lcd_Init();
    Lcd_Cmd(LCD_CLEAR);
    Lcd_Cmd(LCD_CURSOR_OFF);
    __delay_ms(100);
    LATD = 0x00;
    TRISCbits.TRISC0=0;
    TRISCbits.TRISC1=0;
    LATCbits.LATC0=0;
    LATCbits.LATC1=0;
    Promedio=0.0;
     while (1) {
         for(u=0;u<=1;u++){
            Tp[u]=ADC_Channel(u);
            Promedio=Promedio+Tp[u];
            __delay_ms(3);
        }
        Promedio=Promedio/3.0;
        sprintf(Prom,"%.3f",Promedio);
        Lcd_Out(1,1,"Temperatura:");
        Lcd_Out2(2,1,Prom);
        while(datos!=0x00){
            if(datos==0x15){
                Lcd_Cmd(LCD_CLEAR);
                __delay_ms(100);
                while(datos==0x15){
                    Lcd_Out(1,1,"Sin salida");
                }
            }
            else if(datos==0x14){
                Lcd_Cmd(LCD_CLEAR);
                __delay_ms(100);
                while(datos==0x14){
                    Lcd_Out(1,1,"Sin salida 1");
                }
            }
            else if(datos==0x13){
                Lcd_Cmd(LCD_CLEAR);
                __delay_ms(100);
                while(datos==0x13){
                    Lcd_Out(1,1,"Sin salida 2");
                }
            }
        }    
    }
}
void __interrupt() I2C_Slave_Read(){ 
    if(SSPIF == 1){
       SSPCON1bits.CKP = 0;
       if ((SSPCON1bits.SSPOV) || (SSPCON1bits.WCOL)){
             z = SSPBUF;            
             SSPCON1bits.SSPOV = 0; 
             SSPCON1bits.WCOL = 0;   
             SSPCON1bits.CKP = 1;
        }
        if(!SSPSTATbits.D_nA && !SSPSTATbits.R_nW) {
           z = SSPBUF;
           while(!BF);
           datos = SSPBUF;
           SSPCON1bits.CKP = 1;
           SSPM3 = 0;
        }
        else if(!SSPSTATbits.D_nA && SSPSTATbits.R_nW){
           z = SSPBUF;
           BF = 0;
           SSPBUF = Promedio ;
           SSPCON1bits.CKP = 1;
           while(SSPSTATbits.BF);
        }
       
       SSPIF = 0;
    }
    if(INTCONbits.TMR0IF==1){
        if(Tp[0]>2.5){
            LATCbits.LATC0=1;
            __delay_ms(2);
            LATCbits.LATC0=0;
            TMR0=45;
            INTCONbits.TMR0IF=0;
        }
        if(Tp[0]<2.5){
            LATCbits.LATC0=1;
            __delay_ms(1);
            LATCbits.LATC0=0;
            TMR0=33;
            INTCONbits.TMR0IF=0;
        }
        if(Tp[1]>2.5){
            LATCbits.LATC1=1;
            __delay_ms(1);
            LATCbits.LATC1=0;
            TMR0=33;
            INTCONbits.TMR0IF=0;
        }if(Tp[1]<2.5){
            LATCbits.LATC1=1;
            __delay_ms(2);
            LATCbits.LATC1=0;
            TMR0=45;
            INTCONbits.TMR0IF=0;
        }else{
            TMR0=21;
            INTCONbits.TMR0IF=0;
        }
    }
}