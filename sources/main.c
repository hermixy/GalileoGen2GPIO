/* Simple App to blink the Galileo LED on IO13 (Just to the left of the USB
 * host connector).
 *
 * This code has been tested on Wind Rver Linux 6 as well as VxWorks-7.
 */

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>

#include "gpioutils.h"

/*
 * err_exit() - Called when an error is encoutered.  Cleans up and exits 
 * with a -1 status code.
 *
 */
 
static void err_exit(void)
{
    (void)gpio_dealloc(30);
    (void)gpio_dealloc(46);
    (void)gpio_dealloc(7);
    
    exit (-1);
}

/*
 * main function 
 */
 
int main(int argc, char *argv[])
{
    int i;
    
    /* 
     * Create the required GPIO pins and reserve them 
     */
    
    /* 
     * Setup GPIO30. Output and LOW 
     */
     
    if (gpio_set_direction(30, "out"))
        err_exit();
    
    if (gpio_write_pin(30, "0"))
        err_exit();
        
 
    /* 
     * Set up GPIO 46. Output and LOW 
     */
     
    if (gpio_set_direction(46, "out"))
        err_exit();
    
    if (gpio_write_pin(46, "0"))
        err_exit();
        
    
    /* 
     * Setup GPIO7. Output 
     */
     
    if (gpio_set_direction(7, "out"))
        err_exit();    
  
    /* 
     * Flash the LED 10 times with ~1 second delay in between 
     */    
    for (i=0; i < 10; i++)
        {
        if (gpio_write_pin(7, "0"))    /* Turn the LED off */
            err_exit();

        sleep(1);                      /* Wait ~1 second */
        
        if (gpio_write_pin(7, "1"))    /* Turn the LED on */
            err_exit();

        sleep(1);
        }
        

    /* 
     * Clean up 
     */
    if (gpio_write_pin(7, "0"))       /* Turn the LED off */
            err_exit();
            
    if (gpio_dealloc(30))   /* Unreserve /sys/class/gpio/gpio30 (Internal MUX) */
        err_exit();
        
    if (gpio_dealloc(46))    /* Unreserve /sys/class/gpio/gpio46 (Internal MUX) */
        err_exit();
        
    if (gpio_dealloc(7))    /* Unreserve /sys/class/gpio/gpio7  (Arduino IO13) */
        err_exit();
        
    
    return(0);
}
