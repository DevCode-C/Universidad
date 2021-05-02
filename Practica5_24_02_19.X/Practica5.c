/*
 * File:   Practica5.c
 * Author: Emmanuel
 *
 * Created on 24 de febrero de 2019, 09:37 PM
 */

#include "config2.h"
#include <pic18f4550.h>
#define _XTAL_FREQ 8000000
#include "flex_lcd.h"
#include <stdio.h>
//#include "Operaciones.h"
#define delay1 __delay_ms(100)
unsigned char palabra[17];
unsigned char numero1[17];
unsigned char numero2[17];
unsigned char numero3[17];


void main(void) {
    float D1,D2,R;
    short int SEL,fun,fun1;
    ADCON1=0x0F;
    TRISB=0xFF;
    TRISCbits.RC1=1;
    TRISCbits.RC2=1;
    Lcd_Init();
    Lcd_Cmd(LCD_CLEAR);
    Lcd_Cmd(LCD_CURSOR_OFF);
    __delay_ms(100);
    while(PORTCbits.RC1==1){
    Lcd_Out(1,1,"Bienvenido");
    Lcd_Out(2,1,"*Calculadora*");
    }
    Lcd_Cmd(LCD_CLEAR);
    __delay_ms(100);
    while(1){
        inicio:
        Lcd_Out(1,1,"Primer digito:");
        while(PORTCbits.RC1==1){
            D1=PORTB;
            sprintf(numero1,"Numero: %0.3f",D1);
            Lcd_Out2(2,1,numero1);
        }
        Lcd_Cmd(LCD_CLEAR);
        delay1;
        __delay_ms(500);
        Lcd_Out(1,1,"Segundo digito:");
        while(PORTCbits.RC1==1){
            D2=PORTB;
            sprintf(numero2,"Numero: %0.3f",D2);
            Lcd_Out2(2,1,numero2);
        }
        Lcd_Cmd(LCD_CLEAR);
        delay1;
        Lcd_Out(1,1,"Selecciona la");
        Lcd_Out(2,3,"Operacion");
        __delay_ms(2000);
        seleccion:
        Lcd_Cmd(LCD_CLEAR);
        delay1;
        while(PORTCbits.RC1==1){
            SEL=PORTB;
            Lcd_Out(1,1,"1=+ 2=- 4=* 8=/");
            sprintf(numero3,"Seleccion: %03d",SEL);
            Lcd_Out2(2,1,numero3);
        }
         Lcd_Cmd(LCD_CLEAR);
        delay1;
        delay1;
        delay1;
        if(SEL==1){
            Lcd_Cmd(LCD_CLEAR);
            delay1;
            while(PORTCbits.RC1==1){
                R=D1+D2;
                sprintf(numero1,"%0.0f +",D1);
                sprintf(numero2," %0.0f",D2);
                sprintf(palabra,"Suma= %0.3f",R);
                Lcd_Out2(1,1,numero1);
                Lcd_Out2(1,6,numero2);
                Lcd_Out2(2,1,palabra);
            }
            __delay_ms(1000);
            Lcd_Cmd(LCD_CLEAR);
            delay1;
            goto inicio;
        }
        else if(SEL==2){
            if(D2>D1){
                Lcd_Cmd(LCD_CLEAR);
                delay1;
                while(PORTCbits.RC1==1){
                    R=D1-D2;
                    R=R*(-1);
                    sprintf(numero1,"%0.0f -",D1);
                    sprintf(numero2," %0.0f",D2);
                    sprintf(palabra,"Resta= -%0.3f",R);
                    Lcd_Out2(1,1,numero1);
                    Lcd_Out2(1,6,numero2);
                    Lcd_Out2(2,1,palabra);
                }
                __delay_ms(1000);
                Lcd_Cmd(LCD_CLEAR);
                delay1;
                goto inicio;
            }else{
                Lcd_Cmd(LCD_CLEAR);
                delay1;
                while(PORTCbits.RC1==1){
                    R=D1-D2;
                    sprintf(numero1,"%0.0f -",D1);
                    sprintf(numero2," %0.0f",D2);
                    sprintf(palabra,"Resta= %0.3f",R);
                    Lcd_Out2(1,1,numero1);
                    Lcd_Out2(1,6,numero2);
                    Lcd_Out2(2,1,palabra);
                }
                __delay_ms(1000);
                Lcd_Cmd(LCD_CLEAR);
                delay1;
                goto inicio;
            }
        }
        else if(SEL==4){
            Lcd_Cmd(LCD_CLEAR);
            delay1;
            while(PORTCbits.RC1==1){
                R=D1*D2;
                sprintf(numero1,"%0.0f *",D1);
                sprintf(numero2," %0.0f",D2);
                sprintf(palabra,"Mult= %0.3f",R);
                Lcd_Out2(1,1,numero1);
                Lcd_Out2(1,6,numero2);
                Lcd_Out2(2,1,palabra);
            }
            __delay_ms(1000);
            Lcd_Cmd(LCD_CLEAR);
            delay1;
            goto inicio;
        }
        else if(SEL==8){
            R=D1/D2;
            if(D2==0){
                while(PORTCbits.RC1==1){
                    Lcd_Out(1,3,"SYNTAX ERROR");
                }
                __delay_ms(1000);
                Lcd_Cmd(LCD_CLEAR);
                delay1;
                goto inicio;
            }else{
                while(PORTCbits.RC1==1){
                    R=D1/D2;
                    sprintf(numero1,"%0.0f /",D1);
                    sprintf(numero2," %0.0f",D2);
                    sprintf(palabra,"Div= %0.3f",R);
                    Lcd_Out2(1,1,numero1);
                    Lcd_Out2(1,6,numero2);
                    Lcd_Out2(2,1,palabra);
                }
                __delay_ms(1000);
                Lcd_Cmd(LCD_CLEAR);
                delay1;
                goto inicio;
                
            }
        }else{
            goto seleccion;
        }
    }
}
