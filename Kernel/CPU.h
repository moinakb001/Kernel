#pragma once
#include <stdint.h>
#include "kmem.h"
#include "IO.h"
class CPU
{
	
public:
	typedef struct{
		char vendor[16];
		uint32_t features;
		void * gdt;
		void * idt;
	} cpuinfo_t;
#pragma pack(1)
	typedef struct{
		uint16_t size;
		uint32_t offset;
	} GDT_t;
	// any of the alignment in the structure.
#pragma pack(1)
	struct gdt_entry_struct
	{
		uint16_t limit_low;           // The lower 16 bits of the limit.
		uint16_t base_low;            // The lower 16 bits of the base.
		uint8_t  base_middle;         // The next 8 bits of the base.
		uint8_t  access;              // Access flags, determine what ring this segment can be used in.
		uint8_t  granularity;
		uint8_t  base_high;           // The last 8 bits of the base.
	};
	typedef struct gdt_entry_struct gdt_entry_t;
	cpuinfo_t info;
	
	uint32_t * cpuid(uint32_t function, uint32_t * outreg);
	void init();
	CPU();
	virtual ~CPU();
	void initGDT();
	//uint64_t GDT_Entry(uint32_t base, uint32_t limit, uint16_t flag);
	
};

