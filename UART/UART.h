#ifndef UART_5
#define UART_5
//UART5
void UART5_Init(unsigned long baudRate);

unsigned char UART5_ReadChar(void);

void UART5_ReadString(char *str, char stopCh);

void UART0_Init(int baudRate);
void WriteUart0(unsigned char c);
#endif
