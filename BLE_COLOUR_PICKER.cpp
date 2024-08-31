/*
    Title:  Uses Color Picker on BLE App to change the background color of LCD
    Author: Dave Ross
    Date:   Sep 6th, 2017
    Description:    This program will take the Values from the BLE color Picker
                    App and use these to change the background color of the LCD
*/

#include "mbed.h"                           // include the mbed library
#include "Grove_LCD_RGB_Backlight.h"        // include LCD library

Grove_LCD_RGB_Backlight rgbLCD(D14, D15);   // pins for LCD connection

Serial blue(D1,D0);                         // blue is of class serial 
                                            // associated with UART
int main()
{
    char buf[10];                           // char array used with sprintf              
    int red_color=0;                        // initialize red green and 
    int green_color=0;                      // blue colors to 0
    int blue_color=0;
 
    rgbLCD.locate(3,0);                     // Position and Print  RGB
    rgbLCD.print("R    G    B");
    while(1)                                // Endless Loop
    {
        if (blue.getc()=='!')               // check for  ! character
        {
            if (blue.getc()=='C')           //Color Information ?
            {  
                red_color=  blue.getc();    //get red color value
                green_color=blue.getc();    //get green color value
                blue_color=blue.getc();     // get blue color value
                                            // update LCD backlight value
                rgbLCD.setRGB(red_color, green_color, blue_color);
                rgbLCD.locate(0,1);         // Clear bottom row characters
                rgbLCD.print("                ");
                rgbLCD.locate(2,1);         // Print Red Color Value @ (2,1)
                sprintf(buf,"%d",red_color);
                rgbLCD.print(buf); 
                rgbLCD.locate(7,1);         // Print Green Color Value @ (7,1)
                sprintf(buf,"%d",(green_color));
                rgbLCD.print(buf);
                rgbLCD.locate(12,1);        // Print Blue Color Value @ (12,1)
                sprintf(buf,"%d",(blue_color));
                rgbLCD.print(buf);
            }   
      }     
    }
}
