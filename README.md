# Pixel Scroll
How the program works:
This program displays my first and last initials (B and Z). 
The letter will move in the direction that you push the joystick at a velocity that increases by 1 pixel per second in each press. The letters can be displayed in different colors and at different rotations. 
The program is also able to display the current x and y velocities.

commands:

in order to change velocity: push joystick in desired direction

in order to get a set of commands: call ./scroll with -h

in order to change color: call ./scroll with -c COLOR where COLOR is "white","red","green", or "blue"

in order to change the rotation: call ./scroll with -r DEGREES, where degrees is 0, 90, 180, or 270

in order to constantly print the velocities of x and y: call ./scroll with -p
