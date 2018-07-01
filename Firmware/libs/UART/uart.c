#include "uart.h"
// ISR(USART1_RX_vect)
// {
// 	if (stick) 
// 	_STICK_STATUS=USART_Receive();
// 	else
// 	_BUTTON_STATUS=USART_Receive(); // Se não ler UDR aqui ele continuará settando a flag, travando programa
// 	stick = !stick;
// }

unsigned char USART_Receive( void )
{
	/* Wait for data to be received */
	while ( !(UCSR1A & (1<<RXC1)) )
	;
	/* Get and return received data from buffer */
	Rflag=0;
	return UDR1;
}


void USART_Transmit( unsigned char data )
{
	/* Wait for empty transmit buffer */
	while ( !( UCSR1A & (1<<UDRE1)) )
	;
	/* Put data into buffer, sends the data */
	UDR1 = data;
}


int UART_putchar(char c, FILE *fp){
	USART_Transmit(c);
	return 0;
}


void initUart()
{
	
	UBRR1H = (unsigned char)(BAUDRATE>>8);                      // shift the register right by 8 bits
	UBRR1L = (unsigned char)BAUDRATE;                           // set baud rate
	UCSR1B|= (1<<TXEN1)|(1<<RXEN1);                // enable receiver and transmitter
	UCSR1C|=  (1<<USBS1)|(1<<UCSZ10);
}
