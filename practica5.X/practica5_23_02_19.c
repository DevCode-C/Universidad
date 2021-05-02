/*
 * File:   practica5_23_02_19.c
 * Author: Emmanuel
 *
 * Created on 23 de febrero de 2019, 08:21 PM
 */
#include <pic18f4550.h>
#include "config2.h"
#include <stdio.h>
#define _XTAL_FREQ 8000000
#include "flex_lcd.h"

int i;
int a;
unsigned char palabra[20];
 
void main(void) {
   
    
    
    while(1)
    {
        
   //LCD
    Lcd_Init();     //inicializamos el lcd
    Lcd_Cmd(LCD_CLEAR);		//limpiamos lcd
    Lcd_Cmd(LCD_CURSOR_OFF);	//apagamos el cursor
    __delay_ms(100);		//esperamos 100ms

    for(i=10; i>0; i--)
    {
    sprintf(palabra,"Cuenta %03d",i);   //guardamos en el string Buffer1 la palabra Cuenta espacio y el valor de i
    Lcd_Out2(1, 1, palabra);            //escribimos en el renglon uno espaco 1 la que contiene buffer1
    __delay_ms(200);	//esperamos 100ms y repetimos
    }   
    Lcd_Cmd(LCD_CLEAR);
     Lcd_Out(1, 1,"azael mora");
     __delay_ms(1000);
     
    for(i=11; i>0; i--)
    {
    Lcd_Cmd(LCD_SHIFT_LEFT);
     __delay_ms(200);	//esperamos 100ms y repetimos
    } 
    
    
    
    
   
    
 Lcd_Cmd(LCD_CLEAR);
    Lcd_Out(1, 1, "Programacion de");	//escribimos en la linea 2 espacio 1 
     Lcd_Out(2, 4, "embebidos");
    __delay_ms(1000);		//esperamos 600ms
    Lcd_Cmd(LCD_BLINK_CURSOR_ON);   //hacemos que parpade el cursor
    __delay_ms(1000);		//Esperamos 1s
    Lcd_Cmd(LCD_UNDERLINE_ON);	//subraya el cursor
    __delay_ms(1000);		//esperamos 1s
    Lcd_Cmd(LCD_CURSOR_OFF);	//apagamos el cursor
    __delay_ms(1000);
    Lcd_Cmd(LCD_CLEAR);		//limpiamos el cursor
     
    
    }
}
    