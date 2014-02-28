/*
 * File:   rtc.c
 * Author: Cody
 *
 * Created on February 12, 2014, 6:50 PM
 */
#include "config.h"
#include "rtc.h"


void rtcInit(void){
    rtcToggleCS();
    rtcAddr(0x8F);
    rtcData(0x00);
    rtcToggleCS();
    rtcToggleCS();
    rtcAddr(0x8F);
    rtcData(0x00);
    rtcToggleCS();

    rtcToggleCS();
    rtcAddr(0x80);
    rtcData(0x00);
    rtcData(0x59);
    rtcData(0x09);
    rtcToggleCS();

    rtcGetTime();
    return;
}

void rtcTest(void){

    rtcToggleCS();
    rtcAddr(0x80);
    rtcData(0x00);
    rtcData(0x59);
    rtcData(0x20);
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

    PORTB = PORTB ^ RTC_CS;

    __delay_us(4);

    return;
}

char rtcGetSeconds(void){
    rtcToggleCS();
    rtcAddr(0x00);
    char output = rtcData(0x00);
    rtcToggleCS();

    return output;
}

char rtcGetMinutes(void){
    rtcToggleCS();
    rtcAddr(0x01);
    char output = rtcData(0x00);
    rtcToggleCS();

    return output;
}

char rtcGetHours(void){
    rtcToggleCS();
    rtcAddr(0x02);
    char output = rtcData(0x00);
    rtcToggleCS();

    return output;
}

void rtcGetTime(void){
    rtcToggleCS();
    rtcAddr(0x00);
    char holdSec = rtcData(0x00);
    if(GLOBALTIME.secs != holdSec){
        TICK = TICK ^ 0xFF;
        GLOBALTIME.secs = holdSec;
        GLOBALTIME.mins = rtcData(0x00);
        GLOBALTIME.hours = rtcData(0x00);
    }
    rtcToggleCS();
}

void rtcSetTime(void){
    rtcToggleCS();
    rtcAddr(0x80);
    rtcData(GLOBALTIME.secs);
    rtcData(GLOBALTIME.mins);
    rtcData(GLOBALTIME.hours);
    rtcToggleCS();
    return;
}

void rtcIncMins(void){

    if(GLOBALTIME.mins == 0x59){
        rtcIncHrs();
        GLOBALTIME.mins = 0x00;   
    } else {
        if((GLOBALTIME.mins & 0x0F) == 0x09){
            GLOBALTIME.mins = (GLOBALTIME.mins & 0xF0) + 0x10;
        } else {
            GLOBALTIME.mins = GLOBALTIME.mins + 1;
        }
    }

    rtcSetTime();
    return;
}

void rtcIncHrs(void){

    if(GLOBALTIME.hours == 0x23){
        GLOBALTIME.hours = 0x00;
    } else if((GLOBALTIME.hours & 0x0F) == 0x09) {
        GLOBALTIME.hours = (GLOBALTIME.hours & 0xF0) + 0x10;
    } else {
        GLOBALTIME.hours = GLOBALTIME.hours + 1;
    }

    rtcSetTime();
    return;
}