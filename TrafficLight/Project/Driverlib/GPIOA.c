#include "GPIOA.h"


void enablePortAClock (void)
{ 
  SYSCTL_RCGCGPIO_R |= 0x01;
  while((SYSCTL_PRGPIO_R & 0x01) == 0);
  GPIO_PORTA_LOCK_R = 0x4C4F434B;    //unlock
  GPIO_PORTA_CR_R = 0xFF;           //enable changes
}
void setPortAPinOutput (char pin)
{
  GPIO_PORTA_DIR_R |= (1<<pin);
  GPIO_PORTA_DEN_R |= (1<<pin);
 
}
void setPortAPinInput (char pin)
{
  GPIO_PORTA_DIR_R &= ~(1<<pin);
  GPIO_PORTA_PUR_R |= (1<<pin);  //pullup enable
  GPIO_PORTA_DEN_R |= (1<<pin);
 
}
void writePortAPin (char pin,char value)
{
  if( value == 0x01 ) 
  {
  //__asm("CPSIE I");
   GPIO_PORTA_DATA_R |= (1<<pin);
  //__asm("CPSID I");
  }
  else if( value == 0x00 ) 
  {
  //__asm("CPSIE I");
   GPIO_PORTA_DATA_R &= ~(1<<pin);
  //__asm("CPSID I");
  }
}
char readPortAPin (char pin)
{
  return ((GPIO_PORTA_DATA_R & (1<<pin)) >>pin );
}
void enablePortANVIC (void)
{
  NVIC_EN0_R |= 0x01;
}
void enablePortAInt (char pin)
{
  GPIO_PORTA_IM_R |= (1<<pin);
  GPIO_PORTA_IEV_R &= ~ (1<<pin);  //falling edge
}
void disablePortAInt (char pin)
{
   GPIO_PORTA_IM_R &= ~(1<<pin);
}
void setPortAPriority (char priority)
{
  NVIC_PRI0_R = ( ( NVIC_PRI0_R & 0xFFFFFF1F) | (priority <<5) ); //portA is in bits 5-7
}
char readPortAFlag (char pin)
{
  return ((GPIO_PORTA_RIS_R & (1<<pin))>>pin);
}

void clearPortAFlag (char pin)
{
  GPIO_PORTA_ICR_R |= (1<< pin);
}
