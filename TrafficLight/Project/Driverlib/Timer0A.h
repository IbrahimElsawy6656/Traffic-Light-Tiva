#ifndef _TIMER0AH_
#define _TIMER0AH_

#include "stdint.h"
#include "stdbool.h"
#include "tm4c123gh6pm.h"

void enableTimer0AClock (void);
void enableTimer0A (void);
void disableTimer0A (void);
void configTimer0A (void);
void setTimer0ALoad (char value);
char readTimer0AFlag (void);
void clearTimer0AFlag (void);
void enableTimer0AInt(void);
void disableTimer0AInt(void);
void setTimer0APriority (char value);
void delayTimer0Sec(char sec);

#endif
