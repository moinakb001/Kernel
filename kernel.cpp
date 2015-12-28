#include <stddef.h>
#include <stdint.h>
 

#include "serial.h"
 

 
using namespace std;


void eval(char * str){
	if(1==1){
		term.puts("hello\n");
	}
}
extern "C" void kernel_main() {
	/* Initialize terminal interface */
	STerminal term;
	term=STerminal();
	term.repl(0,eval);
	
}
