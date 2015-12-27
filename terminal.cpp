#include "terminal.h"

Terminal::Terminal(vga_color_e bg=0, vga_color_e fg=15){
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
void Terminal::putc(uint8_t c){
	if(c=='\n'){
		position=(position/VGA_WIDTH);
		position++;
		position*=VGA_WIDTH;
	}else{
		vidMem[position].charac=c;
		vidMem[position].color=this->color;
		position++;
	}
	if(position==VGA_WIDTH*VGA_HEIGHT){
		scroll();
		position=VGA_WIDTH*(VGA_HEIGHT-1);
	}
}
void Terminal::puts(char * str){
	uint32_t len=strlen(str);
	for(uint32_t i=0;i<len;i++){
		putc(str[i]);
	}
}
void printf(char *fmt, ...){
	va_list vl;
	va_start(vl,fmt);
	uint32_t len=strlen(str);
	for(uint32_t i=0;i<len;i++){
		if(fmt[i]=='%'){
			i++;
			switch(fmt[i]){
				case 's':
					puts(va_arg(vl,char *));
					i++;
					break;
			}
		}else{
			putc(str[i]);
		}
	}
	va_end(vl);
}
void Terminal::scroll(){
	memmove((void *)(*vidMem[0]),(void *)(*vidMem[VGA_WIDTH]),VGA_WIDTH*(VGA_HEIGHT-1)*sizeof(vgaChar_t));
	for(uint32_t i=0;i<VGA_WIDTH;i++){
		vidmem[i+VGA_WIDTH*(VGA_HEIGHT-1)].charac=' ';
		vidmem[i+VGA_WIDTH*(VGA_HEIGHT-1)].color=color;
	}
}