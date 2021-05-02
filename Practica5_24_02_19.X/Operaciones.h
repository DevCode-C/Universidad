#include "flex_lcd.h"
#include <stdio.h>
unsigned char palabra[17];
unsigned char numero1[17];
unsigned char numero2[17];
unsigned char numero3[17];

void resta(float s1, float s2);
void multiplicacion(float s1, float s2);
void vid(float s1, float s2);


void resta(float s1, float s2){
    float R=0;
    R=s1-s2;
    if(s2>s1){
        R=R*(-1);
        while(PORTCbits.RC1==1){
            sprintf(numero1,"%0.0f +",s1);
            sprintf(numero2," %0.0f",s2);
            sprintf(palabra,"Resta= -%0.3f",R);
            Lcd_Out2(1,1,numero1);
            Lcd_Out2(1,6,numero2);
            Lcd_Out2(2,1,palabra);
        }
    }else{
        while(PORTCbits.RC1==1){
            sprintf(numero1,"%0.0f -",s1);
            sprintf(numero2," %0.0f",s2);
            sprintf(palabra,"Resta= %0.3f",R);
            Lcd_Out2(1,1,numero1);
            Lcd_Out2(1,6,numero2);
            Lcd_Out2(2,1,palabra);
        }
    }
}
void multiplicacion(float s1, float s2){
    float R=0;
    R=s1*s2;
    while(PORTCbits.RC1==1){
        sprintf(numero1,"%0.0f *",s1);
        sprintf(numero2," %0.0f",s2);
        sprintf(palabra,"Mult= %0.3f",R);
        Lcd_Out2(1,1,numero1);
        Lcd_Out2(1,6,numero2);
        Lcd_Out2(2,1,palabra);
        }
}
void vid(float s1, float s2){
    float R=0;
    R=s1/s2;
    if(s2==0){
        while(PORTCbits.RC1==1){
            Lcd_Out(1,1,"Syntax Error");
        }
    }else{
        while(PORTCbits.RC1==1){
            sprintf(numero1,"%0.0f /",s1);
            sprintf(numero2," %0.0f",s2);
            sprintf(palabra,"Div= %0.3f",R);
            Lcd_Out2(1,1,numero1);
            Lcd_Out2(1,6,numero2);
            Lcd_Out2(2,1,palabra);
        }
    }
}