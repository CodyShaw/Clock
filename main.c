/*
 * File:   main.c
 * Author: Cody
 *
 * Created on February 2, 2014, 3:46 PM
 */


#include "config.h"
#include "rtc.h"
#include "shiftRegDisplay.h"

void mcuInit(void);

void main(void) {

    
    mcuInit();

    rtcInit();
    
    int oldSec;
    int ampm = 1;
    oldSec = rtcGetSeconds();
    struct Time theTime;

    while(1){
        theTime = rtcGetTime();
        
        if(theTime.secs != oldSec){
            oldSec = theTime.secs;
            ampm = ampm ^ 1;
        }

        displayChar((theTime.mins & 0x0F), ampm, SRD_MIN);
        displayChar((theTime.mins & 0xF0) >> 4, ampm, SRD_TMIN);
        displayChar((theTime.hours & 0x0F), ampm, SRD_HR);
        displayChar((theTime.hours & 0xF0) >> 4, ampm, SRD_THR);
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
    ADCON1 = 0x06;

    PORTA = 0b00000000;
    PORTB = 0x00;

    RTC_CS = 0x01;
    SRD_CLOCK = 0x01;
    SRD_DATA = 0x02;
    SRD_MIN = 0x40;
    SRD_TMIN = 0x80;
    SRD_HR = 0x08;
    SRD_THR = 0x04;

    return;
}
