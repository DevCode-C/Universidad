/*
 * File:   Practica6_03_03_19.c
 * Author: Emmanuel
 *
 * Created on 3 de marzo de 2019, 02:03 PM
 */
#include "config2.h"
#include <pic18f4550.h>
#include <stdio.h>
#include <string.h>
#define _XTAL_FREQ 8000000
#include "flex_lcd.h"
#define delay1 __delay_ms(100)
#define delay2 __delay_ms(200)

unsigned char palabra[17];
unsigned char palabra1[17];
unsigned char palabra2[17];
unsigned long pin1;
void teclado(void);
void incorrecto(void);
void correcto(void);
void letrero(void);
unsigned long sum1;
unsigned long valor;
unsigned int pasword=0;
unsigned int cambio=0;
long int saldo=0;
short int paso=0;
void main(void){
    short int show=0,opt=0;
    ADCON1=0x0F;
    INTCON2bits.RBPU=0; 
    TRISB=0xF0;
    PORTD=0x00;
    saldo=10000;
    pasword=123;
    Lcd_Init();
    Lcd_Cmd(LCD_CLEAR);
    Lcd_Cmd(LCD_CURSOR_OFF);
    delay1;
    inicio:
    Lcd_Out(1,3,"Bienvenido");
    Lcd_Out(2,7,"A:");
    __delay_ms(2000);
    Lcd_Cmd(LCD_CLEAR);
    delay1;
    Lcd_Out(1,2,"ESTE SU BANCO");
    Lcd_Out(2,2,"JW RED LABEL");
    __delay_ms(2000);
    Lcd_Cmd(LCD_CLEAR);
    delay2;
    Lcd_Out(1,3,"Hola, Humano");
    Lcd_Out(2,1,"****************");
    __delay_ms(2000);
    Lcd_Cmd(LCD_CLEAR);
    delay2;
    while(1){show=1;
        while (valor != '*'){
            teclado();
            Lcd_Out(1, 1,"Ingresa tu pin:");
            if ((valor >= '0')&&(valor <= '9')){
                sum1 = sum1*10 + (valor - 48);   
                 Lcd_Out(2,show,"*");
                 show++;
            }
            pin1=sum1;
        }
        if(pin1==pasword && valor!=0){
            Lcd_Cmd(LCD_CLEAR);
            delay2;
            valor=0;
            sum1=0;
            Lcd_Out(1,1,"Pin Correcto");
            __delay_ms(1000);
            Lcd_Cmd(LCD_CLEAR);
            delay1;
            correcto();
            
        }else if(valor=='*' && paso==1){
            Lcd_Cmd(LCD_CLEAR);
            delay1;
            pin1=0;
            valor=0;
            paso=0;
            goto inicio;
        }
        else{
            Lcd_Cmd(LCD_CLEAR);
            delay2;
            Lcd_Out(1,1,"Pin incorrecto");
            valor=0;
            sum1=0;
            __delay_ms(1000);
            Lcd_Cmd(LCD_CLEAR);
            delay2;
            opt++;
            if(opt==3){
                opt=0;
                incorrecto();
            }
            Lcd_Cmd(LCD_CLEAR);
            delay2;
        }
        Lcd_Cmd(LCD_CLEAR);
        delay2;
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
    //delay1;
}
void incorrecto(void){
    Lcd_Out(1, 1,"No recuerda su");
    Lcd_Out(2,4,"pin X'C");
    __delay_ms(3000);
    delay1;
    Lcd_Cmd(LCD_CLEAR);
    Lcd_Out(1, 1,"Piense un poco");
    Lcd_Out(2,5,"X'V");
     __delay_ms(3000);
    delay1;
    Lcd_Cmd(LCD_CLEAR);
    Lcd_Out(1, 1,"Listo, presione");
    Lcd_Out(2,5," # ");
    while (valor != '#'){
        teclado();     
    }
    valor=0;
}
void correcto(void){
    int i;
   long int deposito=0;
    Operacion:
    valor=0;
    letrero();
    while(valor!='*'){
        teclado();
        switch(valor){
            case 'A':{valor=0;
                Lcd_Cmd(LCD_CLEAR);
                delay1;
                Lcd_Out(1, 1,"Su saldo es:");
                sprintf(palabra1,"  $%d",saldo);
                Lcd_Out2(2,1,palabra1);
                __delay_ms(3000);
                Lcd_Cmd(LCD_CLEAR);
                delay1;
                Lcd_Cmd(LCD_CLEAR);
                delay1;
                letrero();
                teclado();
                //if(valor=='*'){goto Operacion;}
                break;
            }
            case 'B':{deposito=0;
                Lcd_Cmd(LCD_CLEAR);
                delay1;
                Lcd_Out(1,5,"Deposito");
                for(i=16;i>0;i--){
                    Lcd_Cmd(LCD_SHIFT_LEFT);
                    __delay_ms(300);
                }
                Lcd_Cmd(LCD_CLEAR);
                delay1;
                Lcd_Out(1,1,"Solo podra depositar maximo 9000 pesos");
                for(i=38;i>0;i--){
                    Lcd_Cmd(LCD_SHIFT_LEFT);  
                    delay2;
                }
                Lcd_Cmd(LCD_CLEAR);
                delay1;
                Lcd_Out(1,1,"Presiona * cuando termine");
                for(i=26;i>0;i--){
                    Lcd_Cmd(LCD_SHIFT_LEFT);  
                    delay2;
                }
                Lcd_Cmd(LCD_CLEAR);
                delay1;
                sum1=0;
                while(valor!='*'){
                    teclado();
                    Lcd_Out(1, 1,"Ingrese su");
                    Lcd_Out(2,1,"Deposito:");
                    if ((valor >= '0')&&(valor <= '9')){
                        sum1 = sum1*10 + (valor - 48); 
                        sprintf(palabra,"$%d",sum1);
                        Lcd_Out2(2,10,palabra);
                    }
                    deposito=sum1;
                    if(deposito>9000){
                        sum1=0;
                        Lcd_Cmd(LCD_CLEAR);
                        delay1;
                        Lcd_Out(1,1,"Deposito maximo");
                        Lcd_Out(2,1,"alcanzado");
                        __delay_ms(2000);
                        Lcd_Cmd(LCD_CLEAR);
                        delay1;
                        Lcd_Out(1,1,"Intentalo de ");
                        Lcd_Out(2,1,"nuevo humano");
                        __delay_ms(2000);
                        Lcd_Cmd(LCD_CLEAR);
                        delay1;
                    }
                }
                Lcd_Cmd(LCD_CLEAR);                                                             
                delay1;
                valor=0;
                saldo=saldo+deposito;
                Lcd_Out(1,1,"Saldo depositado");
                __delay_ms(1000);
                Lcd_Cmd(LCD_CLEAR);
                delay1;
                letrero();
                teclado();
                break;
            }
            case 'C':{
                deposito=0;
                Lcd_Cmd(LCD_CLEAR);
                delay1;
                Lcd_Out(1,5,"Retiro");
                for(i=12;i>0;i--){
                    Lcd_Cmd(LCD_SHIFT_LEFT);
                    __delay_ms(300);
                }
                 Lcd_Cmd(LCD_CLEAR);
                delay1;
                Lcd_Out(1,1,"Solo podra retirar maximo 9000 pesos");
                for(i=36;i>0;i--){
                    Lcd_Cmd(LCD_SHIFT_LEFT);  
                    delay2;
                }
                Lcd_Cmd(LCD_CLEAR);
                delay1;
                Lcd_Out(1,1,"Presione * cuando termine");
                for(i=26;i>0;i--){
                    Lcd_Cmd(LCD_SHIFT_LEFT);  
                    delay2;
                }
                Lcd_Cmd(LCD_CLEAR);
                delay1;
                sum1=0;
                while(valor!='*'){
                    teclado();
                    Lcd_Out(1, 1,"Ingrese su");
                    Lcd_Out(2,1,"Retiro:");
                    if ((valor >= '0')&&(valor <= '9')){
                        sum1 = sum1*10 + (valor - 48); 
                        sprintf(palabra1,"$%d",sum1);
                        Lcd_Out2(2,10,palabra1);
                    }
                    deposito=sum1;
                    if(deposito>9000){
                        sum1=0;
                        Lcd_Cmd(LCD_CLEAR);
                        delay1;
                        Lcd_Out(1,1,"Retiro maximo");
                        Lcd_Out(2,1,"alcanzado");
                        __delay_ms(2000);
                        Lcd_Cmd(LCD_CLEAR);
                        delay1;
                        Lcd_Out(1,1,"Intentalo de ");
                        Lcd_Out(2,1,"nuevo humano");
                        __delay_ms(2000);
                        Lcd_Cmd(LCD_CLEAR);
                        delay1;
                    }
                }
                Lcd_Cmd(LCD_CLEAR);
                delay1;
                valor=0;
                //saldo=saldo+deposito;
                if(deposito>saldo){
                    for(i=18;i<0;i--){
                        Lcd_Out(1,1,"Saldo insuficiente");
                        delay2;
                    }
                    Lcd_Out(2,4,"Pobre XD");
                    Lcd_Cmd(LCD_CLEAR);
                    delay1;
                    letrero();
                    teclado();
                }else{
                    saldo=saldo-deposito;
                Lcd_Out(1,1,"Saldo retirado");
                __delay_ms(1000);
                Lcd_Cmd(LCD_CLEAR);
                delay1;
                }
                Lcd_Cmd(LCD_CLEAR);
                delay1;
                letrero();
                teclado();
                break;
            }
            case 'D':{
                Lcd_Cmd(LCD_CLEAR);
                delay1;
                Lcd_Out(1,3,"Cambio de NIP");
                for(i=17;i>0;i--){
                    Lcd_Cmd(LCD_SHIFT_LEFT);
                    __delay_ms(300);
                }
                Lcd_Cmd(LCD_CLEAR);
                delay1;
                Lcd_Out(1,1,"Al fin, ya era tiempo");
                Lcd_Out(2,1,"Ya se habia tardado");
                for(i=22;i>0;i--){
                    Lcd_Cmd(LCD_SHIFT_LEFT);  
                    __delay_ms(350);
                }
                Lcd_Cmd(LCD_CLEAR);
                delay1;
                Lcd_Out(1,1,"Presione * cuando termine");
                for(i=26;i>0;i--){
                    Lcd_Cmd(LCD_SHIFT_LEFT);  
                    delay2;
                }
                Lcd_Cmd(LCD_CLEAR);
                delay1;
                try:
                sum1=0;
                while(valor!='*'){
                    teclado();
                    Lcd_Out(1, 1,"Viejo");
                    Lcd_Out(2,1,"NIP:");
                    if ((valor >= '0')&&(valor <= '9')){
                        sum1 = sum1*10 + (valor - 48); 
                        sprintf(palabra1,"%d",sum1);
                        Lcd_Out2(2,5,palabra1);
                    }
                    pin1=sum1;  
                }
                Lcd_Cmd(LCD_CLEAR);
                delay1;
                if(pin1==pasword && valor!=0){
                    mayor:
                    valor=0;
                    sum1=0;
                    while(valor!='*'){
                        teclado();
                        Lcd_Out(1, 1,"Nuevo");
                        Lcd_Out(2,1,"NIP:");
                        if ((valor >= '0')&&(valor <= '9')){
                            sum1 = sum1*10 + (valor - 48); 
                            sprintf(palabra2,"%d",sum1);
                            Lcd_Out2(2,5,palabra2);
                        }
                        cambio=sum1;  
                    }
                    if(cambio>9999){
                        Lcd_Cmd(LCD_CLEAR);
                        delay1;
                        Lcd_Out(1, 1,"PIN no valido");
                        for(i=14;i>0;i--){
                            Lcd_Cmd(LCD_SHIFT_LEFT);
                            __delay_ms(350);
                        }
                        Lcd_Cmd(LCD_CLEAR);
                        delay1;
                        Lcd_Out(1, 1,"Intente otra vez");
                        Lcd_Out(2,5,"Humano");
                        __delay_ms(2000);
                        Lcd_Cmd(LCD_CLEAR);
                        delay1;
                        goto mayor;
                    }else{valor=0;
                        pasword=cambio;
                        Lcd_Cmd(LCD_CLEAR);
                        delay1;
                        Lcd_Out(1, 1,"Cambio realizado");
                        for(i=17;i>0;i--){
                            Lcd_Cmd(LCD_SHIFT_LEFT);
                            __delay_ms(350);
                        }
                        Lcd_Out(2,1,"felicidades");
                        __delay_ms(2000);
                        Lcd_Cmd(LCD_CLEAR);
                        delay1;
                        Lcd_Cmd(LCD_CLEAR);
                        delay1;
                        letrero();
                        teclado();
                    }
                }else{valor=0;
                    Lcd_Cmd(LCD_CLEAR);
                    delay1;
                    Lcd_Out(1, 1,"Pues ya esta viejo");
                    for(i=17;i>0;i--){
                        Lcd_Cmd(LCD_SHIFT_LEFT);
                        __delay_ms(350);
                    }
                    Lcd_Out(2,1,"el NIP");
                    __delay_ms(1000);
                    Lcd_Cmd(LCD_CLEAR);
                    delay1;
                    Lcd_Out(1, 1,"Intente otra vez");
                    Lcd_Out(2,5,"Humano");
                    __delay_ms(2000);
                    Lcd_Cmd(LCD_CLEAR);
                    delay1;
                    goto try;
                }
                break;
            }
            case '#':{
                valor='*';
                paso=1;
                break;
            }
        }
    }
}
void letrero(void){
 Lcd_Out(1, 1,"Operaciones");
    Lcd_Out(2,4,"disponibles:");
    __delay_ms(2000);
    delay1;
    Lcd_Cmd(LCD_CLEAR);
    delay1;
    Lcd_Out(1, 1,"A:Consulta");
    Lcd_Out(2,1,"B:Deposito");
    __delay_ms(2000);
    Lcd_Cmd(LCD_CLEAR);
    delay1;
    Lcd_Out(1,1,"C:Retiro");
    Lcd_Out(2,1,"D:Cambio de nip");
    __delay_ms(2000);
    Lcd_Cmd(LCD_CLEAR);
    delay1;
    Lcd_Out(1,1,"#:Salir");
    __delay_ms(500);
    
}