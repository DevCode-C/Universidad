void ADC_Init(int Entradas);
float ADC_Channel(int Puerto);
float ADC[12];
int valor;
void ADC_Init(int entradas){
    int valor=15-entradas;
    ADCON1bits.VCFG=0;
    ADCON1bits.PCFG=valor;
    ADCON2bits.ADFM=1;
    ADCON2bits.ACQT=0b010;
    ADCON2bits.ADCS=0b101;
    switch(entradas){
        case 1:{
            TRISA=0x01;
            break;
        }
        case 2:{
            TRISA=0x03;
            break;
        }
        case 3:{
            TRISA=0x07;
            break;
        }
        case 4:{
            TRISA=0x0F;
            break;
        }
    }
    LATA=0x00;
}
float ADC_Channel(int Puerto){
    if(Puerto>12){
        return 0;
    }
    ADCON0bits.CHS=Puerto;
    ADCON0bits.ADON = 1;
    ADCON0bits.GO_DONE = 1;
    while(ADCON0bits.GO_DONE==1){
       ADC[Puerto]=ADRES;
       ADC[Puerto]=(ADC[Puerto]*5.0)/1023;
        return  ADC[Puerto];
    }
    //return  ADC[Puerto];
}