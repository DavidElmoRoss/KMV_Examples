/*
    Title:  SKELETON CODE for LCD, 4 digit Display, and Bluefruit Uart Friend.
            Other devices like Temp Sensor, Pot and PIR Motion Detector the
	          code will work as well.
            You will  have to compile all the files once ONLY. After that ONLY
	          changes to the main() will need to be compiled.
    Author: YOUR NAME HERE, Lab Section & Student Id Number here
    Date:   Today's Date HERE
    Description:    
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
  printf("Hello World\n");	    // prints Hello World on PUTTY screen at 9600 baud
	fflush(stdout);			    			// flushes output buffer to Putty screen
	return(0);			    					// returns to Op system
}
