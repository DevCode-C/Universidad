/*
 * File:   I2C_Master.c
 * Author: Emmanuel
 *
 * Created on 23 de abril de 2019, 03:23 PM
 */
#include "config2.h"
#define _XTAL_FREQ 12000000
#include <pic18f4550.h>
#include <stdio.h>
#include "I2C_Master.h"
#include "flex_lcd.h"

unsigned char palabra[17],Palabra1[17];
float valor=0;
short int contador=0;
void main(void) {
    ADCON1=0x0F;
    INTCONbits.GIE=1;
    INTCONbits.PEIE_GIEL=1;
    INTEDG2=0;
    INT2IE=1;
    INT2IF=0;
    TRISBbits.TRISB2=1;
    PORTBbits.INT2=0;
    TRISC=0x00;
    LATC=0x00;
    TRISAbits.TRISA0=1; TRISAbits.TRISA1=1; TRISAbits.TRISA2=1;
    PORTAbits.RA0=0; PORTAbits.RA1=0; PORTAbits.RA2=0;
    I2C_Master_Init(100000);
    Lcd_Init();
    Lcd_Cmd(LCD_CLEAR);
    Lcd_Cmd(LCD_CURSOR_OFF);
    __delay_ms(100);
    while(1){
        Lcd_Out(1,1,"Hola mundo");
    }
    
}
void __interrupt() interru(void){
    if(INT2F==1){
        if(contador==0){
            I2C_Master_Start();
            I2C_Master_Write(0x00);
            I2C_Master_Write(0x01);
            I2C_Master_Stop();
            __delay_ms(200);
            contador++;
        }
        else if(contador==1){
            I2C_Master_Start();
            I2C_Master_Write(0x00);
            I2C_Master_Write(0x02);
            I2C_Master_Stop();
            __delay_ms(200);
            contador++;
        }
        else if(contador==2){
            I2C_Master_Start();
            I2C_Master_Write(0x00);
            I2C_Master_Write(0x03);
            I2C_Master_Stop();
            __delay_ms(200);
            contador++;
            if(contador==3){
                contador=0;
            }
        }
        INT2F=0;
    }
}
