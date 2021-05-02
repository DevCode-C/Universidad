/*
 * File:   Proyecto_SSE_1.c
 * Author: Emmanuel
 *
 * Created on 15 de abril de 2019, 08:23 PM
 */
#include <pic18f4550.h>
#include "config2.h"
#include <stdio.h>
#define _XTAL_FREQ 12000000
#include "flex_lcd.h"
#include "ADC.h"
#include "Servo.h"
unsigned char palabra[17];
unsigned char ADCS[17],Prom[17];
float x = 0;
short int u;
float Tp[12],Promedio;

void main(void) {
    TRISBbits.RB0 = 1;
    Lcd_Init();
    Lcd_Cmd(LCD_CLEAR);
    Lcd_Cmd(LCD_CURSOR_OFF);
    __delay_ms(100);
    LATD = 0x00;
    PORTBbits.RB0 = 0;
    Servo_init();
    ADC_Init(2);
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
    }

}
void __interrupt() isr(void){
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
