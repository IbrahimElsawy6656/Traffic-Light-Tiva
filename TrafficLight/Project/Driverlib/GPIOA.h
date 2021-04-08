#ifndef __GPIOA_H__
#define  __GPIOA_H__


#include "stdint.h"
#include "stdbool.h"
#include "tm4c123gh6pm.h"


void enablePortAClock (void);
void setPortAPinOutput (char pin);
void setPortAPinInput (char pin); //enable pullup inside
void writePortAPin (char pin,char value);
char readPortAPin (char pin);
void enablePortANVIC (void);
void enablePortAInt (char pin); //set interrupt type inside (falling edge)
void disablePortAInt (char pin);
void setPortAPriority (char priority);
char readPortAFlag (char pin); //RIS
void clearPortAFlag (char pin); //ICR

#endif 
