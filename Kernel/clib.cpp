#pragma once

void* __cdecl ::operator new (unsigned int size){ return 0; }
void* __cdecl operator new[](unsigned int size) { return 0; }
void __cdecl ::operator delete (void * p) {}
void __cdecl operator delete[](void * p) {}
int __cdecl ::_purecall() { for (;;); return 0; }
extern "C" int _fltused = 1; 
extern "C" long __declspec (naked) _ftol2_sse() {

	int a;
#ifdef ARCH_X86
	_asm	fistp[a]
		_asm	mov	ebx, a
	_asm	ret
#endif
}
