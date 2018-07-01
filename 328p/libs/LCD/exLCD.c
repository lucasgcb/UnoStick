/*
 * main.c
 *
 *  Created on: Sep 9, 2016
 *      Author: Renan Augusto Starke
 *      Instituto Federal de Santa Catarina
 */


#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <avr/io.h>

#include <ctype.h>
#include <stdint.h>
#include <stdio.h>

#include "LCD.h"

#define F_CPU 16000000UL

/*********************************************************
 * Linker options for libc:
 * If you only need to send strings with basic integer
 * numbers, use minimized version.
 * To do so use linker option:
 * -Wl,-u,vfprintf -lprintf_min

 * In other hand if you need to a floating point functionality
 * use standard option with floating point conversions:
 * -Wl,-u,vfprintf -lprintf_flt -lm
**************************************************************/


int main()
{
	uint8_t x = 0;

	DDRD = 0xFF;

	/* Criação do FILE e mapeamento para o stdout */
	FILE lcd_str = FDEV_SETUP_STREAM(lcd_putchar, NULL, _FDEV_SETUP_WRITE);
	stdout = &lcd_str;

	inic_LCD_4bits();


	while(1){
		printf("%03d", x++);
		_delay_ms(1000);

		/* Reposiciona cursor no inicio */
		cmd_LCD(0x80,0);
	}

}

