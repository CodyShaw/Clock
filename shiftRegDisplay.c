/*
 * File:   shiftRegDisplay.c
 * Author: Cody
 *
 * Created on February 19, 2014, 6:59 PM
 *
 *       5
 *     ----
 *   |      |
 * 4 |      | 6
 *   |   1  |
 *     ----
 *   |      |
 * 3 |      | 7
 *   |      |
 *     ----         * AM/PM  8
 *       2
 */
#include "config.h"
#include "shiftRegDisplay.h"

void outputEnable(char pin){
    PORTA = PORTA | pin;
    return;
}

void outputDisable(char pin){
    PORTA = PORTA & ~pin;
    return;
}

void pulseClock(){
    PORTA = PORTA | SRD_CLOCK;
    //__delay_us(100);
    PORTA = PORTA & ~SRD_CLOCK;
    //__delay_us(100);
    return;
}

void data0(){
    PORTA = PORTA & ~SRD_DATA;
    return;
}

void data1(){
    PORTA = PORTA | SRD_DATA;
    return;
}

void displayChar(char num, int pm, char pin){
    char a = TICK;
    char t = a & 0b10000000;
    switch(num)
    {
        case 1 :
            shiftOut(0b01100000 + t, pin);
            break;
        case 2 :
            shiftOut(0b00110111 + (TICK & 0x80), pin);
            break;
        case 3 :
            shiftOut(0b01110011 + (TICK & 0x80), pin);
            break;
        case 4 :
            shiftOut(0b01101001 + (TICK & 0x80), pin);
            break;
        case 5 :
            shiftOut(0b01011011 + (TICK & 0x80), pin);
            break;
        case 6 :
            shiftOut(0b01011111 + (TICK & 0x80), pin);
            break;
        case 7 :
            shiftOut(0b01110000 + (TICK & 0x80), pin);
            break;
        case 8 :
            shiftOut(0b01111111 + (TICK & 0x80), pin);
            break;
        case 9 :
            shiftOut(0b01111001 + (TICK & 0x80), pin);
            break;
        case 0 :
            shiftOut(0b01111110 + (TICK & 0x80), pin);
            break;
    }
    return;
}

void shiftOut(char output, char pin){
    outputDisable(pin);
    for(int i = 0; i <= 7; i++){
        int set = (output >> i) & 0x01;
        if(set == 1){
            data1();
        } else {
            data0();
        }
        pulseClock();
    }
    pulseClock();
    
    outputEnable(pin);

    __delay_us(100);
    outputDisable(pin);
    return;
}

void displayTime(void){

    displayChar((GLOBALTIME.mins & 0x0F), 1, SRD_MIN);
    displayChar((GLOBALTIME.mins & 0xF0) >> 4, 1, SRD_TMIN);
    displayChar((GLOBALTIME.hours & 0x0F), 1, SRD_HR);
    displayChar((GLOBALTIME.hours & 0xF0) >> 4, 1, SRD_THR);
    
}