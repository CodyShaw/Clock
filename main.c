/*
 * File:   main.c
 * Author: Cody
 *
 * Created on February 2, 2014, 3:46 PM
 */


#include "config.h"
#include "rtc.h"
      

static unsigned char pinCS;


void pulseClock(void);
void data0(void);
void data1(void);
void mcuInit(void);
static unsigned char clock;
static unsigned char data;
static unsigned char prtA;

void main(void) {


    mcuInit();

    rtcInit(pinCS);

    clock = 0b00000001;
    data = 0b00000010;
    
    while(1){
        data1();
        pulseClock();
        pulseClock();
        pulseClock();
        pulseClock();
        pulseClock();
        pulseClock();
        pulseClock();
        pulseClock();
        pulseClock();
        data0();
        pulseClock();
        pulseClock();
        pulseClock();
        pulseClock();
        pulseClock();
        pulseClock();
        pulseClock();
        pulseClock();
        pulseClock();
    }

    //rtcTest();
    
    return;
}

void pulseClock(void){
    prtA = prtA | clock;
    PORTA = prtA;
    __delay_ms(50);
    prtA = prtA & ~clock;
    PORTA = prtA;
    __delay_ms(50);
}

void data0(void){
    prtA = prtA & ~data;
    PORTA = prtA;
}

void data1(void){
    prtA = prtA | data;
    PORTA = prtA;
}

void mcuInit(void){

    TRISB = 0b00000010;
    OPTION_REG = 0x00;
    TRISA = 0x00;
    OSCCON = 0b01110000;
    SSPSTAT = 0b00000000;
    SSPCON = 0b00100010;

    pinCS = 0x01;
    PORTA = 0b00000000;
    PORTB = 0x00;
    prtA = 0x00;

    return;
}
