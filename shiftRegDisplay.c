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
}

void outputDisable(char pin){
    PORTA = PORTA & ~pin;
}

void pulseClock(){
    PORTA = PORTA | SRD_CLOCK;
    //__delay_us(100);
    PORTA = PORTA & ~SRD_CLOCK;
    //__delay_us(100);
}

void data0(){
    PORTA = PORTA & ~SRD_DATA;
}

void data1(){
    PORTA = PORTA | SRD_DATA;
}

void displayChar(char num, int pm, char pin){
    int addPM;
    if(pm == 1){
        addPM = 0x80;
    } else {
        addPM = 0x00;
    }

    switch(num)
    {
        case 1 :
            shiftOut(0b01100000 + addPM, pin);
            break;
        case 2 :
            shiftOut(0b00110111 + addPM, pin);
            break;
        case 3 :
            shiftOut(0b01110011 + addPM, pin);
            break;
        case 4 :
            shiftOut(0b01101001 + addPM, pin);
            break;
        case 5 :
            shiftOut(0b01011011 + addPM, pin);
            break;
        case 6 :
            shiftOut(0b01011111 + addPM, pin);
            break;
        case 7 :
            shiftOut(0b01110000 + addPM, pin);
            break;
        case 8 :
            shiftOut(0b01111111 + addPM, pin);
            break;
        case 9 :
            shiftOut(0b01111001 + addPM, pin);
            break;
        case 0 :
            shiftOut(0b01111110 + addPM, pin);
            break;
    }
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
}