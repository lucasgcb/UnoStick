#define BUTTONS_BUTTON1 (1 << PB7)
#define BUTTONS_BUTTON2 (1 << PB6)  
#define BUTTONS_BUTTON3 (1 << PB5)

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
#define CUR_BUTTONS 0x3f
#endif



#define BUTTONS_ALL (BUTTONS_BUTTON1 | BUTTONS_BUTTON2 | BUTTONS_BUTTON3)

		#include <avr/io.h>
		#include <avr/wdt.h>
		#include <avr/power.h>
		#include <avr/interrupt.h>
		#include <stdbool.h>
		#include <string.h>

static inline void Buttons_Init(void)
{
    // Initialize the appropriate port pins as an inputs here, with pull-ups
    // See Atmel doc 7799, section 12.2.3
    DDRB &= ~BUTTONS_ALL;
    PORTB |= BUTTONS_ALL;
}

static inline void Buttons_Disable(void)
{
    // Clear the appropriate port pins as high impedance inputs here
    DDRB &= ~BUTTONS_ALL;
    PORTB &= ~BUTTONS_ALL;
}

static inline uint8_t Buttons_GetStatus(void)

{
	uint8_t STATUS = 0x3f;
	USART_Transmit('B');
	 uint16_t i=50000;

	 //bloco de timeout
	 do{
		 if (UCSR1A & (1<<RXC1))
			STATUS=USART_Receive();;
	 }while(--i);
	
	STATUS = STATUS ^ 0x3f;
    // Return current button status here, debounced if required
    //return ((_BUTTON_STATUS) ^ 0x3f);
		// Return current button status here, debounced if required
	return (STATUS);
}


static inline uint8_t ButtonsKB_GetStatus(void)
{
	return ((PINB & BUTTONS_ALL) ^ BUTTONS_ALL);
}

static inline uint8_t Stick_GetStatus(void)

{
		uint8_t STATUS = 0xfc;
		USART_Transmit('J');
		uint16_t i=50000;

		//bloco de timeout
				do{
					if (UCSR1A & (1<<RXC1))
					STATUS=USART_Receive();;
				}while(--i);

		STATUS = STATUS ^ 0xfc;
		// Return current button status here, debounced if required
		//return ((_BUTTON_STATUS) ^ 0x3f);
		// Return current button status here, debounced if required
		return (STATUS);
}
