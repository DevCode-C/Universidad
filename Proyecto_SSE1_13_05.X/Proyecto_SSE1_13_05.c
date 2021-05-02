/*
 * File:   Proyecto_SSE1_13_05.c
 * Author: Emmanuel
 *
 * Created on 13 de mayo de 2019, 09:08 PM
 */
#include "config2.h"
#include <pic18f4550.h>
#define _XTAL_FREQ 12000000
#include "flex_lcd.h"
#include "UART.h"
#include <stdio.h>
static float P_Master=500.0,P_jacuzzi=450.0,P_normal=250.0;//Precios de las habitaciones
unsigned char valor,datos,ptr_valor;//Datos para el teclado
short int contador=0,count,r_nomal=0,r_jacuzzi=0,r_master=0;//Contadores 
unsigned long num_hab[3][6],fill_room;//Contraseñas de las habitaciones
unsigned char room_normal[6];//habitaciones
unsigned char room_jacuzzi[6];//habitaciones
unsigned char room_master[6];//habitaciones
unsigned char palabra[17],palabra1[17],palabra2[17],palabra3[17];//Para convertir datos e imprimirlos

void teclado(void);
//void password(int tipo, int cuarto);
//void pago_de_Habitacion(int Room_Type);
void pago_de_Habitaciones(int price);//Pago de las diferentes habitaciones
void clean_rooms(void);//Para obtener cuartos libres
void envio_UART_Tx(char Tx, unsigned char informacion, int lugar );//Envio de datos por UART
void opciones(void);

