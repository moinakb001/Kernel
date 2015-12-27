#if !defined(__cplusplus)
#include <stdbool.h> /* C doesn't have booleans by default. */
#endif
#include <stddef.h>
#include <stdint.h>
 
/* Check if the compiler thinks we are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif
 
/* This tutorial will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif
 #include "terminal.h"
using namespace std;
extern "C" void kernel_main() {
	/* Initialize terminal interface */
	Terminal term=Terminal();
	term.setColor(Terminal::COLOR_LIGHT_MAGENTA,Terminal::COLOR_GREEN);
	term.printf("%sFU\n%s","kjg\n iyo","23");
	term.scroll();
}
