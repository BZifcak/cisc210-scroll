#include "sense.h"
#include <stdlib.h>
#include "scroll.h"
#include <linux/input.h>
#include <stdio.h>
#include <unistd.h>

pi_joystick_t* joystick = NULL; 
void open_input(void){
   joystick = getJoystickDevice();
}


void check_input(void (*callback)(unsigned int code), int delay){
	pollJoystick(joystick, callback, delay);  
}	//checks whether the joystick has recorded any inputs (using pollJoystick from the sense library).That first parameter declaration looks really weird: it means "the parameter is named callback, and the value will be a function needing an unsigned int parameter and having no return value". Note that the argument should be the actual function, not a function call! You'll use the function handler described below under main.c.The second parameter (delay) is a time to wait in milliseconds (actually, about in "double milliseconds" on my Pi). You can use this as one way to modify the speed of the scrolling, 

void close_input(void){
    free(joystick);
    joystick == NULL;    
}	//deallocates the joystick device and set the pointer to NULL. Should do nothing if the joystick hasn't been allocated.
