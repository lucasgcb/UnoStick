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
uint8_t checkForChange(uint8_t buttons, uint8_t stick);
#endif
