#include "Timer1A.h"

void enableTimer1AClock(void)
{
  SYSCTL_RCGCTIMER_R |= 0x02;
  while( (SYSCTL_RCGCTIMER_R & 0x02) == 0x00 );
}

void enableTimer1A (void)
{
  TIMER1_CTL_R |= 0x03;  //enable & stall bits
}
void disableTimer1A (void)
{
  TIMER1_CTL_R &= ~(0x03); 
}

void configTimer1A (void)
{
  TIMER1_CFG_R &= ~(0x03);  //32 bits mode
  TIMER1_TAMR_R |= 0x02;  //Periodic mode
}

void setTimer1ALoad (char value) //set time in seconds 
{
  TIMER1_TAILR_R = (16000000 * value) - 1; 
}

char readTimer1AFlag (void)
{
  return (TIMER1_RIS_R & 0x01);
}

void clearTimer1AFlag (void)
{
  TIMER1_ICR_R |= 0x01;
}

void enableTimer1AInt(void)
{
  TIMER1_IMR_R |= 0x01;  //Enable Timer1A INT
  NVIC_EN0_R |= 1<<21;   //Enable NVIC INT
}

void disableTimer1AInt(void)
{
  TIMER1_IMR_R &= ~(0x01);
}

void setTimer1APriority (char value) 
{
  NVIC_PRI5_R = ( (NVIC_PRI5_R & 0xFFFF1FFF) | (value << 13) );  //bits 13-15 in PRI5
}

void delayTimer1Sec(char sec)
{
    setTimer1ALoad (sec);
    clearTimer1AFlag ();
    enableTimer1A();
    while(readTimer1AFlag () == 0x00)
    {}
}


