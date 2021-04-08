#include "UART0.h"


void UART0init(void)
{
    SYSCTL_RCGCUART_R |= 0x01;
    SYSCTL_RCGCGPIO_R |= 0x01;

    GPIO_PORTA_AFSEL_R = 0x03;
    GPIO_PORTA_PCTL_R =  0x11;
    GPIO_PORTA_DEN_R  = 0x03;
    GPIO_PORTA_AMSEL_R &= ~(0x03);

    UART0_CTL_R &= ~(0x01);
    UART0_IBRD_R = 104;
    UART0_FBRD_R = 11;
    UART0_LCRH_R |= 0x60;
    UART0_CTL_R |= 0x301;

}
void UART0sendChar(char Char)
{
    while( (UART0_FR_R & 0x20) != 0);
    UART0_DR_R = Char;
}


void sendState(char *string)
{

  while(*string)
  {
      UART0sendChar(*(string++));
  }
}
