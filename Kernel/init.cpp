// init.cpp : définit le point d'entrée pour l'application console.
//
#include "Terminal.h"
#include "IO.h"
#include "init.h"
#include <stddef.h>
#include "kmem.h"
#include "CPU.h"
__declspec(naked) void multiboot_entry(void)
{
	__asm{
		align 4

		multiboot_header:
		dd(MULTIBOOT_HEADER_MAGIC); magic number
			dd(MULTIBOOT_HEADER_FLAGS); flags
			dd(CHECKSUM); checksum
			dd(HEADER_ADRESS); header address
			dd(LOADBASE); load address
			dd(00); load end address : not used
			dd(00); bss end addr : not used
			dd(HEADER_ADRESS + 0x30); entry_addr: equ kernel entry
			
			dd(0x00000000)
			dd(00)
			dd(00)
			dd(00)

		kernel_entry :
		mov     esp, KERNEL_STACK; Setup the stack

			push    0; Reset EFLAGS
			popf

			push    ebx; Push multiboot info adress
			push    eax; and magic number
			; which are loaded in registers
			; eax and ebx before jump to
			; entry adress
			; [HEADER_ADRESS + 0x20]
			call    main; kernel entry
		halt :
		jmp halt; halt processor

	}
}


 void main(unsigned long magic, unsigned long addr)
 {
	 
	
	 CPU c = CPU();
	 refreshGDT(0x08,0x10);
	 c.init();
	 
	 
	 Terminal tr = Terminal();
	 tr.putS("hello");
	 while (1 == 1);
	// return;
}
