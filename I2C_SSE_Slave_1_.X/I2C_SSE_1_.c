/*
 * File:   I2C_SSE_1_.c
 * Author: Emmanuel
 *
 * Created on 5 de mayo de 2019, 11:09 PM
 */
#include "config2.h"
#include <pic18f4550.h>
#define _XTAL_FREQ 12000000
#include "I2C_Slave.h"
#include "flex_lcd.h"
short input,output,temp;//Variables para la comunicación I2C
void main(void) {
    ADCON1=0x0F;
    I2C_Slave_Init(0x01);//Inicialización de la comunicación I2C en modo esclavo, dirección 0x01
    //Declaración de Puertos
    TRISBbits.TRISB7=1;//RB7 como entrada
    TRISBbits.TRISB6=1;//RB6 como entrada
    TRISCbits.TRISC2=0;//LATC2 como salida
    TRISEbits.TRISE0=0;//LATE0 como salida
    TRISEbits.TRISE1=0;//LATE1 como salida
    TRISEbits.TRISE2=1;//RE2 como entrada
    //Declaracion de estados en 0
    PORTBbits.RB7=0;//Poniendo a cero para evitar cualquier error
    PORTBbits.RB6=0;//Poniendo a cero para evitar cualquier error
    LATCbits.LATC2=0;//Poniendo a cero para evitar cualquier error
    LATEbits.LATE0=0;//Poniendo a cero para evitar cualquier error
    LATEbits.LATE1=0;//Poniendo a cero para evitar cualquier error
    PORTEbits.RE2=0;//Poniendo a cero para evitar cualquier error
    
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
//            while(PORTEbits.RE2==1){//Bucle para la recepción del dato para selección de cuarto
//                LATE0=1;
//            }
            
            switch(input){//Selección de cuarto
                case 0x10:{
                    Lcd_Cmd(LCD_CLEAR);
                    __delay_ms(100);
                    Lcd_Out(1,1,"Cuarto Normal");
                    Lcd_Out(2,1,"Costo: $250");
                    __delay_ms(2000);
                    break;
                }
                case 0x11:{
                    Lcd_Cmd(LCD_CLEAR);
                    __delay_ms(100);
                    Lcd_Out(1,1,"Con Jacuzzi");
                    Lcd_Out(2,1,"Costo: $450");
                    __delay_ms(2000);
                    break;
                }
                case 0x12:{
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
            while(PORTBbits.RB7==1 || PORTBbits.RB6==1){
                LATCbits.LATC2=1;
                __delay_ms(2);
                LATCbits.LATC2=0;
                __delay_ms(18);
            }
        }
    }
}
void __interrupt() isr(){
    if(SSPIF == 1){
       SSPCON1bits.CKP = 0;
       if ((SSPCON1bits.SSPOV) || (SSPCON1bits.WCOL)){//
             temp = SSPBUF;            
             SSPCON1bits.SSPOV = 0; 
             SSPCON1bits.WCOL = 0;   
             SSPCON1bits.CKP = 1;
        }
        if(!SSPSTATbits.D_nA && !SSPSTATbits.R_nW) {//Entrada de datos
           temp = SSPBUF;
           while(!BF);
           input = SSPBUF;
           SSPCON1bits.CKP = 1;
           SSPM3 = 0;
        }
        else if(!SSPSTATbits.D_nA && SSPSTATbits.R_nW){//salida de datos
           temp = SSPBUF;
           BF = 0;
           SSPBUF = output ;
           SSPCON1bits.CKP = 1;
           while(SSPSTATbits.BF);
        }
       
       SSPIF = 0;
    }
}