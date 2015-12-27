#include "terminal.h"

Terminal::Terminal(vga_color_e bg=vga_color_e::COLOR_BLACK, vga_color_e fg=vga_color_e::COLOR_WHITE){
	this->position=0;
	setColor(fg, bg) ;
	for(uint32_t i=0;i<this->VGA_WIDTH*this->VGA_HEIGHT;i++){
		this->vidMem[i].color=this->color;
		this->vidMem[i].charac=' ';
	}
}

void Terminal::setColor(vga_color_e fg,vga_color_e bg) {
	this->color= fg | (bg << 4);
}
void Terminal::setPosition(uint32_t x, uint32_t y){
	this->position=(y*VGA_WIDTH)+x;
}
void Terminal::putChar(uint8_t c){
	vidMem[position].charac=c;
	vidMem[position].color=this->color;
	position++;
	if(position==this->VGA_WIDTH*this->VGA_HEIGHT){
		memmove(vidMem+);
	}
}