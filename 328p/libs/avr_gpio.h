/*
 * avr_gpio.h
 *
 *  Created on: Mar 9, 2018
 *      Author: Renan Augusto Starke
 */

#ifndef LIB_AVR_GPIO_H_
#define LIB_AVR_GPIO_H_

#include <stdint.h>

#define _IO volatile uint8_t

typedef enum
{	GPIO_IN = 0x00,
	GPIO_OUT = 0x01,
} GPIOMode_t;

typedef struct
{
  uint8_t GPIO_Pins;            /*!< Specifies the GPIO pins to be configured. */
  GPIOMode_t GPIO_Mode;    		/*!< Specifies the operating mode for the selected pins. */
  GPIOMode_t GPIO_Pullups;		/*!< Specifies the pull ups for the selected pins. */

} GPIO_Init_t;

typedef struct
{
  _IO PIN;
  _IO DDR;
  _IO PORT;
} GPIOx_Type;

#define GPIO_B ((GPIOx_Type *) &PINB)
#define GPIO_C ((GPIOx_Type *) &PINC)
#define GPIO_D ((GPIOx_Type *) &PIND)

#define GPIO_SetBit(GPIO_x, bit) (GPIO_x->PORT |= (1<<bit))
#define GPIO_ClrBit(GPIO_x, bit) (GPIO_x->PORT &= ~(1<<bit))

void GPIO_Init(GPIOx_Type *GPIO_x,  GPIO_Init_t*  InitStruct);

#endif /* LIB_AVR_GPIO_H_ */
