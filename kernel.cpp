#include <stddef.h>
#include <stdint.h>
 

#include "serial.h"
 

 
using namespace std;


void eval(char * str, STerminal * sterm){
	if(1==1){
		sterm->puts("hello\n");
	}
}
extern "C" void kernel_main() {
	/* Initialize terminal interface */
	STerminal term;
	term=STerminal();
	term.repl(0,eval);
	
}
