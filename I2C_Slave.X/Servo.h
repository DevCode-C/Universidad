void Servo_init(void);
void Interrupt_Prior(int i);
void Servo_init(void){
    INTCONbits.GIE=0;
    INTCONbits.PEIE = 1;
    INTCONbits.TMR0IE=1;
    INTCONbits.TMR0IF=0;
    T0CONbits.T0CS=0;
    T0CONbits.T0PS=0b111;
    T0CONbits.PSA=0;
    TMR0=21;
    INTCONbits.GIE=1;
}
void Interrupt_Prior(int i){
    RCONbits.IPEN=1;
    INTCONbits.GIEH=1;
    INTCONbits.GIEL=1;
    if(i==1){
        INTCON2bits.INTEDG2=0;
        INTCON3bits.INT2IP=0;
        INTCON3bits.INT2IE=1;
        INTCON3bits.INT2IF=0;
    }
}
