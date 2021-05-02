/*
 * File:   Practica8_15_03_19.c
 * Author: Emmanuel
 *
 * Created on 15 de marzo de 2019, 07:44 PM
 */
#include "config2.h"
#include <pic18f4550.h>
#include <stdio.h>
#define _XTAL_FREQ 12000000
#include "flex_lcd.h"
#include "Prueba1.h"
unsigned long valor;
long int Pasos_fun;
unsigned char palabra[17];
unsigned char palabra1[17];
unsigned char palabra2[17];
void teclado(void);
void main(void){
    ADCON1=0x0F;
    INTCON2bits.RBPU=0; 
    TRISB=0xF0;
    PORTD=0x00;
    PORTA=0x00;
    initM();
    Lcd_Init();
    Lcd_Cmd(LCD_CLEAR);
    Lcd_Cmd(LCD_CURSOR_OFF);
    __delay_ms(100);
    short int dir=0;
    long int pasos=0;
    unsigned char caracter;
    unsigned char Dir_sel;
    //Inicio del programa
    Lcd_Out(1,3,"Bienvenido");
    Lcd_Out(2,4,"Humano :3");
    __delay_ms(2000);
    Lcd_Cmd(LCD_CLEAR);
    __delay_ms(100);
    Lcd_Out(1,1,"Control de");
    Lcd_Out(2,1,"Motor a pasos");
    __delay_ms(2000);
    Lcd_Cmd(LCD_CLEAR);
    __delay_ms(100);
    Lcd_Out(1,1,"Unipolar");
    Lcd_Out(2,1,"Es lo que hay");
    __delay_ms(2000);
    while(1){
        Dir_sel=0;caracter=0;valor=0;dir=0;pasos=0;Dir_sel=0;
        Lcd_Cmd(LCD_CLEAR);
        __delay_ms(100);
        Lcd_Out(1,1,"Opciones");
        for(int i=10;i>0;i--){
            Lcd_Cmd(LCD_SHIFT_LEFT);
            __delay_ms(400);
        }
    
        Lcd_Cmd(LCD_CLEAR);
        __delay_ms(100);
        Lcd_Out(1,1,"Presiona *");
        Lcd_Out(2,1,"cuando termines");
        __delay_ms(2000);
        Lcd_Cmd(LCD_CLEAR);
        __delay_ms(100);
        Lcd_Out(1,1,"A:FS B:WS C:HS");
        while(valor != '*'){
            teclado();
            if(valor=='A' || valor=='B' || valor=='C'){
            caracter=valor;
            sprintf(palabra,"%c",caracter);
            Lcd_Out2(2,1,palabra);
            }
        }
        Lcd_Cmd(LCD_CLEAR);
        __delay_ms(100);
        switch(caracter){//CASE A
            case 'A':{valor=0;caracter=0;
                Lcd_Out(1,1,"FULL STEPS");
                Lcd_Out(2,1,"***************");
                __delay_ms(1000);
                Lcd_Cmd(LCD_CLEAR);
                __delay_ms(100);
                Lcd_Out(1,1,"Selecciona el");
                Lcd_Out(2,1,"sentido de giro");
                __delay_ms(1000);
                Lcd_Cmd(LCD_CLEAR);
                __delay_ms(100);
                Lcd_Out(1,1,"Presiona *");
                Lcd_Out(2,1,"cuando termines");
                __delay_ms(1000);
                Lcd_Cmd(LCD_CLEAR);
                __delay_ms(100);
                Lcd_Out(1,2,"1:DER  2:IZQ");
                Lcd_Out(2,1,"OPT:");
                while(valor != '*'){
                    teclado();
                    if(valor=='1' || valor=='2'){
                        Dir_sel=valor;
                        sprintf(palabra1," %c",Dir_sel);
                        Lcd_Out2(2,5,palabra1);
                        if(Dir_sel=='1'){dir=1;}
                        else if(Dir_sel=='2'){dir=2;}
                    }
                    
                }
                valor=0;
                Lcd_Cmd(LCD_CLEAR);
                __delay_ms(100);
                Lcd_Out(1,1,"Selecciona el");
                Lcd_Out(2,1,"N de pasos");
                __delay_ms(1000);
                Lcd_Cmd(LCD_CLEAR);
                __delay_ms(100);
                Lcd_Out(1,1,"Presiona *");
                Lcd_Out(2,1,"cuando termines");
                __delay_ms(1000);
                Lcd_Cmd(LCD_CLEAR);
                __delay_ms(100);
                while(valor != '*'){
                    teclado();
                    Lcd_Out(1,1,"Numero de ");
                    Lcd_Out(2,1,"Pasos:");
                    if((valor >= '0') && (valor <= '9')){
                        pasos = pasos*10 + (valor - 48);
                        sprintf(palabra2," %d",pasos);
                        Lcd_Out2(2,7,palabra2);
                    }
                    Pasos_fun = pasos;
                    if(Pasos_fun>9000){
                        pasos=0;Pasos_fun=0;
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
                valor=0;
                Lcd_Cmd(LCD_CLEAR);
                __delay_ms(100);
                Lcd_Out(1,1,"Motor Girando");
                opt_Full_stepper(Pasos_fun,dir);
                PORTA=0x00;
                break;
            }//Case B
            case 'B':{valor=0;caracter=0;
                Lcd_Out(1,1,"WAVE STEPS");
                Lcd_Out(2,1,"***************");
                __delay_ms(1000);
                Lcd_Cmd(LCD_CLEAR);
                __delay_ms(100);
                Lcd_Out(1,1,"Selecciona el");
                Lcd_Out(2,1,"sentido de giro");
                __delay_ms(1000);
                Lcd_Cmd(LCD_CLEAR);
                __delay_ms(100);
                Lcd_Out(1,1,"Presiona *");
                Lcd_Out(2,1,"cuando termines");
                __delay_ms(1000);
                Lcd_Cmd(LCD_CLEAR);
                __delay_ms(100);
                Lcd_Out(1,2,"1:DER  2:IZQ");
                Lcd_Out(2,1,"OPT:");
                while(valor != '*'){
                    teclado();
                    if(valor=='1' || valor=='2'){
                        Dir_sel=valor;
                        sprintf(palabra1," %c",Dir_sel);
                        Lcd_Out2(2,5,palabra1);
                        if(Dir_sel=='1'){dir=1;}
                        else if(Dir_sel=='2'){dir=2;}
                    }
                    
                }
                valor=0;
                Lcd_Cmd(LCD_CLEAR);
                __delay_ms(100);
                Lcd_Out(1,1,"Selecciona el");
                Lcd_Out(2,1,"N de pasos");
                __delay_ms(1000);
                Lcd_Cmd(LCD_CLEAR);
                __delay_ms(100);
                Lcd_Out(1,1,"Presiona *");
                Lcd_Out(2,1,"cuando termines");
                __delay_ms(1000);
                Lcd_Cmd(LCD_CLEAR);
                __delay_ms(100);
                while(valor != '*'){
                    teclado();
                    Lcd_Out(1,1,"Numero de ");
                    Lcd_Out(2,1,"Pasos:");
                    if((valor >= '0') && (valor <= '9')){
                        pasos = pasos*10 + (valor - 48);
                        sprintf(palabra2," %d",pasos);
                        Lcd_Out2(2,7,palabra2);
                    }
                    Pasos_fun = pasos;
                    if(Pasos_fun>9000){
                        pasos=0;Pasos_fun=0;
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
                valor=0;
                Lcd_Cmd(LCD_CLEAR);
                __delay_ms(100);
                Lcd_Out(1,1,"Motor Girando");
                opt_Wave_stepper(Pasos_fun,dir);
                PORTA=0x00;
                break;
            }//CASE C
            case 'C':{valor=0;caracter=0;
                Lcd_Out(1,1,"HALF STEPS");
                Lcd_Out(2,1,"***************");
                __delay_ms(1000);
                Lcd_Cmd(LCD_CLEAR);
                __delay_ms(100);
                Lcd_Out(1,1,"Selecciona el");
                Lcd_Out(2,1,"sentido de giro");
                __delay_ms(1000);
                Lcd_Cmd(LCD_CLEAR);
                __delay_ms(100);
                Lcd_Out(1,1,"Presiona *");
                Lcd_Out(2,1,"cuando termines");
                __delay_ms(1000);
                Lcd_Cmd(LCD_CLEAR);
                __delay_ms(100);
                Lcd_Out(1,2,"1:DER  2:IZQ");
                Lcd_Out(2,1,"OPT:");
                while(valor != '*'){
                    teclado();
                    if(valor=='1' || valor=='2'){
                        Dir_sel=valor;
                        sprintf(palabra1," %c",Dir_sel);
                        Lcd_Out2(2,5,palabra1);
                        if(Dir_sel=='1'){dir=1;}
                        else if(Dir_sel=='2'){dir=2;}
                    }
                    
                }
                valor=0;
                Lcd_Cmd(LCD_CLEAR);
                __delay_ms(100);
                Lcd_Out(1,1,"Selecciona el");
                Lcd_Out(2,1,"N de pasos");
                __delay_ms(1000);
                Lcd_Cmd(LCD_CLEAR);
                __delay_ms(100);
                Lcd_Out(1,1,"Presiona *");
                Lcd_Out(2,1,"cuando termines");
                __delay_ms(1000);
                Lcd_Cmd(LCD_CLEAR);
                __delay_ms(100);
                while(valor != '*'){
                    teclado();
                    Lcd_Out(1,1,"Numero de ");
                    Lcd_Out(2,1,"Pasos:");
                    if((valor >= '0') && (valor <= '9')){
                        pasos = pasos*10 + (valor - 48);
                        sprintf(palabra2," %d",pasos);
                        Lcd_Out2(2,7,palabra2);
                    }
                    Pasos_fun = pasos;
                    if(Pasos_fun>9000){
                        pasos=0;Pasos_fun=0;
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
                valor=0;
                Lcd_Cmd(LCD_CLEAR);
                __delay_ms(100);
                Lcd_Out(1,1,"Motor Girando");
                opt_Half_stepper(Pasos_fun,dir);
                PORTA=0x00;
                break;
            }
            default :{
                valor=0;
                Lcd_Cmd(LCD_CLEAR);
                __delay_ms(100);
                Lcd_Out(1,1,"DATO");
                Lcd_Out(2,1,"INCORRECTO");
                __delay_ms(1000);
                Lcd_Cmd(LCD_CLEAR);
                __delay_ms(100);
                Lcd_Out(1,1,"Selecciona de");
                Lcd_Out(2,1,"nuevo X,P");
                __delay_ms(2000);
                Lcd_Cmd(LCD_CLEAR);
                __delay_ms(100);
                break;
            }
        }
    }
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
