#ifndef __SYSTICK__H__
#define __SYSTICK__H__

#include "stdio.h"
#include "stdint.h"
#include "tm4c123gh6pm.h"

void disableSystick (void);
void enableSystick (void);
void setSysTickLoad (char value);
char readSystickFlag(void);
void enableSystickInt (void);
void disableSystickInt (void);
void setSystickPriority (char value);
#endif
