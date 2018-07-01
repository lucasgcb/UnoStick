#define BUTTONS_BUTTON1 (1 << PB7)
#define BUTTONS_BUTTON2 (1 << PB6)  
#define BUTTONS_BUTTON3 (1 << PB5)

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
    // Return current button status here, debounced if required
    return ((PINB & BUTTONS_ALL) ^ BUTTONS_ALL);
}


