# UnoStick / Stickzao

## Slow Installation (no script yet)
### Notice: These steps will not-permanently disable your Arduino programming funcionalities. Read on for a walkthrough on how to restore it.
 0 - Plug the Board. Ensure the serial programmer is installed by uploading a random Sketch; if this fails you have other problems.

 1 - Use AVRDUDES to program the 328p with the BotoesUART.hex file. 

The command usually looks like this; and you may retrieve a more accurate depiction of it for your environment by activating Verbose mode on the Arduino platform while uploading a sketch:
>avrdude.exe `"-CC:\Program Files (x86)\Arduino\hardware\tools\avr/etc/avrdude.conf" -v -patmega328p -carduino -PCOM3 -b115200 -D -Uflash:w:"$(ProjectDir)Release\BotoesUART.hex":i`

 2 - Enable DFU mode on your Arduino.

![Arduino DFU](http://2.bp.blogspot.com/-3NUsmpZn3CU/UjAZu5yS9BI/AAAAAAAADfQ/Xekuk1jNh4Y/s320/ArduinoUno_R3_Front_450px.jpg)

 3 - Acquire Microchip's [FLIP](http://www.microchip.com/Developmenttools/ProductDetails/FLIP) , or dfu-programmer for erasing and programming the ATMEGA16U2

 4 - With your DFU programmer, Program the ATMEGA16U2 with Joystickzao.hex

 5 - Power Cycle the whole thing by unplugging, waiting, and replugging the USB cable.

 6 - Insert button connections in Analog A5 to A0, Digital 6 and 7

 7 - Insert stick connections in Digital 2 to 5. 

__Do not connect anything to Digital 0 or 1__, these are the UART communication ports between both controllers and any extra connections here will make controller unstable.

## Restoring Arduino
 0 - Yes, you'll have to go through a few extra steps to uninstall this. Plug the board.

 1 - Enable DFU mode on your Arduino. This should also disable the controller.

 2 - Use the DFU programmer to flash `Arduino-usbserial-uno.hex` onto the ATMEGA16U2. You may also find this file in your Arduino IDE `/hardware/arduino/avr/firmwares/atmegaxxu2/arduino-usbserial` folder. I've added it to the Firmware folder of this repository for convenience.

 3 - Power Cycle the whole thing by unplugging, waiting, and replugging the USB cable.

 4 - Make sure you've exorcised it entirely by uploading a random Sketch.

 
 
