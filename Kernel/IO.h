#pragma once
#include <stdint.h>
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
	uint8_t ret;
	__asm{
		mov dx, port
			in al, dx
			mov ret, al
	}
	/* TODO: Is it wrong to use 'N' for the port? It's not a 8-bit constant. */
	/* TODO: Should %1 be %w1? */
	return ret;
}
static inline uint16_t inw(uint16_t port)
{
	uint16_t ret;
	__asm{
		mov dx, port
			in ax, dx
			mov ret, ax
	}
	/* TODO: Is it wrong to use 'N' for the port? It's not a 8-bit constant. */
	/* TODO: Should %1 be %w1? */
	return ret;
}