#include <stddef.h>
#include <stdint.h>
 

#include "serial.h"
 

 
using namespace std;

STerminal term;
void eval(char * str){
	if(strcmp((uint8_t *)str,(uint8_t *)"hi")==0){
		term.puts("hello\n");
	}
}
extern "C" void kernel_main() {
	/* Initialize terminal interface */
	term=STerminal();
	term.repl(0,eval);
	
}
