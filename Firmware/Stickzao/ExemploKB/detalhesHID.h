
/*
             LUFA Library
     Copyright (C) Dean Camera, 2017.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2017  Dean Camera (dean [at] fourwalledcubicle [dot] com)

  Permission to use, copy, modify, distribute, and sell this
  software and its documentation for any purpose is hereby granted
  without fee, provided that the above copyright notice appear in
  all copies and that both that the copyright notice and this
  permission notice and warranty disclaimer appear in supporting
  documentation, and that the name of the author not be used in
  advertising or publicity pertaining to distribution of the
  software without specific, written prior permission.

  The author disclaims all warranties with regard to this
  software, including all implied warranties of merchantability
  and fitness.  In no event shall the author be liable for any
  special, indirect or consequential damages or any damages
  whatsoever resulting from loss of use, data or profits, whether
  in an action of contract, negligence or other tortious action,
  arising out of or in connection with the use or performance of
  this software.
*/

/** Buffer to hold the previously generated Keyboard HID report, for comparison purposes inside the HID class driver. */
static uint8_t PrevJoystickHIDReportBuffer[sizeof(USB_JoystickReport_Data_t)];

/** LUFA HID Class driver interface configuration and state information. This structure is
 *  passed to all HID Class driver functions, so that multiple instances of the same class
 *  within a device can be differentiated from one another.
 */
USB_ClassInfo_HID_Device_t Joystick_HID_Interface =
{
	.Config =
	{
		.InterfaceNumber              = INTERFACE_ID_Joystick,
		.ReportINEndpoint             =
		{
			.Address              = JOYSTICK_EPADDR,
			.Size                 = JOYSTICK_EPSIZE,
			.Banks                = 1,
		},
		.PrevReportINBuffer           = PrevJoystickHIDReportBuffer,
		.PrevReportINBufferSize       = sizeof(PrevJoystickHIDReportBuffer),
	},
};

/** HID class driver callback function for the creation of HID reports to the host.
 *
 *  \param[in]     HIDInterfaceInfo  Pointer to the HID class interface configuration structure being referenced
 *  \param[in,out] ReportID    Report ID requested by the host if non-zero, otherwise callback should set to the generated report ID
 *  \param[in]     ReportType  Type of the report to create, either HID_REPORT_ITEM_In or HID_REPORT_ITEM_Feature
 *  \param[out]    ReportData  Pointer to a buffer where the created report should be stored
 *  \param[out]    ReportSize  Number of bytes written in the report (or zero if no report is to be sent)
 *
 *  \return Boolean \c true to force the sending of the report, \c false to let the library determine if it needs to be sent
 */

bool CALLBACK_HID_Device_CreateHIDReport(USB_ClassInfo_HID_Device_t* const HIDInterfaceInfo,
                                         uint8_t* const ReportID,
                                         const uint8_t ReportType,
                                         void* ReportData,
                                         uint16_t* const ReportSize)
{
		USB_JoystickReport_Data_t* JoystickReport = (USB_JoystickReport_Data_t*)ReportData;
	//uint8_t ButtonStatus_LCL = ButtonsKB_GetStatus();
	uint8_t  _BUTTON_STATUS = Buttons_GetStatus();
	uint8_t  _STICK_STATUS = Stick_GetStatus();


	
	
	if (_STICK_STATUS & (1<<UP))
		JoystickReport->Y =  100;

	if (_STICK_STATUS & (1<<DOWN))
		JoystickReport->Y =  -100;

	if (_STICK_STATUS & (1<<LEFT))
		JoystickReport->X =  -100;

	if (_STICK_STATUS & (1<<RIGHT))
		JoystickReport->X =  100;

	if (_STICK_STATUS & (1<<START))
		JoystickReport->Button |= (1 << START);

	if (_STICK_STATUS & (1<<HOME))
		JoystickReport->Button |= (1 << HOME);

	if (_BUTTON_STATUS & (1<<LP))
	JoystickReport->Button |= (1 << LP);

	if (_BUTTON_STATUS & (1<<MP))
	JoystickReport->Button |= (1 << MP);

	if (_BUTTON_STATUS & (1<<HP))
	JoystickReport->Button |= (1 << HP);
	
  	if (_BUTTON_STATUS & (1<<LK))
  		JoystickReport->Button |= (1 << LK);

	if (_BUTTON_STATUS & (1<<MK))
		JoystickReport->Button |= (1 << MK);

	if (_BUTTON_STATUS & (1<<HK))
		JoystickReport->Button |= (1 << HK);

	/*if (ButtonStatus_LCL & BUTTONS_BUTTON2)
	  KeyboardReport->KeyCode[UsedKeyCodes++] = HID_KEYBOARD_SC_C;*/


	*ReportSize = sizeof(USB_JoystickReport_Data_t);
	return false;
}
/** HID class driver callback function for the processing of HID reports from the host.
 *
 *  \param[in] HIDInterfaceInfo  Pointer to the HID class interface configuration structure being referenced
 *  \param[in] ReportID    Report ID of the received report from the host
 *  \param[in] ReportType  The type of report that the host has sent, either HID_REPORT_ITEM_Out or HID_REPORT_ITEM_Feature
 *  \param[in] ReportData  Pointer to a buffer where the received report has been stored
 *  \param[in] ReportSize  Size in bytes of the received HID report
 */
void CALLBACK_HID_Device_ProcessHIDReport(USB_ClassInfo_HID_Device_t* const HIDInterfaceInfo,
                                          const uint8_t ReportID,
                                          const uint8_t ReportType,
                                          const void* ReportData,
                                          const uint16_t ReportSize)
{
	uint8_t  LEDMask   = LEDS_NO_LEDS;
	uint8_t* LEDReport = (uint8_t*)ReportData;

	if (*LEDReport & HID_KEYBOARD_LED_NUMLOCK)
	  LEDMask |= LEDS_LED1;

	if (*LEDReport & HID_KEYBOARD_LED_CAPSLOCK)
	  LEDMask |= LEDS_LED3;

	if (*LEDReport & HID_KEYBOARD_LED_SCROLLLOCK)
	  LEDMask |= LEDS_LED4;

	LEDs_SetAllLEDs(LEDMask);
}

