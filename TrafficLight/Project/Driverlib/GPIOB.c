#include "GPIOB.h"

void enablePortBClock (void)
{ 
  SYSCTL_RCGCGPIO_R |= 0x02;
  while((SYSCTL_PRGPIO_R & 0x02) == 0);
  GPIO_PORTB_LOCK_R = 0x4C4F434B;    //unlock
  GPIO_PORTB_CR_R = 0xFF;           //enable changes
}
void setPortBPinOutput (char pin)
{
  GPIO_PORTB_DIR_R |= (1<<pin);
  GPIO_PORTB_DEN_R |= (1<<pin);
 
}
void setPortBPinInput (char pin)
{
  GPIO_PORTB_DIR_R &= ~(1<<pin);
  GPIO_PORTB_PUR_R |= (1<<pin);  //pullup enable
  GPIO_PORTB_DEN_R |= (1<<pin);
 
}
void writePortBPin (char pin,char value)
{
  if( value == 0x01 ) 
  {
  //__asm("CPSIE I");
   GPIO_PORTB_DATA_R |= (1<<pin);
  //__asm("CPSID I");
  }
  else if( value == 0x00 ) 
  {
  //__asm("CPSIE I");
   GPIO_PORTB_DATA_R &= ~(1<<pin);
  //__asm("CPSID I");
  }
}
char readPortBPin (char pin)
{
  return ((GPIO_PORTB_DATA_R & (1<<pin)) >> pin );
}
void enablePortBNVIC (void)
{
  NVIC_EN0_R |= 0x02;
}

void disablePortBNVIC (void)
{
  NVIC_EN0_R &= ~(0x02);
}
void enablePortBInt (char pin)
{
  GPIO_PORTB_IM_R |= (1<<pin);
  GPIO_PORTB_IEV_R &= ~(1<<pin);  //falling edge
}
void disablePortBInt (char pin)
{
   GPIO_PORTB_IM_R &= ~(1<<pin);
}
void setPortBPriority (char priority)
{
  NVIC_PRI0_R = ( ( NVIC_PRI0_R & 0xFFFF1FFF) | (priority <<13) ); //portB is in bits 13-15
}
char readPortBFlag (char pin)
{
  return ((GPIO_PORTB_RIS_R & (1<<pin))>>pin);
}

void clearPortBFlag (char pin)
{
  GPIO_PORTB_ICR_R |= (1<< pin);
}

