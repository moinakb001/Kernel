#include <stddef.h>
#include <stdint.h>
 
#include "terminal.h"
#include "serial.h"
 

 
using namespace std;

STerminal term;
void eval(char * str){
	if(strcmp(str,"hi")==0){
		term.puts("hello\n");
	}
}
extern "C" void kernel_main() {
	/* Initialize terminal interface */
	term=STerminal();
	term.repl(0,eval);
	
}
