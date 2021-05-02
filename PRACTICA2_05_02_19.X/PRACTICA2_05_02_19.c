/*
 * File:   PRACTICA2_05_02_19.c
 * Author: Emmanuel
 *
 * Created on 3 de febrero de 2019, 06:25 PM
 */
#include "config2.h"
#include <pic18f4550.h>
#define _XTAL_FREQ 8000000
int suma(int s1, int s2);
int resta(int s1, int s2);
int mult(int s1, int s2);
int scv(int s1, int s2);
void main(void) {
    int D1,D2,R0;
    short int SEL;
    TRISD=0x00;//Declaración de puertos
    TRISB=0xFF;
    TRISCbits.RC0=1;
    TRISCbits.RC1=0;
    TRISCbits.RC2=0;
    INICIO://EL REGRESO CON GOTO
    LATD=0x00;
    LATB=0x00;
    LATCbits.LATC0=0;
    LATCbits.LATC1=0;
    LATCbits.LATC2=0;
    //SELECCIÓN DEL PRIMER DIGITO
    while(PORTCbits.RC0==1){
        D1=PORTB;
        LATD=D1;
    }
    LATCbits.LATC1=1;
    __delay_ms(500);
    LATD=0x00;
    LATCbits.LATC1=0;
    //SELECCIÓN DE SEGUNDO DIGITO
    while(PORTCbits.RC0==1){
        D2=PORTB;
        LATD=D2;
    }
    LATCbits.LATC1=1;
    __delay_ms(500);
    LATD=0x00;
    LATCbits.LATC1=0;
    //Selección de operación 
    SELECCION:
    while(PORTCbits.RC0==1){
        LATCbits.LATC2=1;
        SEL=PORTB;
    }
    LATCbits.LATC1=1;
    __delay_ms(500);
    LATCbits.LATC1=0;
    LATCbits.LATC2=0;
    switch(SEL){//Suma
        case 1: {R0=0;
            R0=suma(D1,D2);
            if(R0>255){
                int i;
                for(i=0;i<255;i+=10){
                    PORTD=i;
                    __delay_ms(100);
                }
                goto INICIO;
            }
            else{
                while(PORTCbits.RC0==1){
                    PORTD=R0;
                }
                __delay_ms(1000);
                goto INICIO;
            }
        }//Resta
        case 2: {R0=0;
            R0=resta(D1,D2);
            while(PORTCbits.RC0==1){
                PORTD=R0;
            }
            __delay_ms(1000);
            PORTCbits.RC1=0;
            PORTCbits.RC2=0;
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
        while(PORTCbits.RC0==1){
            PORTCbits.RC1=1;
            PORTCbits.RC2=1;
        }
        __delay_ms(2000);
        return x;
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