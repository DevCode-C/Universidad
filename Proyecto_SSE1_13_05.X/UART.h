void UART_Init(long baud);
void UART_Tx(char data);
char UART_Rx(void);

void UART_Init(long baud){
    TRISCbits.RC6=0; //Salida de datos
    TRISCbits.RC7=1; //Entrada de datos
    SPBRG=(unsigned char)(((_XTAL_FREQ/baud)/64)-1);
    //Iniciar las confiuraciones de los registros
    TXSTAbits.BRGH=0;
    BAUDCONbits.BRG16=0;
    TXSTAbits.SYNC=0;
    RCSTAbits.SPEN=1;
    //Habilitar interrupciones
    INTCONbits.GIE=1;
    INTCONbits.PEIE=1;
    PIE1bits.RCIE=1;
    //Habilitamos La trasmisión
    TXSTAbits.TX9=0;
    TXSTAbits.TXEN=1;
    //habilitar la recepción
    RCSTAbits.RC9=0;
    RCSTAbits.CREN=1;
}
void UART_Tx(char data){
    TXREG=data;
}
char UART_Rx(){
    return RCREG;
}