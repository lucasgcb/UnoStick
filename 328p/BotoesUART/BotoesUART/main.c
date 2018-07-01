/*
 * main.c
 *
 *  Created on: Mar 9, 2018
 *      Author: Renan Augusto Starke
 */

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <avr_gpio.c>
#include <avr/interrupt.h>
#include <avr_gpio.h>
#include "bits.h"
#include "uart.h"
#include "uart.c"
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




#include <bits.h>
void init();
uint8_t checkForChange(uint8_t buttons, uint8_t stick);
int main(){
	
	/* Criação do FILE e mapeamento para o stdout */
	uint8_t prevButtons = 0;
	uint8_t prevStick = 0;
	_delay_ms(1000);
	init();
	while(1)
	{
		(prevButtons==0x3f && prevStick == 0xfc) ? clr_bit(PORTB,PB5):set_bit(PORTB,PB5);

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

uint8_t checkForChange(uint8_t buttons, uint8_t stick)
{
	if( (CUR_BUTTONS) != buttons)
		return 1;
	if( (CUR_STICK_POS) != stick)
		return 1;
	return 0;

}

void clearBuffer(unsigned char* buff, uint8_t length)
{
	uint8_t i = length;
	for(i=0;i<length;i++)
	{
		buff[i]='\0';
	}
}

void init()
{
	PORTC =  0xFF;
	PORTD =  0xFF;
	

	DDRC |= (1<<HP) | (1<<MP) | (1<<LP) | (1<<HK) | (1<<MK) | (1<<LK);
	DDRD |= (1<<RIGHT) | (1<<LEFT) | (1<<DOWN) | (1<<UP) | (1<<START) | (1<<HOME);
	
	initUart();
	sei();
}