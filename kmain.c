#include "framebuffer.h"
#include "serial.h"
#include "memory_segments.h"
#include "interrupts.h"
#include "multiboot.h"
#include "paging.h"
#include "hardware_interrupt_enabler.h"
#include "user_mode.h"


int run_program(unsigned int ebx){
	multiboot_info_t *mbinfo = (multiboot_info_t *) ebx;
	multiboot_module_t* modules = (multiboot_module_t*) mbinfo->mods_addr;
	unsigned int address_of_module = modules->mod_start;
	
	if(mbinfo->mods_count == 1){
	    	typedef void (*call_module_t)(void);
	    	/* ... */
	    	call_module_t start_program = (call_module_t) address_of_module;
	    	start_program();
	    	/* we'll never get here, unless the module code returns */    
	    		
	}else{
	    	char msg[]="Error: multiple modules loaded";
	    	fb_write(0,msg, sizeof(msg));
	}
	
	return 0;
}

//int kmain(unsigned int ebx)
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
    	
    	init_paging();
    	
    	//test module
    	//run_program(ebx);
    	
    	disable_hardware_interrupts();

  	// Switch to User mode
   	switch_to_user_mode();
    	
	return 0;
} 
