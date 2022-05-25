#ifndef UART_H_
#define UART_H_

void UART_Init(void);
char UART_InChar(void);
void UART_OutChar(char data);
void UART_OutString(char *str);

#endif //UART_H_
