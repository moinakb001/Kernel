#ifndef TERMINAL_H
#define TERMINAL_H
#include <stdint.h>
#include <stdarg.h> 
#include "string.h"
class Terminal{
	private:
		typedef struct{
			uint8_t charac;
			uint8_t color;
		}__attribute__((packed)) vgaChar_t;
		uint32_t position;
		uint8_t color;
		const uint32_t VGA_WIDTH = 80,VGA_HEIGHT = 25;
		const vgaChar_t * vidMem=(vgaChar_t *)0xb8000;
	public:
		typedef enum  {
			COLOR_BLACK = 0,
			COLOR_BLUE = 1,
			COLOR_GREEN = 2,
			COLOR_CYAN = 3,
			COLOR_RED = 4,
			COLOR_MAGENTA = 5,
			COLOR_BROWN = 6,
			COLOR_LIGHT_GREY = 7,
			COLOR_DARK_GREY = 8,
			COLOR_LIGHT_BLUE = 9,
			COLOR_LIGHT_GREEN = 10,
			COLOR_LIGHT_CYAN = 11,
			COLOR_LIGHT_RED = 12,
			COLOR_LIGHT_MAGENTA = 13,
			COLOR_LIGHT_BROWN = 14,
			COLOR_WHITE = 15,
		} vga_color_e;
		Terminal(vga_color_e bg=vga_color_e::COLOR_BLACK, vga_color_e fg=vga_color_e::COLOR_WHITE);
		void setColor(vga_color_e fg, vga_color_e bg) ;
		void setPosition(uint32_t x, uint32_t y);
		void putc(char c);
		void puts(char * str);
		void printf(char * format,...);
		void scroll();
		
	
	
}
#endif