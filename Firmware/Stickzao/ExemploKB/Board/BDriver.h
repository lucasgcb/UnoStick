// Buttons driver
/* Estes são os pinos do AT16 U */
// #define BUTTONS_BUTTON1 (1 << PB7)
// #define BUTTONS_BUTTON2 (1 << PB6)  
// #define BUTTONS_BUTTON3 (1 << PB5)


/* Estes são os códigos advindos do 328p */
#ifndef LAYOUT
#define LAYOUT
#define BUTTONS_VECT PINC
#define STICK_VECT PIND
#define HP 5
#define MP 4
#define LP 3
#define HK 2
#define MK 1
#define LK 0
#define UP 2
#define DOWN 3
#define LEFT 4
#define RIGHT 5
#define START 6
#define HOME 7
//#define CUR_BUTTONS ((1<<HP) | (1<<MP) | (1<<LP) | (1<<HK) | (1<<MK) | (1<<LK))
#define NEUTRAL_BUTTONS 0x3f
#define NEUTRAL_STICK 0xfc
#endif



#define BUTTONS_ALL (BUTTONS_BUTTON1 | BUTTONS_BUTTON2 | BUTTONS_BUTTON3)

		#include <avr/io.h>
		#include <avr/wdt.h>
		#include <avr/power.h>
		#include <avr/interrupt.h>
		#include <stdbool.h>
		#include <string.h>


static inline uint8_t Buttons_GetStatus(void)

//Neutral Neutral: fc
//Neutral Botao : 3f (111 111)
//Realiza XOR com o retorno do 328p e o valor padrão
// STATUS = (111 110) XOR (111 111)
// Verifica se o botão foi pressionado ->
// STATUS & (1<<BOTAO)

{
	uint8_t STATUS = NEUTRAL_BUTTONS;
	USART_Transmit('B'); // Pedir pelos botões no PORTC
	 uint16_t i=50000;

	 //bloco de timeout no caso do UART se perder
	 do{
		 if (UCSR1A & (1<<RXC1))
			STATUS=USART_Receive();;
	 }while(--i);
	
	STATUS = STATUS ^ NEUTRAL_BUTTONS;
	return (STATUS);
}


// static inline uint8_t ButtonsKB_GetStatus(void) // usar para depurar com os pinos do 16U2
// {
// 	return ((PINB & BUTTONS_ALL) ^ BUTTONS_ALL);
// }

static inline uint8_t Stick_GetStatus(void)

{
		uint8_t STATUS = NEUTRAL_STICK;
		USART_Transmit('J'); //Pedir pela posicao do joystick + start e home no PORTD
		uint16_t i=50000;

		//bloco de timeout no caso do UART se perder
				do{
					if (UCSR1A & (1<<RXC1))
					STATUS=USART_Receive();;
				}while(--i);

		STATUS = STATUS ^ NEUTRAL_STICK;
		return (STATUS);
}

