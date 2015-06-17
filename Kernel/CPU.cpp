#include "CPU.h"
#include "Terminal.h"
#include "kmem.h"
// Each define here is for a specific flag in the descriptor.
// Refer to the intel documentation for a description of what each one does.
#define SEG_DESCTYPE(x)  ((x) << 0x04) // Descriptor type (0 for system, 1 for code/data)
#define SEG_PRES(x)      ((x) << 0x07) // Present
#define SEG_SAVL(x)      ((x) << 0x0C) // Available for system use
#define SEG_LONG(x)      ((x) << 0x0D) // Long mode
#define SEG_SIZE(x)      ((x) << 0x0E) // Size (0 for 16-bit, 1 for 32)
#define SEG_GRAN(x)      ((x) << 0x0F) // Granularity (0 for 1B - 1MB, 1 for 4KB - 4GB)
#define SEG_PRIV(x)     (((x) &  0x03) << 0x05)   // Set privilege level (0 - 3)

#define SEG_DATA_RD        0x00 // Read-Only
#define SEG_DATA_RDA       0x01 // Read-Only, accessed
#define SEG_DATA_RDWR      0x02 // Read/Write
#define SEG_DATA_RDWRA     0x03 // Read/Write, accessed
#define SEG_DATA_RDEXPD    0x04 // Read-Only, expand-down
#define SEG_DATA_RDEXPDA   0x05 // Read-Only, expand-down, accessed
#define SEG_DATA_RDWREXPD  0x06 // Read/Write, expand-down
#define SEG_DATA_RDWREXPDA 0x07 // Read/Write, expand-down, accessed
#define SEG_CODE_EX        0x08 // Execute-Only
#define SEG_CODE_EXA       0x09 // Execute-Only, accessed
#define SEG_CODE_EXRD      0x0A // Execute/Read
#define SEG_CODE_EXRDA     0x0B // Execute/Read, accessed
#define SEG_CODE_EXC       0x0C // Execute-Only, conforming
#define SEG_CODE_EXCA      0x0D // Execute-Only, conforming, accessed
#define SEG_CODE_EXRDC     0x0E // Execute/Read, conforming
#define SEG_CODE_EXRDCA    0x0F // Execute/Read, conforming, accessed

#define GDT_CODE_PL0 SEG_DESCTYPE(1) | SEG_PRES(1) | SEG_SAVL(0) | \
                     SEG_LONG(0)     | SEG_SIZE(1) | SEG_GRAN(1) | \
                     SEG_PRIV(0)     | SEG_CODE_EXRD

#define GDT_DATA_PL0 SEG_DESCTYPE(1) | SEG_PRES(1) | SEG_SAVL(0) | \
                     SEG_LONG(0)     | SEG_SIZE(1) | SEG_GRAN(1) | \
                     SEG_PRIV(0)     | SEG_DATA_RDWR

#define GDT_CODE_PL3 SEG_DESCTYPE(1) | SEG_PRES(1) | SEG_SAVL(0) | \
                     SEG_LONG(0)     | SEG_SIZE(1) | SEG_GRAN(1) | \
                     SEG_PRIV(3)     | SEG_CODE_EXRD

#define GDT_DATA_PL3 SEG_DESCTYPE(1) | SEG_PRES(1) | SEG_SAVL(0) | \
                     SEG_LONG(0)     | SEG_SIZE(1) | SEG_GRAN(1) | \
                     SEG_PRIV(3)     | SEG_DATA_RDWR

CPU::CPU()
{

}
__declspec(naked) static void reserve(){
	__asm{
		dd(0)
		dd(0)
		dd(0)
		dd(0)
		dd(0)
		dd(0)
		dd(0)
		dd(0)
		dd(0)
		dd(0)
	}
}
 CPU::gdt_entry_t * GDT;
static void gdt_set_gate(uint32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran)
{
	GDT[num].base_low = (base & 0xFFFF);
	GDT[num].base_middle = (base >> 16) & 0xFF;
	GDT[num].base_high = (base >> 24) & 0xFF;

	GDT[num].limit_low = (limit & 0xFFFF);
	GDT[num].granularity = (limit >> 16) & 0x0F;

	GDT[num].granularity |= gran & 0xF0;
	GDT[num].access = access;
}
void CPU::initGDT(){
	
	//GDT =(uint64_t *) reserve;
	GDT = (CPU::gdt_entry_t *)0xB0000;
	gdt_set_gate(0, 0, 0, 0, 0);                // Null segment
	gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Code segment
	gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Data segment
	gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // User mode code segment
	gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // User mode data segment
	/*	for (size_t i = 5; i < 8192; i++)
	{
		GDT[i] = 0;
		tr.putS("HELLO");
	}*/
	
	GDT_t str;
	str.offset = (uint32_t)GDT;
	str.size = 5*8-1;
	lgdt(GDT,5*8-1);
	Terminal tr = Terminal();
	refreshGDT(0x18, 0x20);
	tr.putS("HELLO");
}

uint32_t * CPU::cpuid(uint32_t function, uint32_t * outreg){
	__asm{
		mov eax, function;
		cpuid
			push eax
			mov eax, outreg
			add eax, 4
			mov[eax], ebx
			add eax, 4
			mov[eax], ecx
			add eax, 4
			mov[eax], edx
			pop eax
			mov ebx, outreg
			mov[ebx], eax
	}
	return outreg;
}

void CPU::init(){
	uint32_t list[4];
	/*cpuid(0, list);
	uint8_t * list1 = (uint8_t *)list;
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j <4; j++)
		{
			info.vendor[i * 4 + j] = list1[i * 4 + 3 - j];

		}
	}
	cpuid(1, list);
	info.features = list[3];*/
	initGDT();
	info.gdt = (void *)GDT;
}

CPU::~CPU()
{
}
