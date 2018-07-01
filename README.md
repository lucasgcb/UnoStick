# UnoStick / Stickzao

## Slow Installation (no script yet)
	1- Use AVRDUDES to program the 328p with the BotoesUART.hex file.
	2- Enable DFU mode on your Arduino.
	![Arduino DFU](http://2.bp.blogspot.com/-3NUsmpZn3CU/UjAZu5yS9BI/AAAAAAAADfQ/Xekuk1jNh4Y/s320/ArduinoUno_R3_Front_450px.jpg)
	3- Acquire Microchip's [FLIP](http://www.microchip.com/Developmenttools/ProductDetails/FLIP) , or dfu-programmer for erasing and programming the ATMEGA16U2
	4- Program the ATMEGA16U2 with Joystickzao.hex
	5- Power Cycle the whole thing by unplugging, waiting, and replugging the USB cable.
	6- Insert button connections in Analog A5 to A0, Digital 6 and 7
	6- Insert stick connections in Digital 2 to 5. *Do not connect anything on 0 and 1*, these are the UART ports and any connection there will make controller unstable.


 
 