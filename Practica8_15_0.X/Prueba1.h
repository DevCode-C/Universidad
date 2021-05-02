#include "flex_lcd.h"
#include <xc.h>
#include <stdio.h>
#define intm1 PORTAbits.RA0
#define intm2 PORTAbits.RA1
#define intm3 PORTAbits.RA2
#define intm4 PORTAbits.RA3
#define tiempo 5
void Full_stepper(void);
void Wave_stepper(void);
void Half_stepper(void);
void Half_stepper_izq(void);
void Full_stepper_izq(void);
void Wave_stepper_izq(void);
void opt_Full_stepper(long int steps, short int direttion );
void opt_Wave_stepper(long int steps, short int direttion );
void opt_Half_stepper(long int steps, short int direttion );
long int contador;

void initM(void){
    TRISA=0xF0;
    PORTA=0x00;
    contador=0;
}
void Full_stepper(void){
    intm1=1; intm2=1; intm3=0; intm4=0;
    __delay_ms(tiempo);contador++;
    intm1=0; intm2=1; intm3=1; intm4=0;
    __delay_ms(tiempo);contador++;
    intm1=0; intm2=0; intm3=1; intm4=1;
    __delay_ms(tiempo);contador++;
    intm1=1; intm2=0; intm3=0; intm4=1;
    __delay_ms(tiempo);contador++;
}
void Wave_stepper(void){
    intm1=1; intm2=0; intm3=0; intm4=0;
    __delay_ms(tiempo);contador++;
    intm1=0; intm2=1; intm3=0; intm4=0;
    __delay_ms(tiempo);contador++;
    intm1=0; intm2=0; intm3=1; intm4=0;
    __delay_ms(tiempo);contador++;
    intm1=0; intm2=0; intm3=0; intm4=1;
    __delay_ms(tiempo);contador++;
}
void Half_stepper(void){
    intm1=1; intm2=0; intm3=0; intm4=0;
    __delay_ms(tiempo);contador++;
    intm1=1; intm2=1; intm3=0; intm4=0;
    __delay_ms(tiempo);contador++;
    intm1=0; intm2=1; intm3=0; intm4=0;
    __delay_ms(tiempo);contador++;
    intm1=1; intm2=1; intm3=1; intm4=0;
    __delay_ms(tiempo);contador++;
    intm1=0; intm2=0; intm3=1; intm4=0;
    __delay_ms(tiempo);contador++;
    intm1=0; intm2=0; intm3=1; intm4=1;
    __delay_ms(tiempo);contador++;
    intm1=0; intm2=0; intm3=0; intm4=1;
    __delay_ms(tiempo);contador++;
    intm1=1; intm2=0; intm3=0; intm4=1;
    __delay_ms(tiempo);contador++;
}

void Full_stepper_izq(void){
    intm1=1; intm2=0; intm3=0; intm4=1;
    __delay_ms(tiempo);contador++;
    intm1=0; intm2=0; intm3=1; intm4=1;
    __delay_ms(tiempo);contador++;
    intm1=0; intm2=1; intm3=1; intm4=0;
    __delay_ms(tiempo);contador++;
    intm1=1; intm2=1; intm3=0; intm4=0;
    __delay_ms(tiempo);contador++;
}
void Wave_stepper_izq(void){
    intm1=1; intm2=0; intm3=0; intm4=0;
    __delay_ms(tiempo);contador++;
    intm1=0; intm2=0; intm3=0; intm4=1;
    __delay_ms(tiempo);contador++;
    intm1=0; intm2=0; intm3=1; intm4=0;
    __delay_ms(tiempo);contador++;
    intm1=0; intm2=1; intm3=0; intm4=0;
    __delay_ms(tiempo);contador++;
}
void Half_stepper_izq(void){
    intm1=1; intm2=0; intm3=0; intm4=0;
    __delay_ms(tiempo);contador++;
    intm1=1; intm2=0; intm3=0; intm4=1;
    __delay_ms(tiempo);contador++;
    intm1=0; intm2=0; intm3=0; intm4=1;
    __delay_ms(tiempo);contador++;
    intm1=0; intm2=0; intm3=1; intm4=1;
    __delay_ms(tiempo);contador++;
    intm1=0; intm2=0; intm3=1; intm4=0;
    __delay_ms(tiempo);contador++;
    intm1=0; intm2=1; intm3=1; intm4=0;
    __delay_ms(tiempo);contador++;
    intm1=0; intm2=1; intm3=0; intm4=0;
    __delay_ms(tiempo);contador++;
    intm1=1; intm2=1; intm3=0; intm4=0;
    __delay_ms(tiempo);contador++;
}
void opt_Full_stepper(long int steps, short int direttion ){
    if(direttion==1){contador=0;
        while(steps>contador){
            Full_stepper();
        }
    direttion=0;contador=0;
    }
    else if(direttion==2){contador=0;
        while(steps>contador){
            Full_stepper_izq();    
        }
    direttion=0;contador=0;
    }else{
         direttion=0;contador=0;
         Lcd_Cmd(LCD_CLEAR);
        __delay_ms(100); 
        Lcd_Out(1,4,"Opcion");
        Lcd_Out(2,2,"incorrecta");
        __delay_ms(1000);
        Lcd_Cmd(LCD_CLEAR);
    }
}
void opt_Wave_stepper(long int steps, short int direttion){
    if(direttion==1){contador=0;
        while(steps>contador){
            Wave_stepper();
        }
    direttion=0;contador=0;
    }
    else if(direttion==2){contador=0;
        while(steps>contador){
            Wave_stepper_izq();
        }
    direttion=0;contador=0;
    }else{
        direttion=0;contador=0;
        Lcd_Cmd(LCD_CLEAR);
        __delay_ms(100); 
        Lcd_Out(1,4,"Opcion");
        Lcd_Out(2,2,"incorrecta");
        __delay_ms(1000);
        Lcd_Cmd(LCD_CLEAR);
    }
}
void opt_Half_stepper(long int steps, short int direttion){
    if(direttion==1){contador=0;
        while(steps>contador){
            Half_stepper();
        }
    direttion=0;contador=0;
    }
    else if(direttion==2){contador=0;
        while(steps>contador){
            Half_stepper_izq();
        }
    direttion=0;contador=0;
    }else{
        direttion=0;contador=0;
        Lcd_Cmd(LCD_CLEAR);
        __delay_ms(100); 
        Lcd_Out(1,4,"Opcion");
        Lcd_Out(2,2,"incorrecta");
        __delay_ms(1000);
        Lcd_Cmd(LCD_CLEAR);
    }
}