/*
    Title:  This program will take POT values from 0.000 to 1.000
		        and display centred on the PC SCREEN and LCD
    Author: Dave Ross, MCO455AA, 123-456-789
    Date:   Fri Aug 23rd, 2024
    Description:  The POT that came with your kit should be connected
                  to the GROVE SHIELD where is says A1. As you turn the
                  POT from all the way to the RIGHT (smallest value) all
                  the way to the LEFT (largest value), the DATA from the
                  POT (0.000 to 1.000)will be displayed on the left side 
									of the displays and the equivalent VOLTAGE (0-3.333)
                  will be displayed on the right side.									           									
*/

// INCLUDE SECTION
#include "mbed.h"                           // include the mbed library
#include "Grove_LCD_RGB_Backlight.h"        // include LCD library V5.0
#include "DigitDisplay.h"                   // 4 digit display library

//  HARDWARE INTERFACE SECTION
Grove_LCD_RGB_Backlight LCD(D14, D15);      // pins for LCD connection(D14,D15) 
                                            // connect LCD to any I2C on Grove Shield
DigitDisplay segment(D2,D3);                // 4 digit display connected to D2 on Grove Shield
Serial blue(D1,D0);                         // blue is of class serial (D1,D0) aka UART
                                            // connect bluefruit uart friend to Uart on Shield
AnalogIn POT(A1);														// POT connected to Grove Shield A1 connector

int main()
{
	  char buff[20];													// char array buff needed for sprintf
    volatile double input;									// input is a double precision float variable
	
    segment.clear();
		
	  printf("\e[1;1H\e[1;33;44m\f");					// make entire screen   with    letters
	  printf("\e[12;33HData    Voltage");			// puts title Data  Voltage at (12,33)
	  LCD.clear();														// clear LCD display
	  LCD.blink();														// make LCD cursor blink
	  LCD.setRGB(0x0,0xff,0x0);								// make LCD screen GREEN
	  LCD.locate(0,0);												// put LCD Cursor on Col 0 and Row 0
	  LCD.print(" Data  VOLTAGE  ");					// put Title on LCD display
    for(;;)
    {
			input=POT.read();										  // input gets float value from POT connected to A1
			printf("\e[13;33H%5.3f    %5.3f",			// print Data and Voltage on PC screen @ (13,32)
			input,input*3.333);
      sprintf(buff,"%5.3f  %5.3f",				  // sprintf converts float data to char data
			input,input*3.333);                   // and puts it into buff
			LCD.locate(1,1);											// LCD cursor to col 1 row 1
			LCD.print(buff);											// LCD.print can only output Ascii chars
		}			
}