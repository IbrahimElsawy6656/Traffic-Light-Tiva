#ifndef __UART0__H__
#define __UART0__H__

#include "stdint.h"
#include "stdbool.h"
#include "tm4c123gh6pm.h"

void UART0init(void);
void UART0sendChar(char Char);
void sendState(char *string);

#endif
