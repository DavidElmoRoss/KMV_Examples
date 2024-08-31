/*
    Title:  Pot Data and equivalent voltage to 3 displays
    Author: Dave Ross
    Date:   Thurs Aug 22nd, 2024
    Description:  This program will take pot readings from 0.00 to 0.999 as
		              Data and multiply by 3.33 to convert to voltage and then
								  send both values to PC Screen, LCD Display and 4 digit display 
                  You have to connect the LCD screen to any one of
		              the I2C connectors on the GROVE SHIELD.									
*/

// INCLUDE SECTION
#include "mbed.h"                           // include the mbed library
#include "Grove_LCD_RGB_Backlight.h"        // include LCD library
#include "DigitDisplay.h"                   // 4 digit display library

//  HARDWARE INTERFACE SECTION
Grove_LCD_RGB_Backlight LCD(D14, D15);      // pins for LCD connection(D14,D15) any I2C on Shield
DigitDisplay segment(D2,D3);                // 4 digit display connected to D2 on Grove Shield
Serial blue(D1,D0);                         // blue is of class serial (D1,D0) aka UART
                                            // connect bluefruit uart friend to Uart on Shield
AnalogIn pot(A1);														// associated POT with Analog input A1
int main()
{
	short i;																	// used as a counter
	/*  Has 7 segment patterns for 0,1,2,3,4,5,6,7,8,9*/
	static char table[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6D,
		              0x7d,0x07,0x7f,0x67};
	
	
	char buff[20];
	volatile double input;
  /* Positions cursor to top left corner, makes background screen blue
     with	green letters, then positions cursor at (12,34) and prints
     Data   Voltage*/									
	printf("\e[1;1H\e[1;32;44m\f\e[12;34HData   Voltage");
	fflush(stdout);															// flushes output buffer to screen
	LCD.clear();																// clears LCD display
	LCD.blink();																// makes LCD cursor Blink
	LCD.locate(0,0);														// puts LCD Cursor to col 0, row 0
	LCD.print(" Data   Voltage ");						  // prints Data   Voltage on LCD Scren
	segment.clear();														// clears all four 7 segment displays

	for(;;)																			// endless loop start
	{
	   input=pot.read();												// gets pot value 0.0 - 1.0000
	   sprintf(buff,"%5.3f  %5.3f",							// puts pot DATA value and equivalent 
		          input,input*3.33);							// voltage value to ASCII chars and puts in buff
	   LCD.locate(2,1);													// sets LCD Cursor to Col 2 and Row 1
	   LCD.print(buff);													// printf Data Value and equivalent Voltage value
	   printf("\e[13;34H");											// positions PC Screen cursor to (13,34)
	   printf("%5.3f  %5.3f",input,input*3.33); // prints Data Value and Equivalent voltage
																							// on PC screen
	   for(i=0;i<=3;++i)												// loop to put Voltage value on 7 seg displays
     {		
	      if(buff[i]!='.')											// if NOT decimal point then print voltage digit
		    segment.writeRaw(i,table[buff[i+7]-0x30]);
		    else
		    segment.writeRaw(i,0x08);							// if decimal point print underline for dec pt
     }		
   }
	return(0);																	// can never reach this return statement
}
