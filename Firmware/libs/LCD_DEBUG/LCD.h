#ifndef _LCD_H
#define _LCD_H

//#include "def_principais.h"

//#define F_CPU 16000000UL
//
#include <util/delay.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdio.h>
//
#include "bits.h"

//Definições para facilitar a troca dos pinos do hardware e facilitar a re-programação

#define DADOS_LCD    	PORTD  	//4 bits de dados do LCD no PORTD 
#define NIBBLE_DADOS	1		//0 para via de dados do LCD nos 4 LSBs do PORT empregado (Px0-D4, Px1-D5, Px2-D6, Px3-D7)
								//1 para via de dados do LCD nos 4 MSBs do PORT empregado (Px4-D4, Px5-D5, Px6-D6, Px7-D7) 
#define CONTR_LCD 		PORTD  	//PORT com os pinos de controle do LCD (pino R/W em 0).
#define E    			PD3     //pino de habilitação do LCD (enable)
#define RS   			PD2     //pino para informar se o dado é uma instrução ou caractere


//protótipo das funções
void cmd_LCD(uint8_t c, uint8_t cd);
void inic_LCD_4bits();		
void escreve_LCD(char *c);
void escreve_LCD_Flash(const char *c);

int lcd_putchar(char c, FILE *fp);


#endif
