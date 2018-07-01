/*
 * main.c
 *
 *  Created on: Mar 9, 2018
 *      Author: Renan Augusto Starke & Lucas Gabriel Coliado Bandeira
 */

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <avr_gpio.c>
#include <avr/interrupt.h>
#include <avr_gpio.h>
#include <bits.h>
#include "uart.h"
#include "uart.c"

#include "layout.h"
#include "layout.c"

void init();

int main(){
	
	/* Criação do FILE e mapeamento para o stdout */
	uint8_t prevButtons = 0;
	uint8_t prevStick = 0;
	init();
	while(1)
	{
		(prevButtons==0x3f && prevStick == 0xfc) ? clr_bit(PORTB,PB5):set_bit(PORTB,PB5); // Ativa sinal de feedback se algo for pressionado

		if(checkForChange(prevButtons,prevStick))
		{
			prevButtons = CUR_BUTTONS;
			prevStick = CUR_STICK_POS;
			clr_bit(PORTB,PB2);
			clr_bit(PORTB,PB5);
		}
		_delay_us(10);
	}

	return 0;
}

void init()
{

	_delay_ms(1000); // Aguarda um pouco para o 16u2 inicializar
	PORTC =  0xFF;
	PORTD =  0xFF;
	

	DDRC |= (1<<HP) | (1<<MP) | (1<<LP) | (1<<HK) | (1<<MK) | (1<<LK);
	DDRD |= (1<<RIGHT) | (1<<LEFT) | (1<<DOWN) | (1<<UP) | (1<<START) | (1<<HOME);
	
	initUart();
	sei();
}