/*
    Title:  Program to change colour from red to green to blue and back to red
		          
    Author: YOUR NAME HERE
    Date:   Today's Date HERE
    Description:  The colour of the LEDS and LCD will continually change from
                   red to green to blue and back to red every 2 seconds using
                   a periodic interrupt called update. Message will appear on
                   the LCD and 4 digit displays indicating the colours.									 
*/

// INCLUDE SECTION
#include "mbed.h"                           // include the mbed library
#include "Grove_LCD_RGB_Backlight.h"        // include LCD library
#include "DigitDisplay.h"                   // 4 digit display library

//  HARDWARE INTERFACE SECTION
Grove_LCD_RGB_Backlight LCD(D14, D15);      // pins for LCD connection(D14,D15)
DigitDisplay segment(D2,D3);                // 4 digit display connected to D16
Serial blue(D1,D0);                         // blue is of class serial (D1,D0) 
                                            // associated with UART
DigitalOut r_led(LED_RED);                  // associate r_led to RED LED pin
DigitalOut g_led(LED_GREEN);                // associate g_led to GREEN LED pin
DigitalOut b_led(LED_BLUE);                 // associate b_led to BLUE LED pin

DigitalIn Left_pb(SW3);                     // associate Left_pb with LEFT PB Pin
DigitalIn Right_pb(SW2);                    // associate Right_pb with RIGHT PB Pin
Ticker change;                              // associate change with TICKER class

volatile unsigned short i =0;               // Global variable i set to 0

void update(void)                           // TIMER INTERRUPT update
{
	i++;                                      // add 1 to global variable i
}

int main()
{
	change.attach(&update,2);                 // make update a timer interrupt every 2 seconds
	LCD.setRGB(0,0,0);                        // turn off colours on LCD
	r_led=g_led=b_led=1;								      // shut off all leds
	
	for(;;)                                   // set up endless loop
	{
		if(i==0)                                // if i is 0 then turn on red led 
		{                                       
			r_led=0;
			g_led=1;
			b_led=1;
			LCD.setRGB(0xff,0,0);                // make LCD RED and print rEd on 4 digit 
			LCD.locate(0,0);
			LCD.print("      rEd       ");       
			segment.writeRaw(0,0x50);            // pattern for   r
      segment.writeRaw(1,0x79);                  // pattern for   E
			segment.writeRaw(2,0x5e);            // pattern for   d
			segment.writeRaw(3,0x00);            // blank pattern
		}
		else
			if(i==1)                             // if i is 1 then turn on green led
			{
				r_led=1;
				g_led=0;
				b_led=1;
				LCD.setRGB(0,0xff,0);              // make LCD green and print GREn on 4 digit
			LCD.locate(0,0);
			LCD.print("     GrEEn      ");
			segment.writeRaw(0,0x7D);            // pattern for   6
      segment.writeRaw(1,0x50);                  // pattern for   r
			segment.writeRaw(2,0x79);            // pattern for   E
			segment.writeRaw(3,0x54);            // pattern for   n
			}
			else
				if(i==2)                           // if i is 2 then turn on BLUE led
			{
				r_led=1;
				g_led=1;
				b_led=0;
				LCD.setRGB(0,0x80,0xff);           //�make LCD blue and print bLuE on 4 digit         
       LCD.locate(0,0);
			LCD.print("     bLuE       ");
			segment.writeRaw(0,0x7c);            // pattern for    b
      segment.writeRaw(1,0x38);                  // pattern for    L
			segment.writeRaw(2,0x1c);            // pattern for    u
			segment.writeRaw(3,0x79);            // pattern for    E
			}
			else
			{
				i=0;                               // else set i to 0 to begin again
			}
	}
  
}
