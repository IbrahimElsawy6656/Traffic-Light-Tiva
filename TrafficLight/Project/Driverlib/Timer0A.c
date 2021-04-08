#include "Timer0A.h"

void enableTimer0AClock(void)
{
  SYSCTL_RCGCTIMER_R |= 0x01;
  while( (SYSCTL_RCGCTIMER_R & 0x01) == 0x00 );
}

void enableTimer0A (void)
{
  TIMER0_CTL_R |= 0x03;  //enable & stall bits
}
void disableTimer0A (void)
{
  TIMER0_CTL_R &= ~(0x03);
}

void configTimer0A (void)
{
  TIMER0_CFG_R &= ~(0x03);  //32 bits mode
  TIMER0_TAMR_R |= 0x02;  //Periodic mode
}

void setTimer0ALoad (char value) //set time in seconds 
{
  TIMER0_TAILR_R = (16000000 * value) - 1; 
}

char readTimer0AFlag (void)
{
  return (TIMER0_RIS_R & 0x01);
}

void clearTimer0AFlag (void)
{
  TIMER0_ICR_R |= 0x01;
}

void enableTimer0AInt(void)
{
  TIMER0_IMR_R |= 0x01;  //Enable Timer1A INT
  NVIC_EN0_R |= 1<<19;   //Enable NVIC INT
}

void disableTimer0AInt(void)
{
  TIMER0_IMR_R &= ~(0x01);
}

void setTimer0APriority (char value) 
{
  NVIC_PRI4_R = ( (NVIC_PRI4_R & 0x1FFFFFFF) | (value << 29) );  //bits 29 in PRI5
}

void delayTimer0Sec(char sec)
{
    setTimer0ALoad (sec);
    clearTimer0AFlag ();
    enableTimer0A ();
    while(readTimer0AFlag () == 0x00)
    {}
}


