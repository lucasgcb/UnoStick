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
///#define PULSO_ENABLE() 	_delay_us(1); set_bit(CONTR_LCD,E); _delay_us(1); clr_bit(CONTR_LCD,E); _delay_us(45)
#define E_HIGH (DADOS_LCD | 0x80)
#define E_LOW  (DADOS_LCD & 0x7F)
#define PULSO_ENABLE() 	_delay_us(1);i2c_write(DADOS_LCD,E_HIGH,BUS_ADDR); _delay_us(1); i2c_write(DADOS_LCD,E_LOW,BUS_ADDR); _delay_us(45)

//---------------------------------------------------------------------------------------------
// Sub-rotina para enviar caracteres e comandos ao LCD com via de dados de 4 bits
//---------------------------------------------------------------------------------------------
void cmd_LCD(uint8_t c, uint8_t cd)				//c é o dado  e cd indica se é instrução ou caractere
{
	if(cd==0)
	{
		clr_bit(DADOS_LCD,RS);
	}
	else
	{
		set_bit(DADOS_LCD,RS);
	}

	//primeiro nibble de dados - 4 MSB				//compila código para os pinos de dados do LCD nos 4 LSB do PORT
		DADOS_LCD = (DADOS_LCD & 0xF0)|(c>>4);	
		i2c_write(DADOS_LCD,DADOS_LCD,BUS_ADDR);	
	
	PULSO_ENABLE();

	//segundo nibble de dados - 4 LSB			//compila código para os pinos de dados do LCD nos 4 LSB do PORT
		DADOS_LCD = (DADOS_LCD & 0xF0) | (0x0F & c);
		i2c_write(DADOS_LCD,DADOS_LCD,BUS_ADDR);		
	
	PULSO_ENABLE();
	
	if((cd==0) && (c<4))				//se for instrução de retorno ou limpeza espera LCD estar pronto
		_delay_ms(2);
}
//---------------------------------------------------------------------------------------------
//Sub-rotina para inicialização do LCD com via de dados de 4 bits
//---------------------------------------------------------------------------------------------
void inic_LCD_4bits()		//sequência ditada pelo fabricando do circuito integrado HD44780
{							//o LCD será só escrito. Então, R/W é sempre zero.
	i2c_write(DADOS_LCD,0,BUS_ADDR);		
	
	_delay_ms(20);	 		//tempo para estabilizar a tensão do LCD, após VCC ultrapassar 4.5 V (na prática pode
							//ser maior). 
	//interface de 8 bits
		DADOS_LCD = 0x03;		
		i2c_write(DADOS_LCD,DADOS_LCD,BUS_ADDR);			

	PULSO_ENABLE();			//habilitação respeitando os tempos de resposta do LCD
	_delay_ms(5);		
	PULSO_ENABLE();
	_delay_us(200);
	PULSO_ENABLE();	/*até aqui ainda é uma interface de 8 bits.
					Muitos programadores desprezam os comandos acima, respeitando apenas o tempo de
					estabilização da tensão (geralmente funciona). Se o LCD não for inicializado primeiro no 
					modo de 8 bits, haverá problemas se o microcontrolador for inicializado e o display já o tiver sido.*/
	
	//interface de 4 bits, deve ser enviado duas vezes (a outra está abaixo)

	DADOS_LCD = 0x02;
	i2c_write(DADOS_LCD,DADOS_LCD,BUS_ADDR);		
	
	PULSO_ENABLE();
   	cmd_LCD(0x28,0); 		//interface de 4 bits 2 linhas (aqui se habilita as 2 linhas) 
							//são enviados os 2 nibbles (0x2 e 0x8)
   	cmd_LCD(0x08,0);		//desliga o display
   	cmd_LCD(0x01,0);		//limpa todo o display
   	cmd_LCD(0x0C,0);		//mensagem aparente cursor inativo não piscando   
	   
	   fprintf(&uart_str, "\r limpando tela\r");
   	cmd_LCD(0x80,0);		//inicializa cursor na primeira posição a esquerda - 1a linha
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
