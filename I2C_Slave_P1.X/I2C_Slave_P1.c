/*
 * File:   I2C_Slave_P1.c
 * Author: Emmanuel
 *
 * Created on 4 de mayo de 2019, 09:53 PM
 */

#include "config2.h"
#include <pic18f4550.h>
#define _XTAL_FREQ 12000000
#include <stdio.h>
#include "flex_lcd.h"
#include "I2C_Master.h"
void Adquisicion_Pago(void);
short int input,output,temp;//Variables para la comunicación I2C
int *Ptr_pago,*Ptr_Entrada;
void main(void) {
    ADCON1=0x0F;
    I2C_Master_Init(100000);
    //I2C_Slave_Init(0x01);//Inicialización de la comunicación I2C en modo esclavo, dirección 0x01
    //Declaración de Puertos
    TRISBbits.TRISB7=1;//RB7 como entrada
    TRISBbits.TRISB6=1;//RB6 como entrada
    TRISCbits.TRISC2=0;//LATC2 como salida
    TRISCbits.TRISC0=0;
    
    TRISEbits.TRISE0=1;//LATE0 como entrada
    TRISEbits.TRISE1=1;//LATE1 como entrada
    TRISEbits.TRISE2=0;//RE2 como salida
    //Declaracion de estados en 0
    PORTBbits.RB7=0;//Poniendo a cero para evitar cualquier error
    PORTBbits.RB6=0;//Poniendo a cero para evitar cualquier error
    LATCbits.LATC2=0;//Poniendo a cero para evitar cualquier error
    PORTEbits.RE0=0;//Poniendo a cero para evitar cualquier error
    PORTEbits.RE1=0;//Poniendo a cero para evitar cualquier error
    LATEbits.LATE2=0;//Poniendo a cero para evitar cualquier error
    LATCbits.LATC0=0;
    
    Lcd_Init();//Inicialización del display LCD
    Lcd_Cmd(LCD_CLEAR);//Limpia el display
    Lcd_Cmd(LCD_CURSOR_OFF);//Elimina el cursor
    __delay_ms(100);
    while(TRUE){//Ciclo infinito, inicia la secuencia
        if(PORTBbits.RB7==0 || PORTBbits.RB6==0){//Comprobación de los infrarrojos de la entrada
            Lcd_Out(1,1,"Bienvenido al ");
            Lcd_Out(2,1,"MOTEL LA MILPA");
            __delay_ms(2000);
            Lcd_Cmd(LCD_CLEAR);
            __delay_ms(100);
            Lcd_Out(1,1,"Que habitacion ");
            Lcd_Out(2,4,"desea? ");
            __delay_ms(2000);
            Lcd_Cmd(LCD_CLEAR);
            __delay_ms(100);
            Lcd_Out(1,1,"Tenemos 3 tipos ");
            Lcd_Out(2,1,"de habitaciones ");
            __delay_ms(2000);
             Lcd_Cmd(LCD_CLEAR);
            __delay_ms(100);
            Lcd_Out(1,1,"Normal  jacuzzi ");
            Lcd_Out(2,2,"Master suite ");
            __delay_ms(2000);
            Lcd_Cmd(LCD_CLEAR);
            __delay_ms(100);
            Lcd_Out(1,1,"Normal a $250 ");
            Lcd_Out(2,1,"Jacuzzi a $450 ");
            __delay_ms(2000);
            Lcd_Cmd(LCD_CLEAR);
            __delay_ms(100);
            Lcd_Out(1,1,"Master suite a");
            Lcd_Out(2,4,"$600 ");
            __delay_ms(2000);
            Lcd_Cmd(LCD_CLEAR);
            __delay_ms(100);
            Lcd_Out(1,1,"Cual gustaria ");
            Lcd_Out(2,4,"tener? ");
            __delay_ms(2000);
            LATEbits.LATE2=1;
            I2C_Master_Start();
            I2C_Master_Write(0x20);
            I2C_Master_Write(0x01);
            I2C_Master_Stop();
            __delay_ms(200);
            while(PORTEbits.RE0==0 && PORTEbits.RE1==0 ){//Bucle para la recepción del dato para selección de cuarto
                LATCbits.LATC0=1;
            }
            
            I2C_Master_Start();
            I2C_Master_Write(0x21);
            input = I2C_Master_Read(0);
            I2C_Master_Stop();
            __delay_ms(200);
            LATEbits.LATE2=0;LATCbits.LATC0=0;
            switch(input){//Selección de cuarto
                case 49:{
                    Lcd_Cmd(LCD_CLEAR);
                    __delay_ms(100);
                    Lcd_Out(1,1,"Cuarto Normal");
                    Lcd_Out(2,1,"Costo: $250");
                    __delay_ms(2000);
                    break;
                }
                case 50:{
                    Lcd_Cmd(LCD_CLEAR);
                    __delay_ms(100);
                    Lcd_Out(1,1,"Con Jacuzzi");
                    Lcd_Out(2,1,"Costo: $450");
                    __delay_ms(2000);
                    Lcd_Cmd(LCD_CLEAR);
                    __delay_ms(100);
//                    Lcd_Out(1,1,"Ingrese su pago");
//                    LATEbits.LATE2=1;
//                    __delay_ms(1000);
//                    Adquisicion_Pago();
                    break;
                }
                case 51:{
                    Lcd_Cmd(LCD_CLEAR);
                    __delay_ms(100);
                    Lcd_Out(1,1,"Master Suite");
                    Lcd_Out(2,1,"Costo: $600");
                    __delay_ms(2000);
                    break;
                }
            } 
        }
        else{//Pluma cerrada
            while(PORTBbits.RB7==1 && PORTBbits.RB6==1){
                LATCbits.LATC2=1;
                __delay_ms(2);
                LATCbits.LATC2=0;
                __delay_ms(18);
            }
        }
    }
}
void Adquisicion_Pago(void){
    unsigned char palabra[17];
    LATEbits.LATE2=1;
    I2C_Master_Start();
    I2C_Master_Write(0x20);
    I2C_Master_Write(0x02);
    I2C_Master_Stop();
    __delay_ms(200);
    while(PORTEbits.RE0==0 && PORTEbits.RE1==0 ){//Bucle para la recepción del dato para selección de cuarto
        LATCbits.LATC0=1;
    }
    
    I2C_Master_Start();
    I2C_Master_Write(0x21);
    input = I2C_Master_Read(0);
    I2C_Master_Stop();
    __delay_ms(200);
    LATEbits.LATE2=1;LATCbits.LATC0=0;
    sprintf(palabra,"$:%d",input);
    Lcd_Out2(2,1,palabra);
    
}