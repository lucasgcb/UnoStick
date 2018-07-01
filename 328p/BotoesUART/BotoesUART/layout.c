#include "layout.h"
uint8_t checkForChange(uint8_t buttons, uint8_t stick)
{
	if( (CUR_BUTTONS) != buttons)
		return 1;
	if( (CUR_STICK_POS) != stick)
		return 1;
	return 0;
}