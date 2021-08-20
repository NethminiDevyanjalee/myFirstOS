#include "framebuffer.h"
#include "serial.h"
#include "memory_segments.h"
#include "interrupts.h"

int kmain()
{
	segments_install_gdt();
	
	char msg[] = "Welcome to myFirstOS";
	unsigned int len = sizeof(msg) / sizeof(msg[0]);
	
	//frame builder writing
    	fb_write(0, msg, len);
    
    	//serial writing
    	serial_write(SERIAL_COM1_BASE, msg, len);
    	
    	interrupts_install_idt();
    	
	return 0;
} 
