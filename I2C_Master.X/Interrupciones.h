void interrup_Init(void);
void interrup_Init(void){
    INTCONbits.GIE=1;
    RCONbits.IPEN=1;
    INTCONbits.GIEH=1;
    INTCONbits.GIEL=1;
}