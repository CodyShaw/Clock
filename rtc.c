/*
 * File:   rtc.c
 * Author: Cody
 *
 * Created on February 12, 2014, 6:50 PM
 */

#include "config.h"
#include "rtc.h"

static unsigned char cs;

void rtcInit(char chipSel){
    cs = chipSel;
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
        rtcData(0x00);
        rtcData(0x00);
        rtcData(0x00);
        rtcToggleCS();
    }

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

    __delay_us(4);

    PORTB = PORTB ^ cs;

    __delay_us(4);

    return;
}
