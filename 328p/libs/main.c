/*
 * main.c
 *
 *  Created on: Mar 9, 2018
 *      Author: Renan Augusto Starke
 */

#include <avr/io.h>
#include <util/delay.h>

#include <bits.h>


int main(){

	/* Acesso via Função init */
	GPIO_Init_t portb;
	portb.GPIO_Pins = (1 << PB5) | (1 << PB0);
	portb.GPIO_Mode = GPIO_OUT;

	GPIO_Init(GPIO_B, &portb);
    
    
    /* Acesso por strutura */
    GPIO_C->DDR = (1 << PC0) | (1 << PB0);
    GPIO_C->PORT = 0x03;
    uint8_t x = GPIO_C->PIN;   


	for(;;){
		GPIO_SetBit(GPIO_B, PB5);
		_delay_ms(1000);
		GPIO_ClrBit(GPIO_B, PB5);
		_delay_ms(1000);
	}


	return 0;
}


