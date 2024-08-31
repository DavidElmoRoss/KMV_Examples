/*
Title:      Program to display POT values on PUTTY screen and colours on leds
Author:     Dave Ross, Student ID, MCO455 Section __
Date:       Today's date
Description:    This program  will display  values from
                the GROVE POT on the PUTTY screen and will turn on
                BLUE, RED and GREEN leds for each of 3 ranges
                0.00 < 0.33, 0.33 < 0.66, and 0.66 to 1.00
								These values are multiplied by 100 to simulate
								temperature changes from 0 - 100 degrees celsius             
*/

#include "mbed.h"                     // include mbed.h library
#include "Grove_LCD_RGB_Backlight.h"  // include Grove_LCD_RGB_Backlight Library V5.0
#include "DigitDisplay.h"             // include grove 4 digit display library
void clear(void);                     // clears the PC screen
void position(int x, int y);          // positions screen cursor at (x,y)

// Hardware pin Assignments
AnalogIn pot_input(A1);               // POT connected to pin A1 on header
DigitalOut red_led(LED1);             // red_led associated with red led pin
DigitalOut green_led(LED2);           // green_led associated with green led pin
DigitalOut blue_led(LED3);            // blue_led associated with blue led pin
Grove_LCD_RGB_Backlight LCD(D14,D15); // LCD associated with I2C Grove connector
DigitDisplay segment(D2,D3);          // segment associated with 4 digit display

// main() runs in its own thread in the OS
int main()
{
    float value;                        // float value from pot simulating temp
	  char buff[20];                      // char array used by sprintf
    red_led=green_led=blue_led=1;       // shut off all leds
    clear();                            // clear the screen
    position(11,32);                    // position title 
    printf("\e[1m");
    printf("Temperature");
    position(13,33);
    printf("\e[0m");                    // shut off all colours
    printf("          ");               // clear cool normal hot messgage
	  LCD.clear();                        // clear LCD screen
	  LCD.setRGB(0,0,0);                  // make LCD Screen dark
	  LCD.locate(0,0);                    // position LCD CURSOR top left of screen
	  LCD.print("  TEMPERATURE   ");      // print Temperature on Top line of LCD
	  segment.clear();                    // clear 4 digit display
    for(;;)
    {
        value=pot_input.read();         // get FLOAT value for POT input
        value=value*100;
        position(12,34);                // ouput both values on screen
        printf("\e[0m");                // shut off all colours
        printf("\e[1;37m");             // make bold white letters
        printf("%6.2f",value);
			  sprintf(buff,"%6.2f",value);    // convert pot value to ASCII
			  LCD.locate(0,1);                // position for temp value on LCD
			  LCD.print(buff);
        if(value <33.0)
        {
            red_led=green_led=1;        // turn off red and green leds
            blue_led=0;                 // turn on Green Led
            position(13,33);
            printf("\e[1;37;44m");      // set text colour to blue
            printf("   COLD   ");
					  LCD.setRGB(0,0,0xff);       // make LCD blue
					  LCD.locate(7,1);
					  LCD.print("   COLD  ");
            segment.writeRaw(0,0x39);   // Pattern for   C
					  segment.writeRaw(1,0x3f);   // Pattern for   O
					  segment.writeRaw(2,0x38);   // Pattern for   L
					  segment.writeRaw(3,0x5e);   // Pattern for   d
        } 
        else
        if(value < 66.0)
        {
            red_led=blue_led=1;         // turn off red and blue leds
            green_led=0;                // turn on green led
            position(13,33);
            printf("\e[1;30;42m");      // set text colour to blue
            printf("  NORMAL  "); 
					  LCD.setRGB(0,0xFF,0x00);    // make LCD green
					  LCD.locate(7,1);
					  LCD.print(" NORMAL  ");
            segment.writeRaw(0,0x54);   // Pattern for   n
					  segment.writeRaw(1,0x5c);   // Pattern for   o
					  segment.writeRaw(2,0x50);   // Pattern for   r
					  segment.writeRaw(3,0x38);   // Pattern for   L					
        }
        else
        {
            green_led=blue_led=1;       // turn off green and blue
            red_led=0;
            position(13,33);
            printf("\e[1;37;41m");      // set text colour to blue
            printf("  DANGER  ");
					  LCD.setRGB(0xFF,0,00);       // make LCD RED
					  LCD.locate(7,1);
					  LCD.print("  DANGER ");	
            segment.writeRaw(0,0x5e);   // Pattern for   d
					  segment.writeRaw(1,0x77);   // Pattern for   A
					  segment.writeRaw(2,0x54);   // Pattern for   n
					  segment.writeRaw(3,0x6f);   // Pattern for   g					
        }
        wait(0.1);
    } 
}

void clear(void)
{
       printf("\e[2J");                 // \e[2J clears the screen
       fflush(stdout);
}
void position(int x, int y)
{
      printf("\e[%d;%dH",x,y);          // position cursor at (x,y)
      fflush(stdout);
}