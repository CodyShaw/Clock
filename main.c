/*
 * File:   main.c
 * Author: Cody
 *
 * Created on February 2, 2014, 3:46 PM
 */


#include "config.h"
#include "rtc.h"
      

static unsigned char pinCS;
static unsigned char prtA;



void mcuInit(void);


void main(void) {

    mcuInit();

    rtcInit(pinCS);

    rtcTest();
    
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
    PORTB = 0x00;
    prtA = 0x00;

    return;
}
