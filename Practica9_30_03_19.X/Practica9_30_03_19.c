/*
 * File:   Practica9_30_03_19.c
 * Author: Emmanuel
 *
 * Created on 30 de marzo de 2019, 06:47 PM
 */
#include "config2.h"
#include <pic18f4510.h>
#include <stdio.h>
#define _XTAL_FREQ 12000000
#include "flex_lcd.h"
#define LED1 LATAbits.LA2
#define LED2 LATAbits.LA3
#define Rele1 LATCbits.LC1
#define Rele2 LATCbits.LC6
float adc;
float conver;
float max;
float min;
unsigned long valor;
unsigned char palabra[17];
unsigned char palabra0[17];
unsigned char palabra1[17];
unsigned char palabra2[17];
void teclado(void);
void main(void) {
     
    TRISAbits.TRISA0=1;
    TRISAbits.RA2=0;
    TRISAbits.RA3=0;
    TRISCbits.RC1=0;
    TRISCbits.RC6=0;
    ADCON1=0b00001110;
    ADCON0bits.CHS=0;
    ADCON2bits.ADFM=1;
    ADCON2bits.ADCS=0b010;
    ADCON2bits.ACQT=0b101;
    ADCON0bits.ADON=1;
    float caracter;
    Rele1=0;Rele2=0;LED1=0;LED2=0;
    Lcd_Init();
    Lcd_Cmd(LCD_CLEAR);
    Lcd_Cmd(LCD_CURSOR_OFF);
    __delay_ms(100);
    Lcd_Out(1,3,"Bienvenido");
    Lcd_Out(2,5,"Humano");
    __delay_ms(2000);
    Lcd_Cmd(LCD_CLEAR);
    __delay_ms(100);
    volver:
    Lcd_Out(1,1,"Seleccione el");
    Lcd_Out(2,1,"limite Superior");
    __delay_ms(2000);
    Lcd_Cmd(LCD_CLEAR);
    __delay_ms(100);
    caracter=0;valor=0;min=0;max=0;
    while(valor != '*'){
        Lcd_Out(1,1,"XP Temp MAX XP");
        teclado();
        if((valor >= '0') && (valor <= '9')){
        caracter=caracter*10+(valor-48);
        max=caracter;
        sprintf(palabra,"C:%0.1f",caracter);
        Lcd_Out2(2,5,palabra);
        }
        if(caracter>101){
            caracter=0;max=0;valor=0;
            Lcd_Cmd(LCD_CLEAR);
            __delay_ms(100);
            Lcd_Out(1,1,"Valor maximo");
            Lcd_Out(2,1,"alcanzado");
            __delay_ms(2000);
            Lcd_Cmd(LCD_CLEAR);
            __delay_ms(100);
            Lcd_Out(1,1,"Intentalo de ");
            Lcd_Out(2,1,"nuevo humano");
            __delay_ms(2000);
            Lcd_Cmd(LCD_CLEAR);
            __delay_ms(100);
        }
    }
    Lcd_Cmd(LCD_CLEAR);
    __delay_ms(100);
    Lcd_Out(1,1,"Seleccione el");
    Lcd_Out(2,1,"limite inferior");
    __delay_ms(2000);
    Lcd_Cmd(LCD_CLEAR);
    __delay_ms(100);
    caracter=0;valor=0;
    while(valor != '*'){
        Lcd_Out(1,1,"XP Temp MIN XP");
        teclado();
        if((valor >= '0') && (valor <= '9')){
        caracter=caracter*10+(valor-48);
        min=caracter;
        sprintf(palabra2,"C:%0.1f",caracter);
        Lcd_Out2(2,5,palabra2);
        }
        if(caracter>101 || min>max){
            caracter=0;min=0;valor=0;
            Lcd_Cmd(LCD_CLEAR);
            __delay_ms(100);
            Lcd_Out(1,1,"Valor maximo");
            Lcd_Out(2,1,"alcanzado o");
            __delay_ms(2000);
            Lcd_Cmd(LCD_CLEAR);
            __delay_ms(100);
            Lcd_Out(1,1,"Temp MIN mayor");
            Lcd_Out(2,1,"que Temp MAX");
            __delay_ms(2000);
            Lcd_Cmd(LCD_CLEAR);
            __delay_ms(100);
            Lcd_Out(1,1,"Intentalo de ");
            Lcd_Out(2,1,"nuevo humano");
            __delay_ms(2000);
            Lcd_Cmd(LCD_CLEAR);
            __delay_ms(100);
        }
    }
    Lcd_Cmd(LCD_CLEAR);
    __delay_ms(100);
    valor=0;
    while(valor!= '*'){
        teclado();
        ADCON0bits.GO_DONE=1;
        while(ADCON0bits.DONE){
            adc=ADRESH;
            adc=ADRESH<<8;
            adc=ADRESH+ADRESL;
            conver=(adc*500.0)/1023.0;
            Lcd_Out(1,1,"Temperatura");
            sprintf(palabra0,"C:%.3f",conver);
            Lcd_Out2(2,1,palabra0);
            if(conver>max){
                Rele1=1;LED1=1;
            }
            else if((conver<max) && (conver>min)){
                Rele1=0;Rele2=0;
                LED1=0;LED2=0;
            }
            else if(conver<min){
                Rele2=1;LED2=1; 
            }
        }
    }
    Rele1=0;Rele2=0;LED1=0;LED2=0;
    Lcd_Cmd(LCD_CLEAR);
    __delay_ms(100);
    Lcd_Out(1,2,"Hola Humano ");
    Lcd_Out(2,1,"**************** ");
    __delay_ms(2000);
    Lcd_Cmd(LCD_CLEAR);
    __delay_ms(100);
    Lcd_Out(1,1,"Selecciona la ");
    Lcd_Out(2,3,"temperatura ");
    __delay_ms(2000);
    Lcd_Cmd(LCD_CLEAR);
    __delay_ms(100);
    Lcd_Out(1,1,"De nuevo ");
    Lcd_Out(2,1,"**************** ");
    __delay_ms(2000);
    Lcd_Cmd(LCD_CLEAR);
    __delay_ms(100);
    goto volver;
}
void teclado(void){
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
    LATB = 0xF0;
    while (PORTB != 0xF0);
}
