#include "framebuffer.h"

char *fb = (char *) 0x000B8000;

void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg)
{
     fb[i] = c;
     fb[i + 1] = ((fg & 0x0F) << 4) | (bg & 0x0F);
}
    
void fb_move_cursor(unsigned short pos)
{
     outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
     outb(FB_DATA_PORT,    ((pos >> 8) & 0x00FF));
     outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
     outb(FB_DATA_PORT,    pos & 0x00FF);
}

void fb_write(unsigned int pos, char *buff, unsigned int len)
{
    unsigned int currentPos;
    for(unsigned int i=0; i<(len-1); i++){
        //setting current position
    	currentPos = (pos+i)*2;
    	    	   
        //writing charactors
    	fb_write_cell(currentPos, *(buff+i), FB_GREEN, FB_DARK_GREY);
    }
    //setting the cursor
    fb_move_cursor(pos+len-1);   
}

