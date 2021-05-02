/*
 * File:   Calcu.c
 * Author: chris_000
 *
 * Created on 21 de marzo de 2019, 15:28
 */

#include <stdlib.h>
#include <xc.h>
#define delay __delay_ms(100)
#include "Config.h"
#include <pic18f4550.h>
#define _XTAL_FREQ 8000000
#include "flex_lcd.h"
#include <stdio.h>
unsigned char Word[16];
unsigned char numero1[16];
unsigned char numero2[16];
unsigned char numero3[16];

float Num1;
float Num2;
int Selector,Selector2,Selector3;
float Resultado;

void main(void) {
    
    TRISD=0x00;
    TRISB=0xFF;
    TRISCbits.RC0=1;
    TRISCbits.RC1=1;
    Lcd_Init();
    Lcd_Cmd(LCD_CLEAR);
    Lcd_Cmd(LCD_CURSOR_OFF);
    __delay_ms(100);
    while(PORTCbits.RC1==1){
        Lcd_Out(1,1,"Wolo");
        Lcd_Out(2,1,"Calcu");        
    }
    
    Lcd_Cmd(LCD_CLEAR);
    delay;
    delay;
    while(1)
    {
      Begain:
      Lcd_Out(1,1,"Dato1");
      while(PORTCbits.RC1==1){
          Num1=PORTB;
          sprintf(numero1,"Number:%0.3f",Num1);
          Lcd_Out2(2,1,numero1);
          
      }
      Lcd_Cmd(LCD_CLEAR);
      delay;
      __delay_ms(500);
      Lcd_Out(1,1,"Numero2");
      while(PORTCbits.RC1==1)
      {
          Num2=PORTB;
          sprintf(numero2,"Number:%0.03f",Num2);
          Lcd_Out2(2,1,numero2);
          
      }
      Lcd_Cmd(LCD_CLEAR);
      delay;
      Lcd_Out(1,1,"Cual");
        Lcd_Out(2,1,"Operacion Prro");
        __delay_ms(2000);
        Selector:
        Lcd_Cmd(LCD_CLEAR);
        delay;
        while(PORTCbits.RC1==1){
            Selector=PORTB;
            Lcd_Out(1,1,"1=+ 3=- 7=* 15=/");
            sprintf(numero3,"Seleccion: %03d",Selector);
            Lcd_Out2(2,1,numero3);
        }
        Lcd_Cmd(LCD_CLEAR);
        __delay_ms(400);
        switch(Selector){
            
            case 1:{
            Lcd_Cmd(LCD_CLEAR);
            delay;
            while(PORTCbits.RC1==1){
                Resultado=Num1+Num2;
                sprintf(numero1,"%0.0f+",Num1);
                sprintf(numero2,"%0.0f",Num2);
                sprintf(Word,"Suma= %0.0f",Resultado);
                Lcd_Out2(1,1,numero1);
                Lcd_Out2(1,4,numero2);
                Lcd_Out2(2,1,Word);
            }
            __delay_ms(1000);
            Lcd_Cmd(LCD_CLEAR);
            delay;
            goto Begain;
        }
        
            case 3:{
                if(Num2>Num1){
                
            Lcd_Cmd(LCD_CLEAR);
            delay;
            while(PORTCbits.RC1==1){
                Resultado=Num1-Num2;
                Resultado=Resultado*(-1);
                sprintf(numero1,"%0.0f+",Num1);
                sprintf(numero2,"%0.0f",Num2);
                sprintf(Word,"Resta= %0.0f",Resultado);
                Lcd_Out2(1,1,numero1);
                Lcd_Out2(1,4,numero2);
                Lcd_Out2(2,1,Word);
            }
                             }
                else {
                Resultado=Num1-Num2;
                sprintf(numero1,"%0.0f+",Num1);
                sprintf(numero2,"%0.0f",Num2);
                sprintf(Word,"Resta= %0.0f",Resultado);
                Lcd_Out2(1,1,numero1);
                Lcd_Out2(1,4,numero2);
                Lcd_Out2(2,1,Word);
                
                     }
                __delay_ms(1000);
            Lcd_Cmd(LCD_CLEAR);
            delay;
            goto Begain;
        }
            case 7:
            {
                Lcd_Cmd(LCD_CLEAR);
                delay;
                while(PORTCbits.RC1==1){
                    Resultado=Num1*Num2;
                    sprintf(numero1,"%0.0f*",Num1);
                    sprintf(numero2,"%0.0f",Num2);
                    sprintf(Word,"Mult= %0.0f",Resultado);
                    Lcd_Out2(1,1,numero1);
                    Lcd_Out2(1,6,numero2);
                    Lcd_Out2(2,1,Word);
                    
                }
                 __delay_ms(1000);
                 Lcd_Cmd(LCD_CLEAR);
                 delay;
                 goto Begain;
            }
            case 15:
            {
                Lcd_Cmd(LCD_CLEAR);
                delay;
                if(Num2==0)
                {
                     while(PORTCbits.RC1==1)
                      Lcd_Out(1,1,"NelPrro");
                }
                    
                else{
                while(PORTCbits.RC1==1)
                {
                  Resultado=Num1/Num2;
                  sprintf(numero1,"%0.0f/",Num1);
                  sprintf(numero2,"%0.0f",Num2);
                  sprintf(Word,"Div= %0.0f",Resultado);
                  Lcd_Out2(1,1,numero1);
                  Lcd_Out2(1,4,numero2);
                  Lcd_Out2(2,1,Word);
                 __delay_ms(1000);
                 Lcd_Cmd(LCD_CLEAR);
                 delay;
                }
            }
                goto Begain;
            }
        
    }

    return;

    }
}