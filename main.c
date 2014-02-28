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

    while(1){
        INTCONbits.RBIE = 0;
        rtcGetTime();
        displayTime();
        INTCONbits.RBIE = 1;
    }

    return;
}

void mcuInit(void){

    TRISB = 0b01100010;
    OPTION_REG = 0x00;
    TRISA = 0x00;
    OSCCON = 0b01110000;
    SSPSTAT = 0b00000000;
    SSPCON = 0b00100010;
    ADCON1 = 0x06;
    

    PORTA = 0b00000000;
    PORTB = 0b00000000;

    RTC_CS = 0x01;
    SRD_CLOCK = 0x01;
    SRD_DATA = 0x02;
    SRD_MIN = 0x40;
    SRD_TMIN = 0x80;
    SRD_HR = 0x08;
    SRD_THR = 0x04;

    INTCON = 0b10001000;
    TICK = 0x00;


    return;
}

void interrupt isr(void){
    
    INTCONbits.RBIE = 0;
    INTCONbits.RBIF = 0;
    int i = 0;
    int j = 0;
    while(PORTBbits.RB5 == 0){
        i = i + 1;
        if(i == 500){
            rtcIncMins();
        }
    }
    while(PORTBbits.RB6 == 0){
        j = j + 1;
        if(j == 500){
            rtcIncHrs();
        }
    }

    INTCONbits.RBIE = 1;

}
