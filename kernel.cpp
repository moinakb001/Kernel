#include <stddef.h>
#include <stdint.h>
 
 #include "terminal.h"
 #include "io.h"
 
 #define COM 0x3f8   /* COM1 */
 
using namespace std;

void init_serial() {
   outb(COM + 1, 0x00);    // Disable all interrupts
   outb(COM + 3, 0x80);    // Enable DLAB (set baud rate divisor)
   outb(COM + 0, 0x03);    // Set divisor to 3 (lo byte) 38400 baud
   outb(COM + 1, 0x00);    //                  (hi byte)
   outb(COM + 3, 0x03);    // 8 bits, no parity, one stop bit
   outb(COM + 2, 0xC7);    // Enable FIFO, clear them, with 14-byte threshold
   outb(COM + 4, 0x0B);    // IRQs enabled, RTS/DSR set
}
int serial_received() {
   return inb(COM + 5) & 1;
}
 
char read_serial() {
   while (serial_received() == 0);
 
   return inb(COM);
}
int is_transmit_empty() {
   return inb(COM + 5) & 0x20;
}
 
void write_serial(char a) {
   while (is_transmit_empty() == 0);
 
   outb(COM,a);
}
void write_serial_str(char * str){
	uint32_t len=strlen((uint8_t *)str);
	for(uint32_t i=0;i<len;i++){
		write_serial(str[i]);
	}
}
extern "C" void kernel_main() {
	/* Initialize terminal interface */
	init_serial();
	Terminal term=Terminal();
	term.setColor(Terminal::COLOR_LIGHT_MAGENTA,Terminal::COLOR_GREEN);
	term.printf("%sFU\n%s","kjg\n iyo","23");
	term.scroll();
	while(true){
		write_serial(read_serial());
		term.printf("%sFU\n%s","kjg\n iyo","23");
	}
	
}
