/*
 * File:   main.c
 * Author: Cody
 *
 * Created on February 2, 2014, 3:46 PM
 */


#include "config.h"
#define _XTAL_FREQ 8000000        // this is used by the __delay_ms(xx) and __delay_us(xx) functions

static unsigned char pinCS;


void mcuInit(void);
char rtcData(char);
void rtcAddr(char);
void rtcToggleCS(void);
void rtcInit(void);
void rtcTest(void);

void main(void) {

    char readTest;

    mcuInit();

    rtcInit();

    rtcTest();
    
    return;
}

void rtcTest(void){

    rtcToggleCS();
    rtcAddr(0x80);
    rtcData(0x00);
    rtcData(0x00);
    rtcData(0x00);
    rtcToggleCS();

    while(1){
        rtcToggleCS();
        rtcAddr(0x00);
        readTest = rtcData(0x00);
        rtcData(0x00);
        rtcData(0x00);
        rtcToggleCS();
        readTest = 0x00;
    }

    return;
}

void mcuInit(void){

    TRISB = 0b00000010;
    OPTION_REG = 0x00;
    TRISA = 0x00;
    OSCCON = 0b01110000;
    SSPSTAT = 0b00000000;
    SSPCON = 0b00100010;

    pinCS = 0x01;
    PORTA = 0x00;

    return;
}

char rtcData(char out){

    char in;

    SSPBUF = out;
    while(SSPSTATbits.BF == 0);
    in = SSPBUF;
    return in;
}

void rtcAddr(char addr){

    SSPBUF = addr;
    while(SSPSTATbits.BF == 0);
    
    return;
}

void rtcToggleCS(void){
    char tmp;

    __delay_us(4);
    tmp = PORTA;
    tmp = tmp ^ pinCS;
    PORTA = tmp;
    __delay_us(4);
    
    return;
}

void rtcInit(){

    rtcToggleCS();
    rtcAddr(0x8F);
    rtcData(0x00);
    rtcToggleCS();
    rtcToggleCS();
    rtcAddr(0x8F);
    rtcData(0x00);
    rtcToggleCS();

    return;
}