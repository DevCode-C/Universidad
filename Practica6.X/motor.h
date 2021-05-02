#include "flex_lcd.h"

#define intm1 PORTAbits.RA0
#define intm2 PORTAbits.RA1
#define intm3 PORTAbits.RA2
#define intm4 PORTAbits.RA3
void secuencia1(void);
void secuencia2(void);
void secuencia3(void);
void secuencia3_Izq(void);
void secuencia2_Izq(void);
void secuencia1_Izq(void);
void half_step(long int x,short int y);
void full_step(long int x,short int y);
void wave_step(long int x,short int y);
void initM(void){
    TRISA=0xF0;
    PORTA=0x00;
}
void secuencia1(void){
    intm1=1; intm2=1; intm3=0; intm4=0;
    __delay_ms(100);
    intm1=0; intm2=1; intm3=1; intm4=0;
    __delay_ms(100);
    intm1=0; intm2=0; intm3=1; intm4=1;
    __delay_ms(100);
    intm1=1; intm2=0; intm3=0; intm4=1;
    __delay_ms(100);
}
void secuencia2(void){
    intm1=1; intm2=0; intm3=0; intm4=0;
    __delay_ms(10);
    intm1=0; intm2=1; intm3=0; intm4=0;
    __delay_ms(10);
    intm1=0; intm2=0; intm3=1; intm4=0;
    __delay_ms(10);
    intm1=0; intm2=0; intm3=0; intm4=1;
    __delay_ms(10);
}
void secuencia3(void){
    intm1=1; intm2=0; intm3=0; intm4=0;
    __delay_ms(10);
    intm1=1; intm2=1; intm3=0; intm4=0;
    __delay_ms(10);
    intm1=0; intm2=1; intm3=0; intm4=0;
    __delay_ms(10);
    intm1=1; intm2=1; intm3=1; intm4=0;
    __delay_ms(10);
    intm1=0; intm2=0; intm3=1; intm4=0;
    __delay_ms(10);
    intm1=0; intm2=0; intm3=1; intm4=1;
    __delay_ms(10);
    intm1=0; intm2=0; intm3=0; intm4=1;
    __delay_ms(10);
    intm1=1; intm2=0; intm3=0; intm4=1;
    __delay_ms(10);
}