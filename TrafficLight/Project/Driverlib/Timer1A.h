#ifndef __TIMER1A__H__
#define __TIMER1A__H__

#include "stdint.h"
#include "stdbool.h"
#include "tm4c123gh6pm.h"

void enableTimer1AClock (void);
void enableTimer1A (void);
void disableTimer1A (void);
void configTimer1A (void);
void setTimer1ALoad (char value);
char readTimer1AFlag (void);
void clearTimer1AFlag (void);
void enableTimer1AInt(void);
void disableTimer1AInt(void);
void setTimer1APriority (char value);
void delayTimer1Sec(char sec);

#endif
