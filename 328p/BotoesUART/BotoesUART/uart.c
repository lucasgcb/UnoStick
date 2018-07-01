ISR(USART_RX_vect)
{
	new = UDR0;
	if(new =='J')
	{
		USART_Transmit(CUR_STICK_POS);
	}
	if(new == 'B')
	{
		USART_Transmit(CUR_BUTTONS);
	}
		 // Se não ler UDR aqui ele continuará settando a flag, travando programa
		set_bit(PORTB,PB2);
		set_bit(PORTB,PB5);
	Rflag=1;
}

unsigned char USART_Receive( void )
{
	/* Wait for data to be received */
	while ( !(UCSR0A & (1<<RXC0)) )
	;
	/* Get and return received data from buffer */
	Rflag=0;
	return UDR0;
}


void USART_Transmit( unsigned char data )
{
	/* Wait for empty transmit buffer */
	while ( !( UCSR0A & (1<<UDRE0)) )
	;
	/* Put data into buffer, sends the data */
	UDR0 = data;
}


int UART_putchar(char c, FILE *fp){
	USART_Transmit(c);
	return 0;
}


void initUart()
{
	
	UBRR0H = (unsigned char)(BAUDRATE>>8);                      // shift the register right by 8 bits
	UBRR0L = (unsigned char)BAUDRATE;                           // set baud rate
	UCSR0B|= (1<<TXEN0)|(1<<RXEN0)|(1<<RXCIE0);                // enable receiver and transmitter
	UCSR0C|=  (1<<USBS0)|(1<<UCSZ00);

}
