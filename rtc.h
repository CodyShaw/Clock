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
void rtcInit(void);
void rtcTest(void);
char rtcGetSeconds(void);
char rtcGetMinutes(void);
char rtcGetHours(void);
void rtcGetTime(void);
void rtcIncMins(void);
void rtcIncHrs(void);
void rtcSetTime(void);


#endif	/* RTC_H */

