global loader                
    MAGIC_NUMBER equ 0x1BADB002     
    FLAGS        equ 0x0            
    CHECKSUM     equ -MAGIC_NUMBER  
                                    
    section .text:                  
    align 4                         
        dd MAGIC_NUMBER             
        dd FLAGS                   
        dd CHECKSUM   
        
    ;declare uninitialized data
   KERNEL_STACK_SIZE equ 4096			; size of stack in bytes

    section .bss
    align 4                                     ; align at 4 bytes
    kernel_stack:                               ; label points to beginning of memory
        resb KERNEL_STACK_SIZE                  ; reserve stack for the kernel  
                      
    loader:                        
        mov eax, 0xCAFEBABE 
        mov esp, kernel_stack + KERNEL_STACK_SIZE   ; point esp to the start of the
                                                ; stack (end of memory area)
       ; The assembly code
    	extern kmain   ; the function kmain is defined elsewhere
   	call kmain       ; call the function, the result will be in eax
   	        
    .loop:
        jmp .loop                   
