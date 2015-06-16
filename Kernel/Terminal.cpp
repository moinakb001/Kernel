#include "Terminal.h"
#include "IO.h"

Terminal::Terminal()
{
	Terminal(defwidth, defheight, 0, 0, makeColor(black,red));
}

Terminal::Terminal(const uint32_t width,const uint32_t height,const uint32_t x, const uint32_t y,const uint8_t color)
{
	this->height = height;
	this->width = width;
	this->x = x;
	this->y = y;
	this->cursorX = 0;
	this->cursorY = 0;
	this->color = color;
	clrScreen();
	

}
void Terminal::moveHCursor(){
	uint16_t position = (x + cursorX) + (y + cursorY) * defwidth;
	// cursor LOW port to vga INDEX register
	outb(0x3D4, 0x0F);
	outb(0x3D5, (unsigned char)(position & 0xFF));
	// cursor HIGH port to vga INDEX register
	outb(0x3D4, 0x0E);
	outb(0x3D5, (unsigned char)((position >> 8) & 0xFF));
}
void Terminal::clrScreen(){
	for (int x = 0; x < width;x++){
		for (int y = 0; y < height; y++){
			memloc[this->x+x + ((y+this->y)*defwidth)] = color<<8;
		}
	}
}
void Terminal::printf(const char * fmt,...){
	//temporary impl
	putS(fmt);
}
void Terminal::putS(const char * fmt){
	uint32_t i = 0;
	while (fmt[i]!=0)
	{
		putC(fmt[i]);
		i++;

	}
}
void Terminal::putC(const char ch){
	memloc[x + cursorX + ((y + cursorY)*defwidth)] |= ch;

	cursorX++;
	if (cursorX == width){
		cursorX = 0;
		cursorY++;
	}
	if (cursorY == height){
		scroll();
	}
	moveHCursor();
}
void Terminal::scroll(uint32_t n ){
	if (n != 0){
		for (uint32_t y = 0; y < height; y++)
		{
			for (uint32_t x = 0; x < width; x++)
			{
				if (y >= n){
					memloc[this->x + x + ((y + this->y - n)*defwidth)] = memloc[this->x + x + ((y + this->y)*defwidth)];
				}
				memloc[this->x + x + ((y + this->y)*defwidth)] = color << 8;
			}
		}
		cursorY = cursorY>n ? cursorY - n: 0;
	}
	moveHCursor();
}
Terminal::~Terminal()
{
}

uint8_t Terminal::makeColor(colors_t bg, colors_t fg){
	return (bg << 4) | (fg & 0xF);
}