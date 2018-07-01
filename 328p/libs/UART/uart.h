#define BAUD 9600                                   // define baud
#define BAUDRATE ((F_CPU)/(BAUD*16UL)-1)            // set baud rate value for UBRR
#define BUFFERSIZE 16
#define UART_OUT uart_str
#include <stdio.h>

volatile unsigned char new='\0';
volatile uint8_t Rflag = 0;
void initUart();
int UART_putchar(char c, FILE *fp);
void USART_Transmit( unsigned char );
unsigned char USART_Receive( void );

FILE UART_OUT = FDEV_SETUP_STREAM(UART_putchar, NULL, _FDEV_SETUP_WRITE);
