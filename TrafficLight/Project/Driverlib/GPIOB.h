#ifndef __GPIOB_H__
#define  __GPIOB_H__


#include "stdint.h"
#include "stdbool.h"
#include "tm4c123gh6pm.h"


void enablePortBClock (void);
void setPortBPinOutput (char pin);
void setPortBPinInput (char pin); //enable pullup inside
void writePortBPin (char pin,char value);
char readPortBPin (char pin);
void enablePortBNVIC (void);
void disablePortBNVIC(void);
void enablePortBInt (char pin); //set interrupt type inside (falling edge)
void disablePortBInt (char pin);
void setPortBPriority (char priority);
char readPortBFlag (char pin); //RIS
void clearPortBFlag (char pin); //ICR

#endif 
