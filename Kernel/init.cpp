// init.cpp : définit le point d'entrée pour l'application console.
//

#include "init.h"
#include <stddef.h>
#include "kmem.h"
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
			dd(HEADER_ADRESS + 0x20); entry_addr: equ kernel entry
			; 0x20 is the size of multiboot heeader

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
int i = 0;
void printf(char * arr){
	unsigned short *vidmem = (unsigned short *)0xB8000;
	int y = 0;
	for ( i = i; arr[y] != 0; i++,y++){
		if (arr[y] != '\n'){
			vidmem[i] = (unsigned char)arr[y] | 0xA000;
			i = i + 0;
		}
		else{
			//hi
			i = (i + 80)/80*80;
			i--;
		}
		//hg
	}
}
char * itoa(int a, char * arr){
	char * index = "0123456789";

	int as = 10;
	arr[10] = 0;
	do{
		//printf("hr");
		as--;
		arr[as] = index[a - (a / 10 * 10)];
		a = a / 10 ;

	} while (a != 0);
	//printf("he");
	return &(arr[as]);
}

void trace(unsigned int MaxFrames)
{
	// Stack contains:
	//  Second function argument
	//  First function argument (MaxFrames)
	//  Return address in calling function
	//  ebp of calling function (pointed to by current ebp)
	unsigned int * ebp = &MaxFrames - 2;
	int num = 0;
	printf("stack trace\n");
	for (unsigned int frame = 0; frame < MaxFrames; ++frame)
	{
		unsigned int eip = ebp[1];
		if (eip == 0)
			// No caller on stack
			break;
		// Unwind to previous stack frame
		ebp = reinterpret_cast<unsigned int *>(ebp[0]);
		unsigned int * arguments = &ebp[2];
		char ar[11];
		printf(itoa(eip, ar));
		printf("\n");
	}
}

 void main(unsigned long magic, unsigned long addr)
{
	char *string = "Hello World from GRUB and PE kernel !", *ch;
	unsigned short *vidmem = (unsigned short *)0xB8000;
	int i;
	Kernel::initMem();
	//float a = 1.1;
	if (magic == MULTIBOOT_BOOTLOADER_MAGIC){

		char *arr[10];
		char as[11];
		for (int r = 0; r < 10; r++){
			//Kernel::mem
			printf(itoa(Kernel::Num(), as));
			printf(" ");
			arr[r] = (char *)Kernel::malloc((r + 1) * 10);
			printf(itoa((r + 1) * 10, as));
			printf(" ");
			printf(itoa((int)arr[r], as));
			printf("\n");
		}
		for (int r = 9; r >=5; r--){
			Kernel::free(arr[r]);
		}for (int isa = 0; isa < 4; isa++)
		{
			Kernel::free(arr[isa]);
		}
		printf("\n");
		for (int r = 0; r < 10; r++){
			//Kernel::mem
			printf(itoa(Kernel::Num(), as));
			printf(" ");
			arr[r] = (char *)Kernel::malloc((r +1) * 10);
			printf(itoa((r+1)*10,as));
			printf(" ");
			printf(itoa((int)arr[r], as));
			printf("\n");
		}
		for (int r = 9; r >= 5; r--){
			Kernel::free(arr[r]);
		}for (int isa = 0; isa < 5; isa++)
		{
			Kernel::free(arr[isa]);
		}
		printf("\n");
		for (int r = 0; r < 10; r++){
			//Kernel::mem
			printf(itoa(Kernel::Num(), as));
			printf(" ");
			arr[r] = (char *)Kernel::malloc((r + 1) * 10);
			printf(itoa((r + 1) * 10, as));
			printf(" ");
			printf(itoa((int)arr[r], as));
			printf("\n");
		}

	}
	else
	{
		// DO SOMETHING
	}
}