void main(void) {
    UART_Init(9600);//Inicialización de la comunicación UART
    INTCON2bits.RBPU=0;
    ADCON1=0x0F;//Solo entradas y salidas digitales
    TRISDbits.RD6=1;//Sensores de proximidad
    TRISDbits.RD7=1;//Sensores de proximidad
    TRISCbits.TRISC0=0;//Salida del Servomotor
    TRISB=0xF0;
    TRISE=0;
    TRISAbits.RA0=1;
    
    Lcd_Init();//Inicialización del display LCD
    Lcd_Cmd(LCD_CLEAR);//Limpia el display
    Lcd_Cmd(LCD_CURSOR_OFF);//Elimina el cursor
    __delay_ms(100);
    
    PORTDbits.RD6=0;//Estado bajo para evitar fallas
    PORTDbits.RD7=0;//Estado bajo para evitar fallas
    LATCbits.LATC0=0;//Estado bajo para evitar fallas
    PORTB=0x00;//Estado bajo para evitar fallas
    LATE=0b000;
    PORTAbits.RA0=0;
    r_jacuzzi=0;
    r_master=0;
    r_nomal=0;
     
    while(1){//Ciclo infinito
        if(PORTDbits.RD7==0 || PORTDbits.RD6==0){//Cuando hay un auto entranda
            if((r_nomal==0)&&(r_jacuzzi==0)&&(r_master==0)){
                UART_Tx(250);
            }
            
            Lcd_Cmd(LCD_CLEAR);
            __delay_ms(100);
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
            Lcd_Out(1,1,"Habitaciones ");
            Lcd_Out(2,4,"disponibles ");
            __delay_ms(2000);
            Lcd_Cmd(LCD_CLEAR);
            Lcd_Out(1,1,"Habt Normal");
           // m_rooms(room_normal,6);
            sprintf(palabra,"Displonible:%d",r_nomal);
            Lcd_Out2(2,1,palabra);
            __delay_ms(2000);
            Lcd_Cmd(LCD_CLEAR);
            Lcd_Out(1,1,"Habt Jacuxxxi");
           // m_rooms(room_jacuzzi,6);
            sprintf(palabra1,"Displonible:%d",r_jacuzzi);
            Lcd_Out2(2,1,palabra1);
            __delay_ms(2000);
            Lcd_Cmd(LCD_CLEAR);
            Lcd_Out(1,1,"Master Suite");
           // m_rooms(room_master,6);
            sprintf(palabra2,"Displonible:%d",r_master);
            Lcd_Out2(2,1,palabra2);
            __delay_ms(2000);
            Lcd_Cmd(LCD_CLEAR);
            Lcd_Out(1,1,"Esc Habitacion");
            valor=0;
            while(valor!='*'){
                teclado();
                if(valor=='1' || valor=='2' || valor=='3' || valor== 'A'){
                    ptr_valor=valor;
                    sprintf(palabra,"Tipo:%c",ptr_valor);
                    Lcd_Out2(2,1,palabra);
                }
            }
            valor=0;
            if((r_nomal==0)&&(r_jacuzzi==0)&&(r_master==0)){
                valor=0;
                Lcd_Cmd(LCD_CLEAR);
                __delay_ms(100);
                Lcd_Out(1,1,"Todo lleno");
                Lcd_Out(2,1,"***************");
                __delay_ms(2000);
                Lcd_Cmd(LCD_CLEAR);
                __delay_ms(100);
                Lcd_Out(1,1,"Opciones");
                Lcd_Out(2,1,"***************");
                __delay_ms(2000);
                Lcd_Cmd(LCD_CLEAR);
                __delay_ms(100);
                Lcd_Out(1,1,"A:Admin");
                Lcd_Out(2,1,"B:Esperar");
                __delay_ms(2000);
                Lcd_Cmd(LCD_CLEAR);
                __delay_ms(100);
                Lcd_Out(1,1,"C:Retirarse");
                Lcd_Out(2,1,"***************");
                __delay_ms(2000);
                Lcd_Cmd(LCD_CLEAR);
                __delay_ms(100);
                while(valor!='*'){
                    teclado();
                    if((valor=='A')||(valor=='B')||(valor=='C')){
                        fill_room=valor;
                        sprintf(palabra2,"Opcion:%c",fill_room);
                        Lcd_Out2(2,1,palabra2);
                    }
                }
                switch(fill_room){
                    case 'A':{
                        valor=0;
                        Lcd_Cmd(LCD_CLEAR);
                        __delay_ms(100);
                        Lcd_Out(1,1,"Permitame ir");
                        Lcd_Out(2,1,"con el ADMIN");
                        __delay_ms(1500);
                        Lcd_Cmd(LCD_CLEAR);
                        __delay_ms(100);
                        Lcd_Out(1,1,"Checaremos las");
                        Lcd_Out(2,1,"habitaciones");
                        __delay_ms(1500);
                        Lcd_Cmd(LCD_CLEAR);
                        __delay_ms(100);
                        Lcd_Out(1,1,"***************");
                        Lcd_Out(2,1,"***************");
                        __delay_ms(1500);
                        Lcd_Cmd(LCD_CLEAR);
                        __delay_ms(100);
                        clean_rooms();
                        __delay_ms(1000);
                        break; 
                    }
                    case 'B':{
                        Lcd_Cmd(LCD_CLEAR);
                        __delay_ms(100);
                        Lcd_Out(1,1,"PASE A LA");
                        Lcd_Out(2,1,"SALA DE ESPERA");
                        __delay_ms(1500);
                        Lcd_Cmd(LCD_CLEAR);
                        __delay_ms(100);
                        Lcd_Out(1,1,"***************");
                        Lcd_Out(2,1,"***************");
                        __delay_ms(1500);
                        Lcd_Cmd(LCD_CLEAR);
                        __delay_ms(100);
                        count=0;
                        while(count!=100){
                            LATCbits.LATC0=1;
                            __delay_ms(1);
                            LATCbits.LATC0=0;
                            __delay_ms(19);
                            count++;
                        }
                        __delay_ms(5000);
                        ptr_valor=0;
                        break;
                    }
                    case 'C':{
                        ptr_valor='A';
                        break;
                    }
                }
            }
            switch(ptr_valor){
                case '1':{valor=0;
                    if(r_nomal!=0){
                        room_normal[r_nomal]='F';
                        Lcd_Cmd(LCD_CLEAR);
                        __delay_ms(100);
                        Lcd_Out(1,1,"Habitacion");
                        Lcd_Out(2,1,"Normal");
                        __delay_ms(2000);
                        Lcd_Cmd(LCD_CLEAR);
                        __delay_ms(100);
                        pago_de_Habitaciones(250);
                        envio_UART_Tx(10,r_nomal,0);
                         while(count!=100){
                            LATCbits.LATC0=1;
                            __delay_ms(1);
                            LATCbits.LATC0=0;
                            __delay_ms(19);
                            count++;
                        }
                        r_nomal--;
                    }
                    else{
                        Lcd_Cmd(LCD_CLEAR);
                        __delay_ms(100);
                        Lcd_Out(1,5,"Sin ");
                        Lcd_Out(2,1,"Habitaciones de");
                        Lcd_Cmd(LCD_CLEAR);
                        __delay_ms(100);
                        Lcd_Out(1,5,"ese tipo ");
                        Lcd_Out(2,1,"disponibles");
                        Lcd_Cmd(LCD_CLEAR);
                        __delay_ms(100);
                        opciones();
                        break;
                    }
                    break;
                }
                case '2':{valor=0;
                    if(r_jacuzzi!=0){
                        room_jacuzzi[r_jacuzzi]='F';
                        Lcd_Cmd(LCD_CLEAR);
                        __delay_ms(100);
                        Lcd_Out(1,1,"Habitacion");
                        Lcd_Out(2,1,"Jacuxxxi");
                        __delay_ms(2000);
                        Lcd_Cmd(LCD_CLEAR);
                        __delay_ms(100);
                        pago_de_Habitaciones(450);
                        envio_UART_Tx(20,r_jacuzzi,0);
                         while(count!=100){
                            LATCbits.LATC0=1;
                            __delay_ms(1);
                            LATCbits.LATC0=0;
                            __delay_ms(19);
                            count++;
                        }
                        r_jacuzzi--;
                    }
                    else{
                        Lcd_Cmd(LCD_CLEAR);
                        __delay_ms(100);
                        Lcd_Out(1,5,"Sin ");
                        Lcd_Out(2,1,"Habitaciones de");
                        Lcd_Cmd(LCD_CLEAR);
                        __delay_ms(100);
                        Lcd_Out(1,5,"ese tipo ");
                        Lcd_Out(2,1,"disponibles");
                        Lcd_Cmd(LCD_CLEAR);
                        __delay_ms(100);
                        opciones();
                        break;
                    }
                    break;
                }
                case '3':{valor=0;
                    if(r_master!=0){
                        room_master[r_master]='F';
                        Lcd_Cmd(LCD_CLEAR);
                        __delay_ms(100);
                        Lcd_Out(1,1,"Habitacion");
                        Lcd_Out(2,1,"Master");
                        __delay_ms(2000);
                        Lcd_Cmd(LCD_CLEAR);
                        __delay_ms(100);
                        pago_de_Habitaciones(600);
                        envio_UART_Tx(30,r_master,0);
                         while(count!=100){
                            LATCbits.LATC0=1;
                            __delay_ms(1);
                            LATCbits.LATC0=0;
                            __delay_ms(19);
                            count++;
                        }
                        r_master--;
                    }
                    else{
                        Lcd_Cmd(LCD_CLEAR);
                        __delay_ms(100);
                        Lcd_Out(1,5,"Sin ");
                        Lcd_Out(2,1,"Habitaciones de");
                        Lcd_Cmd(LCD_CLEAR);
                        __delay_ms(100);
                        Lcd_Out(1,5,"ese tipo ");
                        Lcd_Out(2,1,"disponibles");
                        Lcd_Cmd(LCD_CLEAR);
                        __delay_ms(100);
                        opciones();
                        break;
                    }
                    break;
                }
                case 'A':{valor=0;
                    Lcd_Cmd(LCD_CLEAR);
                    __delay_ms(100);
                    Lcd_Out(1,3,"Que le vaya");
                    Lcd_Out(2,5,"bien");
                    __delay_ms(2000);
                    Lcd_Cmd(LCD_CLEAR);
                    __delay_ms(100);
                    Lcd_Out(1,1,"Vuelva");
                    Lcd_Out(2,5,"Pronto");
                    __delay_ms(2000);
                    Lcd_Cmd(LCD_CLEAR);
                    __delay_ms(100);
                    count=0;
                    while(count!=100){
                        LATCbits.LATC0=1;
                        __delay_ms(1);
                        LATCbits.LATC0=0;
                        __delay_ms(19);
                        count++;
                    }
                    __delay_ms(5000);
                    break;
                }
                default:{
                    Lcd_Cmd(LCD_CLEAR);
                    __delay_ms(100);
                    break;
                }
            }
            if((r_nomal==0)&&(r_jacuzzi==0)&&(r_master==0)){
                UART_Tx(250);
            }
        }
        else{//Mientras no haya nada, pluma cerrada
            Lcd_Out(1,2,"BIENVENIDO");
            Lcd_Out(2,2,"PASE USTED");
            while(PORTDbits.RD7==1 && PORTDbits.RD6==1){//Ciclo para mantener la pluma abajo
                LATCbits.LATC0=1;
                __delay_ms(2);
                LATCbits.LATC0=0;
                __delay_ms(18);
                if(PORTAbits.RA0==0){
                    Lcd_Cmd(LCD_CLEAR);
                    __delay_ms(100);
                    clean_rooms();
                    UART_Tx(249);
                    break;
                }
            }
            Lcd_Cmd(LCD_CLEAR);
            __delay_ms(100);
        }
    }
}
void teclado(void){//Función teclado
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
//void password(int tipo, int cuarto){
//    Lcd_Out(1,1,"Password");
//    while(valor!='*'){
//        teclado();
//        if( (valor>='0') && (valor<='9')){
//            num_hab[tipo][cuarto]=(num_hab[tipo][cuarto])*10 +(valor-48);
//            sprintf(palabra1,":%d",num_hab[tipo][cuarto]);
//            Lcd_Out2(2,1,palabra1);
//        }
//    }
//    valor=0;
//    Lcd_Cmd(LCD_CLEAR);
//    __delay_ms(100);
//    Lcd_Out(1,1,"Password");
//    Lcd_Out(2,3,"Guardada");
//    __delay_ms(1000);
//    Lcd_Cmd(LCD_CLEAR);
//    __delay_ms(100);
//    
//}
void pago_de_Habitaciones(int price){
    unsigned char uso_local[17],uso_local2[17];
    short int circle = TRUE;
    float money=0,cambio=0;
    sprintf(palabra3,"$ %d",price);
    Lcd_Out(1,1,"Pago de");
    Lcd_Out2(2,1,palabra3);
    __delay_ms(1500);
    Lcd_Cmd(LCD_CLEAR);
    __delay_ms(100);
    sprintf(uso_local,"Costo $%d",price);
    while(circle){
        Lcd_Out2(1,1,uso_local);
        while(valor != '*'){
            teclado();
            if((valor>='0') && (valor<='9')){
                money=(money)*10 + (valor-48);
                sprintf(uso_local2,"Pago: %.2f",money);
                Lcd_Out2(2,1,uso_local2);
            }
        }
        if(money<price){valor=0;money=0;
            Lcd_Cmd(LCD_CLEAR);
            __delay_ms(100);
            Lcd_Out(1,1,"Pobre XD");
            Lcd_Out(2,1,"A conseguir");
            __delay_ms(1500);
            Lcd_Cmd(LCD_CLEAR);
            __delay_ms(100);
            Lcd_Out(1,1,"Dinero y rapido");
            Lcd_Out(2,1,"***************");
            __delay_ms(1000);
            Lcd_Cmd(LCD_CLEAR);
            __delay_ms(100);
        }
        else{valor=0;
            Lcd_Cmd(LCD_CLEAR);
            __delay_ms(100);
            cambio=(float)money-price;
            sprintf(uso_local,":%.2f",cambio);
            Lcd_Out(1,1,"Su cambio es");
            Lcd_Out2(2,1,uso_local);
            __delay_ms(1500);
            Lcd_Cmd(LCD_CLEAR);
            __delay_ms(100);
            Lcd_Out(1,1,"Gracias por su");
            Lcd_Out(2,4,"Pago");
            __delay_ms(1000);
            Lcd_Cmd(LCD_CLEAR);
            __delay_ms(100);
            circle=FALSE;
            break;
        }
    }
}
void clean_rooms(void){
    valor=0;
    unsigned char tipo=0,cuarto=0;
    unsigned char uso_local[17],uso_local2[17];
    int tipo_clean=0,cuarto_clean=0;
    Lcd_Out(1,1,"Seleccione");
    while(valor!='*'){
        teclado();
        if((valor=='1')||(valor=='2')||(valor=='3')){
            tipo=valor;
            sprintf(uso_local,"Tipo:%c",tipo);
            Lcd_Out2(2,1,uso_local);
        }
    }valor=0;
    while(valor!='*'){
        teclado();
        if((valor>='0')&&(valor<='5')){
            cuarto=valor;
            sprintf(uso_local2,"Hab:%c",cuarto);
            Lcd_Out2(2,8,uso_local2);
        }
    }
    switch(tipo){
        case '1':{
            r_nomal++;
            room_normal[cuarto]=0;
            break;
        }
        case '2':{
            r_jacuzzi++;
            room_jacuzzi[cuarto]=0;
            break;
        }
        case '3':{
            r_master++;
            room_master[cuarto]=0;
            break;
        }
    }
    valor=0;
    Lcd_Cmd(LCD_CLEAR);
    __delay_ms(100);
}
void envio_UART_Tx(char Tx, unsigned char informacion, int lugar ){//"lugar" es el sitio donde se quiere enviar datos."Tx" es modificacion 
    switch(lugar){
        case 0:{
            LATE=0b111;
            informacion+=Tx;
            UART_Tx(informacion);
            __delay_ms(100);
            LATE=0b000;
            break;
        }
        case 1:{
            LATE=0b110;
            break;
        }
        case 2:{
            LATE=0b101;
            break;
        }
        case 3:{
            LATE=0b100;
            break;
        }
    }
}
void opciones(void){
    Lcd_Cmd(LCD_CLEAR);
    __delay_ms(100);
    Lcd_Out(1,1,"Habitaciones");
    Lcd_Out(2,3,"***LLenas***");
    __delay_ms(2000);
    Lcd_Cmd(LCD_CLEAR);
    __delay_ms(100);
    Lcd_Out(1,1,"Opciones");
    Lcd_Out(2,1,"***************");
    __delay_ms(2000);
    Lcd_Cmd(LCD_CLEAR);
    __delay_ms(100);
    Lcd_Out(1,1,"A:Admin");
    Lcd_Out(2,1,"B:Esperar");
    __delay_ms(2000);
    Lcd_Cmd(LCD_CLEAR);
    __delay_ms(100);
    Lcd_Out(1,1,"C:Retirarse");
    Lcd_Out(2,1,"***************");
    __delay_ms(2000);
    Lcd_Cmd(LCD_CLEAR);
    __delay_ms(100);
    while(valor!='*'){
        teclado();
        if((valor=='A')||(valor=='B')||(valor=='C')){
            fill_room=valor;
            sprintf(palabra2,"Opcion:%c",fill_room);
            Lcd_Out2(2,1,palabra2);
        }
        switch(fill_room){
            case 'A':{
                valor=0;
                Lcd_Cmd(LCD_CLEAR);
                __delay_ms(100);
                Lcd_Out(1,1,"Permitame ir");
                Lcd_Out(2,1,"con el ADMIN");
                __delay_ms(1500);
                Lcd_Cmd(LCD_CLEAR);
                __delay_ms(100);
                Lcd_Out(1,1,"Checaremos las");
                Lcd_Out(2,1,"habitaciones");
                __delay_ms(1500);
                Lcd_Cmd(LCD_CLEAR);
                __delay_ms(100);
                Lcd_Out(1,1,"***************");
                Lcd_Out(2,1,"***************");
                __delay_ms(1500);
                Lcd_Cmd(LCD_CLEAR);
                __delay_ms(100);
                clean_rooms();
                __delay_ms(1000);
                break; 
            }
            case 'B':{
                Lcd_Cmd(LCD_CLEAR);
                __delay_ms(100);
                Lcd_Out(1,1,"PASE A LA");
                Lcd_Out(2,1,"SALA DE ESPERA");
                __delay_ms(1500);
                Lcd_Cmd(LCD_CLEAR);
                __delay_ms(100);
                Lcd_Out(1,1,"***************");
                Lcd_Out(2,1,"***************");
                __delay_ms(1500);
                Lcd_Cmd(LCD_CLEAR);
                __delay_ms(100);
                count=0;
                while(count!=100){
                    LATCbits.LATC0=1;
                    __delay_ms(1);
                    LATCbits.LATC0=0;
                    __delay_ms(19);
                    count++;
                }
                __delay_ms(5000);
                ptr_valor=0;
                break;
            }
            case 'C':{
                ptr_valor='A';
                break;
            }
        }
    }
}
void __interrupt() isr(void){
    if(PIR1bits.RCIF==1){
        datos=UART_Rx(); 
    }
    PIR1bits.RCIF=0;
}
