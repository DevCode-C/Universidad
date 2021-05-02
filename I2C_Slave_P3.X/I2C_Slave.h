void I2C_Slave_Init(short address)
{
    SSPSTAT = 0x80;
    SSPADD = address;
    SSPCON1 = 0x36;
    SSPCON2 = 0x01;
    TRISBbits.TRISB1 = 1;
    TRISBbits.TRISB0 = 1;
    GIE = 1;
    PEIE = 1;
    SSPIF = 0;
    SSPIE = 1;
    
}
