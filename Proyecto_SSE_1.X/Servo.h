void Servo_init(void);
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

