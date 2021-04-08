#include "Systick.h"

void disableSystick (void)
{
    NVIC_ST_CTRL_R &= ~(0x1); 
}
void enableSystick (void)
{
    NVIC_ST_CTRL_R |= 0x5;
}

void setSysTickLoad (char value)
{
   
 NVIC_ST_RELOAD_R = (value / 0.0000000625) - 1;
  
}

char readSystickFlag(void)
{
 
 return (NVIC_ST_CTRL_R & (1<<16));
  
}

void enableSystickInt (void)
{
 NVIC_ST_CTRL_R |= 0x02;
}

void disableSystickInt (void)
{
 NVIC_ST_CTRL_R &= ~(0x02);
}

void setSystickPriority (char value)
{
  NVIC_SYS_PRI3_R = (NVIC_SYS_PRI3_R & 0x1FFFFFFF) | value << 29; //bits 29-31
}

