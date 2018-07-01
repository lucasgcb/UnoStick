/*
 * Blinkzao.c
 *
 * Created: 27/06/2018 14:19:14
 * Author : Dave

 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "bits.h"

int main(void)
{
    /* Replace with your application code */
	DDRD = (1<<PD5) | (1<<PD4);
    while (1) 
    {
		clr_bit(PORTD,PD4);
		set_bit(PORTD,PD5);
		_delay_ms(500);
		set_bit(PORTD,PD4);
		clr_bit(PORTD,PD5);
		_delay_ms(500);
    }
}

