/*
    Title:  Uses Control Pad to turn on RED, GREEN, BLUE, internal Leds
    Author: Dave Ross
    Date:   Sep 6th, 2017
    Description:    This program will take CONTROL PAD data from the BLUETOOTH
                    APP (1,2,3,4 and 4 arrows) and use it to control the Internal
                    LEDS. The buttons on this control pad will generate a string
                    when pressed. The string is of format  ['1']['B'] as the
                    starting two characters. After this is the button number
                    such as ['4'] for button 4. The next character will be 
                    ['1'] if the button was pressed, and ['0'] if the button
                    is released.
                    For the arrows, the up arrow is button ['5']
                                    the dn arrow is button ['6']
                                    the left arrow is button ['7']
                                    the right arrow is button ['8']
*/

#include "mbed.h"               // include the mbed library
DigitalOut red_led(LED1);       // red_led is internal red led
DigitalOut green_led(LED2);     // green_led is internal green led
DigitalOut blue_led(LED3);      // blue_led is internal blue led

Serial blue(D1,D0);             // blue is of class serial associated with UART
int main()
{
    char bnum=0;                // set button # to zero and shut off RGB leds
    red_led=1; green_led=1;blue_led=1;    
    while(1) {                  // set up infinte loop
        if (blue.getc()=='!') {
            if (blue.getc()=='B') { //button data
                bnum = blue.getc(); //button number
                if ((bnum>='1')&&(bnum<='8')) //is a number button 1..8
                {
                    switch(bnum)
                    {
                        case '1':   red_led=!red_led;       // button 1 red led
                                    break;
                        case '2':   green_led=!green_led;   // button 2 green "
                                    break;
                        case '3':   blue_led=!blue_led;     // button 3 blue  "
                                    break;
                        case '4':   red_led=!red_led;       // button 4 red &
                                    green_led=!green_led;   // green leds
                                    break;
                        case '5':   red_led=!red_led;       // uparrow red &
                                    blue_led=!blue_led;     // blue leds
                                    break;
                        case '6':   green_led=!green_led;   // downarrow green &
                                    blue_led=!blue_led;     // blue leds
                                    break;
                        case '7':   red_led=!red_led;       // left arrow is
                                    green_led=!green_led;   // red green & blue
                                    blue_led=!blue_led;
                                    break;
                        default:    red_led=!red_led;       // right arrow is
                                    blue_led=!blue_led;     // starting with 
                                    green_led=!green_led;   // white light
                                    wait(0.25);             // then subtracing
                                    blue_led=!blue_led;     // blue then
                                    wait(0.25);             // subtracing green
                                    green_led=!green_led;   // and finally red
                                    wait(0.25);
                                    red_led=!red_led;
                                    wait(0.25);
                                    break;
                    }
                }
            }
        }
    }
}
