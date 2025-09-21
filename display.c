#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include "sense.h"
#include <string.h>
#define WHITE 0xFFFF
#define BLACK 0x0000
#define GREEN 0x0f00
#define BLUE 0x0000FF
#define RED 0xF000

int rotate = 0;
int active_color = WHITE;
int vPrint = 0;

pi_framebuffer_t *fb = NULL;
sense_fb_bitmap_t *bm = NULL;
int letterB[][2] = {
        {4,1}, {5,1}, {6,1}, {2,2}, {4,2}, {5,2}, {6,2},
        {1,3}, {3,3}, {6,3}, {1,4}, {3,4}, {6,4}, {1,5},
        {2,5},{3,5}, {4,5}, {5,5}, {6,5}, {1,6}, {2,6},
        {3,6},{4,6}, {5,6}, {6,6}};
int Bsize = sizeof(letterB) / sizeof(letterB[0]);

int letterZ[][2]={{1,1},{2,1},{3,1},{4,1},{5,1},{6,1},
	{2,2},{3,3},{4,4},{5,5},{1,6},{2,6},{3,6},{4,6},
	{5,6},{6,6}};
int Zsize = sizeof(letterZ) / sizeof(letterZ[0]);
float x = 0.0;
float y = 0.0;

void clear_display(void);
void change_color(char color[]){
	if(strcmp(color, "white") == 0){
		active_color = WHITE;
	}else if (strcmp(color, "red") == 0){
		active_color = RED;
	} else if(strcmp(color, "green") == 0) { 
		active_color = GREEN;
	}else if (strcmp(color, "blue") == 0) {
		active_color = BLUE;
	}	
}
void change_rotate(int newR){
	rotate = newR;
}	
void change_velocity_print(void){
	vPrint = 1;
}
void open_display(void){
       fb = getFrameBuffer();
       if (fb == NULL) {
        	fprintf(stderr, "Error: Framebuffer could not be initialized.\n");
        	exit(1);
  	}

       bm = fb->bitmap;

}	


void display_letter(char letter, int xOffset, int yOffset){
	clear_display(); 
	if (bm == NULL) {
       		 fprintf(stderr, "Error: Bitmap not initialized.\n");
        	return;
    	}
	float dt= 0.1; 
	
	if(xOffset >= 10){
		xOffset = 10;
		x = (x + dt*xOffset );
		
	} else if(xOffset <= -10){
		xOffset = -10;
		x = (x + dt*xOffset );
		
	}else{
		x = (x + dt*xOffset );
		
	}

	if(yOffset  >= 10){
		yOffset = 10;
		y = (y + dt*yOffset );
		
	} else if(yOffset  <= -10){
		yOffset = -10;
		y = (y + dt*yOffset );
		
	} else { 
		y = (y + dt*yOffset );
		
	}
	if(vPrint){	
		printf("x velocity: %d\ny velocity: %d\n",-xOffset,-yOffset);
	}
	switch(rotate){
		case 0:


			if(letter == 'b'){ 
                		for (int i = 0; i < Bsize; i++) {
         	   		 int tx = (letterB[i][1] + ((int)x)%8 + 8)%8;
        	   		 int ty = ( letterB[i][0] + ((int)y)%8+8)%8;
		   		 bm->pixel[tx][ty] = active_color;
				} 
         		} else if (letter == 'z'){
				 for (int i = 0; i < Zsize; i++) {
         	  		  int tx = (letterZ[i][0] + ((int)x)%8 + 8)%8;
        			  int ty = (letterZ[i][1] + ((int)y)%8+8)%8;
				  bm->pixel[tx][ty] = active_color; 
				}
	 		}
			break;
		case 90:
			if(letter == 'b'){ 
                		for (int i = 0; i < Bsize; i++) {
         	    		int tx = (7-letterB[i][1] + ((int)y)%8 + 8)%8;
        	   		 int ty = (letterB[i][0] + ((int)x)%8+8)%8;
		  		  bm->pixel[ty][tx] = active_color;
				} 
        		 } else if (letter == 'z'){
				 for (int i = 0; i < Zsize; i++) {
         			    int tx = (7-letterZ[i][0] + ((int)y)%8 + 8)%8;
        			    int ty = (letterZ[i][1] + ((int)x)%8+8)%8;
				    bm->pixel[ty][tx] = active_color; 
				}
			 }
			break;
		case 180:
			if(letter == 'b'){ 
                		for (int i = 0; i < Bsize; i++) {
         	   		 int tx = (7-letterB[i][1] + ((int)x)%8 + 8)%8;
        	   		 int ty = (7- letterB[i][0] + ((int)y)%8+8)%8;
		   		 bm->pixel[tx][ty] = active_color;
				} 
         		} else if (letter == 'z'){
				 for (int i = 0; i < Zsize; i++) {
         	 		   int tx = (7-letterZ[i][0] + ((int)x)%8 + 8)%8;
        			    int ty = (7- letterZ[i][1] + ((int)y)%8+8)%8;
				    bm->pixel[tx][ty] = active_color; 
				}
	 		}
			break;
		case 270: 
			if(letter == 'b'){ 
                		for (int i = 0; i < Bsize; i++) {
         	   		 int tx = (letterB[i][1] + ((int)y)%8 + 8)%8;
        	   		 int ty = (7-letterB[i][0] + ((int)x)%8+8)%8;
		   		 bm->pixel[ty][tx] = active_color;
				} 
       			} else if (letter == 'z'){
		 		for (int i = 0; i < Zsize; i++) {
         	  		  int tx = (letterZ[i][0] + ((int)y)%8 + 8)%8;
        	  		  int ty = (7-letterZ[i][1] + ((int)x)%8+8)%8;
				    bm->pixel[ty][tx] = active_color; 
				}
			 }
			break;
	}



	

}	
void clear_display(void){
	clearFrameBuffer(fb, BLACK);
 
} 

void close_display(void){
       clearFrameBuffer(fb, BLACK);
       freeFrameBuffer(fb);	
       fb = NULL;
       bm = NULL;
}



