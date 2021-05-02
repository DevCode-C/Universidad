/*
 * File:   practica5_0_1.c
 * Author: Emmanuel
 *
 * Created on 23 de febrero de 2019, 10:26 PM
 */
#include <xc.h>
#include <stdio.h>
#include "config2.h"
#include <pic18f4550.h>
#define _XTAL_FREQ 8000000
#include "flex_lcd.h"


unsigned char palabra[17];
unsigned char numero1[17];
unsigned char numero2[17];
unsigned char numero3[17];

int suma(int s1, int s2);
int resta(int s1, int s2);
int mult(int s1, int s2);
int scv(int s1, int s2);
void main(void) {
    float D1,D2,R0;
    short int SEL;
    TRISB=0xFF;
    TRISCbits.RC1=1;
    Lcd_Init();
    Lcd_Cmd(LCD_CLEAR);
    Lcd_Cmd(LCD_CURSOR_OFF);
    __delay_ms(100);
    while(PORTCbits.RC1==1){
    Lcd_Out(1,1,"Bienvenido :*");
    Lcd_Out(2,1,"*Calculadora*");
    }
    __delay_ms(500);
    INICIO://EL REGRESO CON GOTO
    LATB=0x00;
    Lcd_Cmd(LCD_CLEAR);
    __delay_ms(100);
    //SELECCIÓN DEL PRIMER DIGITO
    Lcd_Out(1,1,"Primer digito:");
   // __delay_ms(1000);
    //Lcd_Cmd(LCD_CLEAR);
    while(PORTCbits.RC1==1){
        D1=PORTB;
        sprintf(numero1,"Numero: %0.3f",D1);
        Lcd_Out2(2,1,numero1);
    }
    Lcd_Cmd(LCD_CLEAR);
    __delay_ms(100);
    Lcd_Out(1,1,"Segundo digito:");
    //SELECCIÓN DE SEGUNDO DIGITO
    while(PORTCbits.RC1==1){
        D2=PORTB;
        sprintf(numero2,"Numero: %0.3f",D2);
        Lcd_Out2(2,1,numero2);
    }
    //Selección de operación 
    SELECCION:
    Lcd_Cmd(LCD_CLEAR);
    __delay_ms(100);
    Lcd_Out(1,1,"Selecciona la ");
    Lcd_Out(2,3,"Operacion");
    __delay_ms(2000);
    Lcd_Cmd(LCD_CLEAR);
    __delay_ms(100);
    while(PORTCbits.RC1==1){
        SEL=PORTB;
        Lcd_Out(1,1,"1=+ 2=- 4=* 8=/");
        sprintf(numero3,"Seleccion: %03d",SEL);
        Lcd_Out2(2,1,numero3);
    }
    Lcd_Cmd(LCD_CLEAR);
    __delay_ms(100);
    switch(SEL){//Suma
        case 1: {R0=0;
            while(PORTCbits.RC1==1){
                R0=suma(D1,D2);
                sprintf(numero1,"%0.0f +",D1);
               // __delay_ms(100);
                sprintf(numero2," %0.0f",D2);
                //__delay_ms(100);
                sprintf(palabra,"Suma= %0.3f",R0);
               // __delay_ms(100);
                Lcd_Out2(1,1,numero1);
                
                Lcd_Out2(1,6,numero2);
               
                Lcd_Out2(2,1,palabra);
                
            }
        goto INICIO;
        }//Resta
        case 2: {R0=0;
            R0=resta(D1,D2);
            __delay_ms(100);
            Lcd_Cmd(LCD_CLEAR);
            __delay_ms(100);
            while(PORTCbits.RC1==1){
                //R0=resta(D1,D2);
                if(R0>=0){
                    sprintf(numero1,"%0.0f -",D1);
                    sprintf(numero2," %0.0f",D2);
                    sprintf(palabra,"Resta= %0.3f",R0);
                    Lcd_Out2(1,1,numero1);
                    Lcd_Out2(1,6,numero2);
                    Lcd_Out2(2,1,palabra);
                    }
                else{break;}
            }
            goto INICIO;
        }//Multiplicación
        case 4: {R0=0;
            R0=mult(D1,D2);
            if(R0>0){
                while(PORTCbits.RC0==1){
                    PORTD=R0;
                }
                __delay_ms(1000);
                goto INICIO;
            }
            else if(R0<0){
                while(PORTCbits.RC0==1){
                    PORTD=0;
                    PORTCbits.RC2=1;
                    __delay_ms(30);
                    PORTCbits.RC2=0;
                }
                 __delay_ms(1000);
                PORTCbits.RC2=0;
                goto INICIO;
            }
            else {
                __delay_ms(1000);
                goto INICIO;
            }
        }//División
        case 8: {R0=0;
            R0=scv(D1,D2);
            if(R0==0){
                PORTD=0xFF;
                __delay_ms(100);
                PORTD=0x00;
                goto INICIO;
            }
            else if(R0!=0){
                while(PORTCbits.RC0==1){
                    PORTD=R0;
                }
                __delay_ms(1000);
                PORTCbits.RC1=0;
                PORTCbits.RC2=0;
                goto INICIO;
            }
            else if(R0<0){
                while(PORTCbits.RC0==1){
                    PORTCbits.RC1=1;
                    PORTCbits.RC2=1;
                    PORTD=0;
                   /* __delay_ms(100);
                    PORTCbits.RC1=0;
                    PORTCbits.RC2=1;*/
                }
                __delay_ms(1000);
                PORTCbits.RC1=0;
                PORTCbits.RC2=0;
                PORTD=0;
                goto INICIO;
            }
        }
        default :{
            goto SELECCION;
        }
    }
}
int suma(int s1, int s2){
    int x=0;
    x=s1+s2;
    return x;
}
int resta(int s1, int s2){
    int x=0;
    x=s1-s2;
    if(x<0){
        x=x*(-1);
        while(PORTCbits.RC1==1){
            sprintf(numero1,"%0.0d -",s1);
            sprintf(numero2," %0.0d",s2);
            sprintf(palabra,"Resta= -%0.3d",x);
            Lcd_Out2(1,1,numero1);
            Lcd_Out2(1,6,numero2);
            Lcd_Out2(2,1,palabra);
        }
        __delay_ms(1000);
        return -1;
    }else  return x;
}
int mult(int s1, int s2){
    int x=0;
    x=s1*s2;
    if(x>255){
        int i;
        for(i=0;i<255;i+=10){
            PORTD=i;
            __delay_ms(100);
        }
        x=(-1);
        return x;
    }else return x;
}
int scv(int s1, int s2){
    int x=0,x1=0,x2=0;
    x1=s1;
    x2=s2;
    if(x2==0){
       
        for(int i=0;i<=255;i++){
          PORTD=i;
          __delay_ms(100);
        }
        x=0;
        return x;
    }
    
   /* else if(x1==0){
        x= -1;
        return x;
    }*/
    else {
        x=x1/x2;
        return x;
    }
    
}