#pragma once
#include <cstdarg>
#include <cstdint>
class Terminal
{
public:

	enum colors_t:uint8_t{black=0,blue=1,green=2,cyan=3,red=4,magenta=5,brown=6,lgray=7,dgray=8,lblue=9,lgreen=10,lcyan=11,lred=12,lmagenta=13,yellow=14,white=15};
	
	Terminal(const uint32_t width,const uint32_t height, const uint32_t x, const uint32_t y,const uint8_t color);
	Terminal();
	virtual ~Terminal();

	void printf(const char * fmt,...);
	void putS(const char * str);
	void putC(const char ch);
	void clrScreen();
	void scroll(uint32_t n = 1);
	void setColor(uint8_t color);

	static uint8_t makeColor(colors_t bg, colors_t fg);

	const uint32_t defheight = 25;
	const uint32_t defwidth = 80;

private:
	void moveHCursor();
	uint16_t * memloc = (uint16_t *)0xB8000;
	uint32_t height;
	uint32_t width;
	uint32_t x;
	uint32_t y;
	uint32_t cursorX;
	uint32_t cursorY;
	uint8_t color;

};

