#define BAUD 9600                                   // define baud
#define BAUDRATE ((F_CPU)/(BAUD*16UL)-1)            // set baud rate value for UBRR
#define BUFFERSIZE 16
#define UART_OUT uart_str
#include <stdio.h>

#ifndef LAYOUT
#define LAYOUT
	#define BUTTONS_VECT PINC
	#define STICK_VECT PIND
	#define HP PC5
	#define MP PC4
	#define LP PC3
	#define HK PC2
	#define MK PC1
	#define LK PC0
	#define UP PD2
	#define DOWN PD3
	#define LEFT PD4
	#define RIGHT PD5
	#define START PD6
	#define HOME PD7

	
	#define CUR_BUTTONS (PINC & 0b0111111)
	#define CUR_STICK_POS (PIND & 0b11111100)
#endif 

#define CUR_BUTTONS (PINC & 0b0111111)
#define CUR_STICK_POS (PIND & 0b11111100)
volatile unsigned char new='\0';
volatile uint8_t Rflag = 0;
void initUart();
int UART_putchar(char c, FILE *fp);
void USART_Transmit( unsigned char );
unsigned char USART_Receive( void );

FILE UART_OUT = FDEV_SETUP_STREAM(UART_putchar, NULL, _FDEV_SETUP_WRITE);
