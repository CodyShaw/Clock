/* 
 * File:   shiftRegDisplay.h
 * Author: Cody
 *
 * Created on February 19, 2014, 6:59 PM
 */

#ifndef SHIFTREGDISPLAY_H
#define	SHIFTREGDISPLAY_H

void pulseClock(void);
void data0(void);
void data1(void);
void shiftOut(char, char);
void displayChar(char, int, char);
void outputEnable(char);
void outputDisable(char);
void displayTime(void);

#endif	/* SHIFTREGDISPLAY_H */

