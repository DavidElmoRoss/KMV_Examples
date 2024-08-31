/*
    Title:  Program to display temperature on PC Screen from Grove Temp Sensor
    Author: David Ross
    Date:   July 13, 2017
    Description:    This program assumes that the Grove Temperature Module 
                    has been connected to Connector A0 of the Grove Shield V2.
                    It will constantly update the Temperature on the PC screen
                    in both Celsius and Fahrenheit, as well as show the Resistance.
*/
//Function Prototypes
void clear(void);                   // clears the PC screen
void position(int x, int y);        // positions screen cursor at (x,y)

#include "mbed.h"                   // include the mbed.h library
#include "Grove_LCD_RGB_Backlight.h"
#include "DigitDisplay.h"
AnalogIn input1(A0);                // set Analog input1 to A0 
                                    // (A1 is not connected)
Grove_LCD_RGB_Backlight LCD(D14,D15);
DigitDisplay segment(D2,D3);
// Global Variables and Constants
const int B=4250;                   // B constant for Thermistor
                                    // in Temp Sensor V1.2
volatile double temperature;        // output temperature
volatile unsigned short voltage;    // voltage  from Grove Temperature Sensor
volatile unsigned short temp;       // used for temp on 4 digit display

int main(void)
{
    volatile double R;              // variable used to compute temperature
	  char buff[20];                  // used for sprintf and LCD
    clear();                        // clear the screen
    position(11,36);                // positions curson at (11,36)
    printf("Temperature");          // print title Temperature
    fflush(stdout);                 // flush output buffer to screen
	  LCD.clear();
	  LCD.setRGB(0,0x80,0x80);        // set LCD colour to TEAL
	  LCD.locate(0,0);                // Set LCD cursor to Col 0, Row 0
	  LCD.print("Tmp_C Tmp_F Resi");
	  segment.clear();
	
 
    while(1)                        // loop forever
    {
        
      // wait_ms(500);                // wait 0.5 seconds 
        ThisThread::sleep_for(500);  
       voltage=input1.read_u16();       //  gets 16-bit raw A/D value 
                                    //voltage=32768 will give 25deg and 100.0Kohms
 
       R=65536.0/((double)voltage)-1.0; 
                                    // temperature conv based on data sheet
       temperature=1.0/(log(R)/B+1/298.15)-273.15; 

       position(12,30);    
       printf("%6.1f",temperature); // output temperature value on screen
       putchar(0xf8);               // change Putty Translation to CP437 
                                    // output Celsius and Fahrenheit temps 
       printf("C   %9.1f",((9.0/5.0)*temperature+32));
       putchar(0xf8);               // change Putty Translation to CP437  
       printf("F");
       position(14,35);             // set cursor 2 lines down
       printf("R= %6.2f Kohms",R*100);
       fflush(stdout);
			 LCD.locate(0,1);             // set LCD cursor to COL 0 ROW1
			                              // format Cel Fahr and Resistance into buff
			 sprintf(buff,"%4.1f  %4.1f  %4.1f",
			   temperature,(9.0/5.0)*temperature+32,R*100);
				 LCD.print(buff);           // Print Cel Fahr and Resistance on LCD
				                            // use temp to format Cel and Fahr Temps
																		// at 0.5 to int version of Cel and Fahr
																		// to round to the next digit
			 temp=(int)(temperature+0.5); 
			 temp=100*temp+(int)(((9.0/5.0)*temperature+32)+0.5);		                              
			 segment.setColon(1);        // turn on COLON to separate Cel and Fahr
			 segment.write(temp);        // write Cel and Fahr on 4 dig display
    }
}
void clear(void)
{
    printf("\e[2J");               // \e[2J clears putty screen
    fflush(stdout);                // flush output buffer to screen
}
void position(int x, int y)
{
    printf("\e[%d;%dH",x,y);       // \e[x;yH positions cursor at (x,y)
    fflush(stdout);                // flush output buffer to putty screen
}