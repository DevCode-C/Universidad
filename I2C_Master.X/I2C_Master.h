//#include "config2.h"
//#include <pic18f4550.h>
//#define _XTAL_FREQ 12000000
void I2C_Master_Init(const unsigned long c){
    SSPCON1 = 0b00101000;
    SSPCON2 = 0;
    SSPADD = (_XTAL_FREQ/(4*c))-1;
    SSPSTAT = 0;
    TRISBbits.TRISB1 = 1;
    TRISBbits.TRISB0 = 1;
}
void I2C_Master_Wait()
{
    while ((SSPSTAT & 0x04) || (SSPCON2 & 0x1F));
}

void I2C_Master_Start()
{
    I2C_Master_Wait();
    SEN = 1;
}

void I2C_Master_RepeatedStart()
{
    I2C_Master_Wait();
    RSEN = 1;
}

void I2C_Master_Stop()
{
    I2C_Master_Wait();
    PEN = 1;
}

void I2C_Master_Write(unsigned d)
{
    I2C_Master_Wait();
    SSPBUF = d;
}

float I2C_Master_Read(unsigned short a)
{
    float temp;
    I2C_Master_Wait();
    RCEN = 1;
    I2C_Master_Wait();
    temp = SSPBUF;
    I2C_Master_Wait();
    ACKDT = (a)?0:1;
    ACKEN = 1;
    return temp;
}
