//--------------------------------------------------------------------------------------------- //
//		AVR e Arduino: Técnicas de Projeto, 2a ed. - 2012.										//	
//--------------------------------------------------------------------------------------------- //
//=============================================================================================	//
//		Sub-rotinas para o trabalho com um LCD 16x2 com via de dados de 4 bits					//	
//		Controlador HD44780	- Pino R/W aterrado													//
//		A via de dados do LCD deve ser ligado aos 4 bits mais significativos ou					//
//		aos 4 bits menos significativos do PORT do uC											// 																
//=============================================================================================	//
#include "LCD.h"

#include <stdarg.h>

//sinal de habilitação para o LCD
#define PULSO_ENABLE() 	_delay_us(1); set_bit(CONTR_LCD,E); fprintf(&uart_str, "%s%d", " ", PORTD); _delay_us(1); clr_bit(CONTR_LCD,E); fprintf(&uart_str, "%s%d", " ", PORTD); _delay_us(45)

//---------------------------------------------------------------------------------------------
// Sub-rotina para enviar caracteres e comandos ao LCD com via de dados de 4 bits
//---------------------------------------------------------------------------------------------
void cmd_LCD(uint8_t c, uint8_t cd)				//c é o dado  e cd indica se é instrução ou caractere
{
	if(cd==0)
		clr_bit(CONTR_LCD,RS);
	else
		set_bit(CONTR_LCD,RS);
	fprintf(&uart_str, "%s%d", " ", PORTD);
	
	//primeiro nibble de dados - 4 MSB
	#if (NIBBLE_DADOS)								//compila código para os pinos de dados do LCD nos 4 MSB do PORT
		DADOS_LCD = (DADOS_LCD & 0x0F)|(0xF0 & c);		
	#else											//compila código para os pinos de dados do LCD nos 4 LSB do PORT
		DADOS_LCD = (DADOS_LCD & 0xF0)|(c>>4);	
	#endif
	fprintf(&uart_str, "%s%d", " ", PORTD);
	
	_delay_ms(10);
	PULSO_ENABLE();

	//segundo nibble de dados - 4 LSB
	#if (NIBBLE_DADOS)								//compila código para os pinos de dados do LCD nos 4 MSB do PORT
		DADOS_LCD = (DADOS_LCD & 0x0F) | (0xF0 & (c<<4));		
	#else											//compila código para os pinos de dados do LCD nos 4 LSB do PORT
		DADOS_LCD = (DADOS_LCD & 0xF0) | (0x0F & c);
	#endif
	
	fprintf(&uart_str, "%s%d", " ", PORTD);
	_delay_ms(10);
	PULSO_ENABLE();
	
	if((cd==0) && (c<4))				//se for instrução de retorno ou limpeza espera LCD estar pronto
		_delay_ms(2);
}
//---------------------------------------------------------------------------------------------
//Sub-rotina para inicialização do LCD com via de dados de 4 bits
//---------------------------------------------------------------------------------------------
void inic_LCD_4bits()		//sequência ditada pelo fabricando do circuito integrado HD44780
{							//o LCD será só escrito. Então, R/W é sempre zero.

	clr_bit(CONTR_LCD,RS);	//RS em zero indicando que o dado para o LCD será uma instrução	
	fprintf(&uart_str, "%s%d", " ", PORTD);
	clr_bit(CONTR_LCD,E);	//pino de habilitação em zero
	fprintf(&uart_str, "%s%d", " ", PORTD);
	
	_delay_ms(20);	 		//tempo para estabilizar a tensão do LCD, após VCC ultrapassar 4.5 V (na prática pode
							//ser maior). 
	//interface de 8 bits						
	#if (NIBBLE_DADOS)
		DADOS_LCD = (DADOS_LCD & 0x0F) | 0x30;		
	#else		
		DADOS_LCD = (DADOS_LCD & 0xF0) | 0x03;		
	#endif						
	fprintf(&uart_str, "%s%d", " ", PORTD);
								
	PULSO_ENABLE();			//habilitação respeitando os tempos de resposta do LCD
	_delay_ms(5);		
	PULSO_ENABLE();
	_delay_us(200);
	PULSO_ENABLE();	/*até aqui ainda é uma interface de 8 bits.
					Muitos programadores desprezam os comandos acima, respeitando apenas o tempo de
					estabilização da tensão (geralmente funciona). Se o LCD não for inicializado primeiro no 
					modo de 8 bits, haverá problemas se o microcontrolador for inicializado e o display já o tiver sido.*/
	
	//interface de 4 bits, deve ser enviado duas vezes (a outra está abaixo)
	#if (NIBBLE_DADOS)
		DADOS_LCD = (DADOS_LCD & 0x0F) | 0x20;		
		
	#else		
		DADOS_LCD = (DADOS_LCD & 0xF0) | 0x02;
	#endif
	
	fprintf(&uart_str, "%s%d", " ", PORTD);
	
	PULSO_ENABLE();
   	cmd_LCD(0x28,0); 		//interface de 4 bits 2 linhas (aqui se habilita as 2 linhas) 
							//são enviados os 2 nibbles (0x2 e 0x8)
	cmd_LCD(0x28,0); 	
   	cmd_LCD(0x08,0);		//desliga o display
   	cmd_LCD(0x01,0);		//limpa todo o display
	_delay_ms(10);
	
   	cmd_LCD(0x0C,0);		//mensagem aparente cursor inativo não piscando   
	   
	   fprintf(&uart_str, "\r limpando tela\r");
   	cmd_LCD(0x80,0);		//inicializa cursor na primeira posição a esquerda - 1a linha
	
	
	fprintf(&uart_str, "\r peep: %d\r", DADOS_LCD);
}

//---------------------------------------------------------------------------------------------
//Sub-rotina de escrita no LCD -  dados armazenados na RAM
//---------------------------------------------------------------------------------------------
void escreve_LCD(char *c)
{
   for (; *c!=0;c++) cmd_LCD(*c,1);
}

//---------------------------------------------------------------------------------------------
//Sub-rotina de escrita no LCD - dados armazenados na FLASH
//---------------------------------------------------------------------------------------------
void escreve_LCD_Flash(const char *c)
{
   for (;pgm_read_byte(&(*c))!=0;c++) cmd_LCD(pgm_read_byte(&(*c)),1);
}


int lcd_putchar(char c, FILE *fp){
	cmd_LCD(c,1);

	return 0;
}
