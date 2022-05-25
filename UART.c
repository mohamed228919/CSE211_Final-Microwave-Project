#include "UART.h"
#include "tm4c123gh6pm.h"
#include <stdint.h>

void UART_Init(void) {
	SYSCTL_RCGCUART_R |= 0x0001;
	SYSCTL_RCGCGPIO_R |= 0x0001;
	UART0_CTL_R &= ~0x0001;
	UART0_IBRD_R = 0x68;
	UART0_FBRD_R = 0xB;
	UART0_LCRH_R = 0x0070;
	UART0_CTL_R  = 0x0301;
	GPIO_PORTA_AFSEL_R |= 0x03;
	GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R&0xFFFFFF00) + 0x00000011;
	// configure UART fot PA0 and PA1
	GPIO_PORTA_DEN_R |= 0x03;
	GPIO_PORTA_AMSEL_R &= ~0x03;
}

char UART_InChar(void) {
	while ((UART0_FR_R & 0x10) != 0);
	return (char)(UART0_DR_R & 0xFF);
}

void UART_OutChar(char data) {
	while((UART0_FR_R & 0x0020) != 0);
	UART0_DR_R = data;
}

void UART_OutString(char *str) {
	while (*str) {
		UART_OutChar(*str);
		str++;
	}
}
