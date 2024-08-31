/*
    Title:  Pot Data and equivalent voltage to 3 displays
    Author: Dave Ross
    Date:   Thurs Aug 22nd, 2024
    Description:  This program will change between DATA and VOLTAGE on the 4 digit
                  display every 5 seconds.		
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


volatile short Data_Volt=0;                 // used for selecting DATA(0) or VOLTAGE(1)
volatile char get_serial;                   // used to get UART value 

/*
This code check to see if the LEFT ARROW (7) or RIGHT ARROW (8)
was pressed in the CONTROL PAD APP. Any other keypress is ignored.
If the LEFT Arrow is pressed it prints DATA on 4 digit display
If the RIGHT Arrow is pressed it prints VOLTAGE on the 4 digiti display.
Prompts are sent to the PUTTY screen
*/
void check_ser(void)                        
{
	   printf("\e[1;1H\e[0m\f");
	   printf("In Control Pad app, press\n");
	   printf("  <=   for  Data on 4 digit\n");
	   printf("  =>   for Voltage on 4 digit\n");
	
	   /*                               
	       Data coming from the BLUEFRUIT CONTROL PAD APP
	       has the format
	           ! B 7           for the LEFT ARROW
	           ! B 8           for the RIGHT ARROW
	   */
			 if(blue.getc()=='!')                 
		 {
			 if(blue.getc()=='B')
			 {
				 get_serial=blue.getc();
				 if(get_serial=='7')       // if ! B 7 then set global variable
				 {
					  Data_Volt=0;           // Data_Volt to 0
				 }
				 else
					if(get_serial=='8')      // if ! B 8  then set global variable
					{
						Data_Volt=1;           // Data_Volt to 1
					}
					else{}                   // for any other button presses on the
						                       // control pad app, nothing happens
				
					}
				}
		 
	
}

int main()
{
	short i;																	// used as a counter
	/*  Has 7 segment patterns for 0,1,2,3,4,5,6,7,8,9*/
	static char table[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6D,
		              0x7d,0x07,0x7f,0x67};
	
	
	char buff[20];
	volatile double input;
	check_ser();                                // Use Control Pad APP to use either
									                            // Data or Voltage on the 4 digit display
									                            // You will be prompted on the Putty Screen
									
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
				{	
		      if(Data_Volt==0)
					{	
		      segment.writeRaw(i,table[buff[i]-0x30]);
					}
					else
						if(Data_Volt==1)
					{
						segment.writeRaw(i,table[buff[i+7]-0x30]);
					}
					else{}
				}
		    else
		    segment.writeRaw(i,0x5c);							// if decimal point print underline for dec pt
     }

   }
	return(0);																	// can never reach this return statement
}
