/* 
 * File:   rtc.h
 * Author: Cody
 *
 * Created on February 12, 2014, 6:50 PM
 */

#ifndef RTC_H
#define	RTC_H

char rtcData(char);
void rtcAddr(char);
void rtcToggleCS(void);
void rtcInit(char);
void rtcTest(void);

#endif	/* RTC_H */

