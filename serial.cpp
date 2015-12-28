#include "serial.h"
#define COM 0x3f8   /* COM1 */
using namespace std;
void STerminal::init_serial() {
   outb(COM + 1, 0x00);    // Disable all interrupts
   outb(COM + 3, 0x80);    // Enable DLAB (set baud rate divisor)
   outb(COM + 0, 0x03);    // Set divisor to 3 (lo byte) 38400 baud
   outb(COM + 1, 0x00);    //                  (hi byte)
   outb(COM + 3, 0x03);    // 8 bits, no parity, one stop bit
   outb(COM + 2, 0xC7);    // Enable FIFO, clear them, with 14-byte threshold
   outb(COM + 4, 0x0B);    // IRQs enabled, RTS/DSR set
}
int STerminal::serial_received() {
   return inb(COM + 5) & 1;
}
 
char STerminal::read_serial() {
   while (serial_received() == 0);
	char c=inb(COM);
	buffer[index]=c;
	index++;
   return c;
}
int STerminal::is_transmit_empty() {
   return inb(COM + 5) & 0x20;
}
 
void STerminal::write_serial(char a) {
   while (is_transmit_empty() == 0);
 
   outb(COM,a);
}
STerminal::STerminal(){
	index=0;
	init_serial();
}
char * STerminal::readln(){
	while((index==0?0:buffer[index])!='\n'){
		read_serial();
		putc(buffer[index]);
	}
	buffer[index-1]=0;
	index=0;
	return buffer;
	
}
void STerminal::putc(char c){
	if(c=='\n'){
		write_serial('\r');
	}
	write_serial(c);
}
void STerminal::puts(char * str){
	uint32_t len=strlen((uint8_t *)str);
	for(uint32_t i=0;i<len;i++){
		putc(str[i]);
	}
}
void STerminal::printf(char *fmt, ...){
	va_list vl;
	va_start(vl,fmt);
	uint32_t len=strlen((uint8_t *)fmt);
	for(uint32_t i=0;i<len;i++){
		if(fmt[i]=='%'){
			i++;
			switch(fmt[i]){
				case 's':
					puts(va_arg(vl,char *));
					break;
			}
		}else{
			putc(fmt[i]);
		}
	}
	va_end(vl);
}
void STerminal::repl(uint32_t num,void (*eval)(char *,STerminal *)){
	if(num==0){
		while(true){
			putc('>');
			(*eval)(readln(),this);
		}
	}else{
		for(uint32_t i=0;i<num;i++){
			putc('>');
			(*eval)(readln(), this);
		}
	}
}