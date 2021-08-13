#include "framebuffer.h"
#include "serial.h"
#include "memory_segments.h"

int kmain()
{
	segments_install_gdt();
	
	char msg[] = "Welcome to myFirstOS";
	unsigned int len = sizeof(msg) / sizeof(msg[0]);
	
	//frame builder writing
    	fb_write(0, msg, len);
    
    	//serial writing
    	serial_write(0x3F8, msg, len);
    	
	return 0;
} 
