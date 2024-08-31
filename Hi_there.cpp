/*
    Title:  Program to put HI THERE on PC SCREEN, LCD SCREEN and
		        HI on 4 digit display
    Author: Dave Ross, MCO455AA, 123-456-789
    Date:   Friday August 23rd 2024
    Description: You have to connect the LCD screen to any one of
		             the I2C connectors on the GROVE SHIELD.
								 You have to connect the 4 digit display to D2 on
								 the Grove Shield
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
int main()
{
	LCD.clear();									// clears the LCD display
	LCD.blink();									// will cause the LCD Cursor to blink
	LCD.locate(3,1);							// will position the cursor on Col 3 and Row 1
	LCD.setRGB(0,0x80,0x80);			// will show a green blue mix colour called TEAL
	LCD.print("Hi there");				// will print Hi there starting on col 3 and row 1
	segment.writeRaw(0,0);				// will make left 7 segment blank
	segment.writeRaw(1,0x74);			// will put   h   on 2nd from left 7 segment
	segment.writeRaw(2,0x06);			// will put   I   on 3rd from left 7 segment
	segment.writeRaw(3,0);				// will make right most 7 seg be blank
	printf("\e[1;1H");						// will position PUTTY cursor in top left corner
	printf("\e[2J");							// will clear  PUTTY screen
	printf("\e[1;33;44m\f");			// will entire screen turn blue and use bold yellow letters
	printf("\e[12;36H");					// puts putty cursor at (12,36)
  printf("Hi there");	          // prints Hi there on PUTTY screen at 9600 baud
	fflush(stdout);			          // flushes output buffer to Putty screen
	return(0);			              // returns to Op system
}
