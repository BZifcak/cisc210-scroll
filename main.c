#include "sense.h"
#include <stdlib.h>
#include "scroll.h"
#include <linux/input.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int running = 2;
int vx = 0, vy = 0;
void handler(unsigned int code);

void argChecker(int argc, char *argv[]);
int main(int argc, char *argv[]){	
	open_display();
	open_input();
	argChecker(argc,argv);
	while(running == 2){	
	check_input(handler,100);
	display_letter('b',vx,vy);	
	}
	while(running == 1){
	check_input(handler,100);
	display_letter('z',vx,vy);
	}
	close_input();
	close_display();
	return 0;

}

void handler(unsigned int code){
    fprintf(stderr,"code: %u\t",code);
    if(code == KEY_UP) {
        fprintf(stderr,"right");
     	vx--;;          
    
    }else if(code == KEY_DOWN) {
        fprintf(stderr,"left");
 	vx++;      
    
    }else if(code == KEY_RIGHT) {
        fprintf(stderr,"down");
	vy++;        
    
    }else if(code == KEY_LEFT) {
        fprintf(stderr,"up");
	vy--;       
    
    }else if(code == KEY_ENTER) {
        fprintf(stderr,"push");
        running--;
    }
    fprintf(stderr,"\n");

}

void argChecker(int argc, char *argv[]){

	if(argc){
		for(int i = 0; i < argc; i++){
			if (strcmp(argv[i], "-h") == 0){
				printf("in order to change velocity: push joystick in desired direction.\nin order to get a set of commands: call %s with -h\nin order to change color: call %s with -c COLOR where COLOR is \"white\" ,\"red\", \"green\", or \"blue\".\nin order to change the rotation: call %s with -r DEGREES, where degrees is 0, 90, 180, or 270\nin order to constantly print the velocities of x and y: call %s with -p\n",argv[0],argv[0],argv[0],argv[0]);
			}
			else if(strcmp(argv[i], "-c") == 0){
				if(( strcmp(argv[i+1], "white") == 0)||( strcmp(argv[i+1], "red")==0)||( strcmp(argv[i+1], "green")==0) ||( strcmp(argv[i+1], "blue")==0)){
					change_color( argv[i+1]);
				} else {
					printf("Invalid color argument\nin order to change velocity: push joystick in desired direction.\nin order to get a set of commands: call %s with -h\nin order to change color: call %s with -c COLOR where COLOR is \"white\" ,\"red\", \"green\", or \"blue\".\nin order to change the rotation: call %s with -r DEGREES, where degrees is 0, 90, 180, or 270\nin order to constantly print the velocities of x and y: call %s with -p\n",argv[0],argv[0],argv[0],argv[0]);
				}
			}
			else if(strcmp(argv[i], "-r") == 0){
				if(( strcmp(argv[i+1], "0") == 0)||( strcmp(argv[i+1], "90") == 0)||( strcmp(argv[i+1], "180") == 0)||( strcmp(argv[i+1], "270") == 0)){
					change_rotate(atoi( argv[i+1]));
				} else{
					printf("Invalid rotation argument\nin order to change velocity: push joystick in desired direction.\nin order to get a set of commands: call %s with -h\nin order to change color: call %s with -c COLOR where COLOR is \"white\" ,\"red\", \"green\", or \"blue\".\nin order to change the rotation: call %s with -r DEGREES, where degrees is 0, 90, 180, or 270\nin order to constantly print the velocities of x and y: call %s with -p\n",argv[0],argv[0],argv[0],argv[0]);

				}
			}
			else if(strcmp(argv[i], "-p") == 0){
				change_velocity_print();
			}


		}
	}

}
