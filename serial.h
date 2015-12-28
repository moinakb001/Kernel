#ifndef SERIAL_H
#define SERIAL_H
#include <stdint.h>
#include <stdarg.h> 
#include "io.h"
#include "string.h"
class STerminal{
	private:
		char buffer[1000];
		uint32_t index;
		void init_serial() ;
		int serial_received();
		char read_serial();
		int is_transmit_empty() ;
		void write_serial(char a) ;
	public:
		STerminal();
		char * readln();
		void putc(char c);
		void puts(char * str);
		void printf(char * fmt,...);
		void repl(uint32_t num,void (*eval)(char *));
	
	
};
#endif