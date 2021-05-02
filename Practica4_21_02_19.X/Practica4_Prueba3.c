/*
 * File:   Practica4_Prueba3.c
 * Author: Emmanuel
 *
 * Created on 19 de febrero de 2019, 07:50 PM
 */
#include "Config1.h"
#include <pic18f4550.h>
#define _XTAL_FREQ 8000000
unsigned char Tabla[]={0x7E,0x30,0x6D,0x79,0x33,0x5B,0x5F,0x71,0xFF,0xF3};
void conteo(void);
void display(unsigned char veces);
int seleccion(void);
int unidadesS1=0;
int unidadesS2=0;
int Decenas1=0;
int Decenas2=0;
short int Dato=0;

void main(void) {
ADCON1=0x0F;
TRISD=0x00;
TRISBbits.RB0=0;
TRISBbits.RB1=0;
TRISBbits.RB2=0;
TRISBbits.RB3=0;
TRISBbits.RB4=1;
TRISBbits.RB7=1;

TRISAbits.RA0=1;
TRISAbits.RA1=1;
TRISAbits.RA2=1;
TRISAbits.RA3=1;
TRISAbits.RA4=1;

LATBbits.LATB0=0;
LATBbits.LATB1=0;
LATBbits.LATB2=0;
LATBbits.LATB3=0;
LATD=0x00;
short int cont=0;
short int sel=0;
while(sel<5){
    if(sel==0 && PORTBbits.RB4==1){
        unidadesS1=seleccion();
        if(unidadesS1>9){unidadesS1=9;}
        else if (unidadesS1<0){unidadesS1=0;}
        else if(PORTBbits.RB4==1 && PORTAbits.RA1==0){sel=1;}
    }
   // __delay_ms(100);
    if(sel==1 && PORTBbits.RB4==1){
        unidadesS2=seleccion();
        if(unidadesS2>5){unidadesS2=5;}
        else if (unidadesS2<0){unidadesS2=0;}
        else if(PORTBbits.RB4==1 && PORTAbits.RA0==0){sel=2;}
    }
   // __delay_ms(100);
    if(sel==2 && PORTBbits.RB4==1){
        Decenas1=seleccion();
        if(Decenas1>9){Decenas1=9;}
        else if (Decenas1<0){Decenas1=0;}
        else if(PORTBbits.RB4==1 && PORTBbits.RB7==0){sel=3;}
    }
    //__delay_ms(100);
    if(sel==3 && PORTBbits.RB4==1){
        Decenas2=seleccion();
        if(Decenas2>5){Decenas2=5;}
        else if (Decenas2<0){Decenas2=0;}
        else if(PORTBbits.RB4==1 && PORTAbits.RA1==0){sel=4;}
    }
   // __delay_ms(100);
    if(sel==4 && PORTAbits.RA0==0 && PORTAbits.RA1==0){
        sel=6;
    }
    display(22);
}
while(1){
    if(PORTBbits.RB7==0 && PORTBbits.RB4==1){
        cont=1;//EL INICION
    }
    if(PORTBbits.RB7==1 && PORTBbits.RB4==0){
        cont=2;//LA PAUSA
    }
    if(cont==1){
        conteo();   
    }
    display(45);
}
}
void display(unsigned char veces){
    while(veces){
        LATD=Tabla[unidadesS1];
        LATBbits.LATB3=1;
        __delay_ms(5);
        LATBbits.LATB3=0;
        
        LATD=Tabla[unidadesS2];
        LATBbits.LATB2=1;
        __delay_ms(5);
        LATBbits.LATB2=0;
        
        LATD=Tabla[Decenas1];
        LATBbits.LATB1=1;
        __delay_ms(5);
        LATBbits.LATB1=0;
        
        LATD=Tabla[Decenas2];
        LATBbits.LATB0=1;
        __delay_ms(5);
        LATBbits.LATB0=0;
        veces--;
    }
}
void conteo(void){
    short int condicion=0;
    short int condicion2=0;
    
    unidadesS1--;
    if(unidadesS1<0){
        unidadesS1=9;
        unidadesS2--;
        if(unidadesS2<0){
            unidadesS2=5;
            Decenas1--;
            if(Decenas1<0){
                Decenas1=9;
                Decenas2--;
                if(Decenas2<0){
                    Decenas2=0;
                }
            }
        }
    }
   /* if(unidadesS1<0 && unidadesS2!=0){
        unidadesS1=9;
        unidadesS2--;
        if(unidadesS2<0 && Decenas1>0){
            unidadesS2=5;
            Decenas1--;
            if((Decenas1<0) && (Decenas2>0)){
                Decenas1=5;
                Decenas2--;
                if(Decenas2<0){
                    Decenas2=0;
                    condicion=1;
                }
            }
            else if(Decenas1<0 && Decenas2==0 && condicion==1){
                Decenas1=0;
                Decenas2=0;
            }
        }
    else if(unidadesS2==0 && Decenas1==0 && Decenas2==0 && condicion1==1){
            unidadesS2=0;
        }
    }
    else if(unidadesS1==0 && unidadesS2==0 && Decenas1==0 && Decenas2==0){
        unidadesS1=0;
     }*/
   
}
int seleccion(void){
    if(PORTAbits.RA2==0 && PORTAbits.RA3==1){
        Dato++;
    }else if(PORTAbits.RA3==0 && PORTAbits.RA2==1){
        Dato--;
    }
   
    return Dato;
}