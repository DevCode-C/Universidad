/* 
 * File:   newmain.c
 * Author: Emmanuel
 *
 * Created on 13 de febrero de 2019, 10:18 PM
 */
#include "newfile.h"
#include <pic18f4550.h>
#define _XTAL_FREQ 8000000
void puertos(){
    ADCON1=0x0F;
    TRISD=0x00;
    TRISAbits.RA0=0;
    TRISAbits.RA1=0;
    TRISAbits.RA2=0;
    TRISAbits.RA3=0;
    TRISBbits.RB0=1;
    TRISBbits.RB1=1;
    TRISBbits.RB2=1;
    TRISBbits.RB3=1;
}
void timer(){
    INTCONbits.GIE=0;
    T0CONbits.T08BIT=1;
    T0CONbits.T0CS=0;
    T0CONbits.T0SE=0;
    T0CONbits.T0PS=0b111;
    T0CONbits.TMR0ON=1;
    INTCONbits.TMR0IE=1;
    INTCONbits.TMR0IF=0;
    INTCONbits.PEIE=1;
    INTCONbits.GIE=1;
}
int cont=0;
void main(void) {
    puertos();
    timer();
    TMR0=60;
    PORTD=0;
    while(1);

}
void interrupt ggdg(void){
    if(INTCONbits.TMR0IF){
        TMR0=60;
        INTCONbits.TMR0IF=0;
        cont++;
        if(cont==40){
        PORTD=PORTD+1;
        cont=0;
        }
        
    }
}