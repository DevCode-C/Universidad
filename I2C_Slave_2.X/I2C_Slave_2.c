/*
 * File:   I2C_Slave_2.c
 * Author: Emmanuel
 *
 * Created on 24 de abril de 2019, 11:53 PM
 */
#include "Config_16F.h"
#include <pic16f887.h>
#include <xc.h>
#include <stdio.h>
#define _XTAL_FREQ 12000000
#include "I2C_Slave.h"
#include "flex_lcd.h"
short z;
float Promedio;
unsigned char palabra2[17];
unsigned long datos;
unsigned char valor,caracter;
void teclado(void);
void main(void){
    I2C_Slave_Init(0x00);
    Lcd_Init();
    Lcd_Cmd(LCD_CLEAR);
    Lcd_Cmd(LCD_CURSOR_OFF);
    __delay_ms(100);
    ANSEL=0x00;
    ANSELH=0x00;
    OPTION_REG=1;
    TRISB=0xF0;
    TRISA=0x00;
    PORTB=0x00;
    PORTA=0x00;
    while(1){
        Lcd_Out(1,1,"Bienvenido");
        __delay_ms(1000);
        Lcd_Cmd(LCD_CLEAR);
        __delay_ms(100);
        while(valor != '*'){
            teclado();
            Lcd_Out(1,1,"Slecciona los ");
            Lcd_Out(2,1,"Leds:");
            if((valor >= '0') && (valor <= '9') || valor=='A'){
                caracter=valor;
                sprintf(palabra2," %c",valor);
                Lcd_Out2(2,7,palabra2);
            }
            switch(caracter){
                case '1':{
                    PORTA=0x01;
                    break;
                }
                case '2':{
                    PORTA=0x02;
                    break;
                }
                case '3':{
                    PORTA=0x03;
                    break;
                }
                case '4':{
                    PORTA=0x04;
                    break;
                }case '5':{
                    PORTA=0x05;
                    break;
                }
                case '6':{
                    PORTA=0x06;
                    break;
                }case '7':{
                    PORTA=0x07;
                    break;
                }
                case '8':{
                    PORTA=0x08;
                    break;
                }
                case '9':{
                    PORTA=0x09;
                    break;
                }
                case 'A':{
                    PORTA=0x00;
                    Lcd_Cmd(LCD_CLEAR);
                    __delay_ms(100);
                    while(1){
                        Lcd_Out(1,1,"Informacion");
                        switch(datos){
                            case 0x01:{
                                Lcd_Out(1,1,"Informacion 1");
                                break;
                            }
                            case 0x02:{
                                Lcd_Out(1,1,"Informacion 2");
                                break;
                            }
                            case 0x03:{
                                Lcd_Out(1,1,"Informacion 3");
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
}
void __interrupt() I2C_Slave2_(){
        if(SSPIF == 1){
       SSPCONbits.CKP = 0;
       if ((SSPCONbits.SSPOV) || (SSPCONbits.WCOL)){
             z = SSPBUF;            
             SSPCONbits.SSPOV = 0; 
             SSPCONbits.WCOL = 0;   
             SSPCONbits.CKP = 1;
        }
        if(!SSPSTATbits.D_nA && !SSPSTATbits.R_nW) {
           z = SSPBUF;
           while(!BF);
           datos = SSPBUF;
           SSPCONbits.CKP = 1;
           SSPM3 = 0;
        }
        else if(!SSPSTATbits.D_nA && SSPSTATbits.R_nW){
           z = SSPBUF;
           BF = 0;
           SSPBUF = Promedio ;
           SSPCONbits.CKP = 1;
           while(SSPSTATbits.BF);
        }
       
       SSPIF = 0;
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
    PORTB = 0xF0;
    while (PORTB != 0xF0);
}