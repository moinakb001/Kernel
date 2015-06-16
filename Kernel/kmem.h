#include <stdint.h>
#include <stddef.h>
#ifndef KMEM_H
#define KMEM_H
namespace Kernel{


	void * malloc(size_t size);
	void free(void * t);
	void initMem();
	int Num();
}
#endif