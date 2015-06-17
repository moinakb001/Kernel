#pragma once
#include <stdint.h>
#include "init.h"
static inline void outb(unsigned short port, unsigned char data)
{
	__asm  mov al, data;
	__asm  mov dx, port;
	__asm  out dx, al;
}
static inline void outw(unsigned short port, unsigned short data)
{
	__asm  mov ax, data;
	__asm  mov dx, port;
	__asm  out dx, ax;
}
static inline uint8_t inb(uint16_t port)
{
	uint8_t retu;
	__asm{
		mov dx, port
			in al, dx
			mov retu, al
	}

	return retu;
}
static inline uint16_t inw(uint16_t port)
{
	uint16_t retu;
	__asm{
		mov dx, port
			in ax, dx
			mov retu, ax
	}
	return retu;
}
_declspec(naked) static  void lgdt(void * gdtaddr, uint16_t size){
	
	__asm{
	
		setGdt :
		MOV   EAX, [esp + 4]
			MOV[gdtr + 2], EAX
			MOV   AX, [ESP + 8]
			mov edx,gdtr
			MOV [edx], AX
			LGDT[gdtr]
			RET
		gdtr :
		__asm _emit 0
		__asm _emit 0
		dd(0)
	}
}

static void refreshGDT(uint16_t code,uint16_t data){

	__asm{
		mov eax,reload_CS
		sub eax,2
		mov bx,code
		mov [eax],bx
		sub eax,4
		mov ebx,reload_CS
		mov [eax],ebx
		__asm _emit 0xEA & 0xFF
		dd(0x00000000)
		__asm _emit 0x08 & 0xFF
		__asm _emit 0x00 & 0xFF

	reload_CS:

		MOV   AX, data
		MOV   DS, AX
		MOV   ES, AX
		MOV   FS, AX
		MOV   GS, AX
		MOV   SS, AX
	}
}
