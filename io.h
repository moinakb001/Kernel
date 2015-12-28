#ifndef IO_H
#define IO_H
#include <stdint.h>

static inline void outb(uint16_t port, uint8_t val)
{
    asm volatile ( "outb %0, %1" : : "a"(val), "Nd"(port) );
    /* TODO: Is it wrong to use 'N' for the port? It's not a 8-bit constant. */
    /* TODO: Should %1 be %w1? */
}
static inline uint8_t inb(uint16_t port)
{
    uint8_t ret;
    asm volatile ( "inb %1, %0" : "=a"(ret) : "Nd"(port) );
    /* TODO: Is it wrong to use 'N' for the port? It's not a 8-bit constant. */
    /* TODO: Should %1 be %w1? */
    return ret;
}
static inline void lidt(void* base, uint16_t size)
{
    struct
    {
        uint16_t length;
        uint32_t base;
    } __attribute__((packed)) IDTR;
 
    IDTR.length = size;
    IDTR.base = (uint32_t) base;
    asm ( "lidt (%0)" : : "p"(&IDTR) );
}
static inline void lgdt(void* base, uint16_t size)
{
    struct
    {
        uint16_t length;
        uint32_t base;
    } __attribute__((packed)) GDTR;
 
    GDTR.length = size;
    GDTR.base = (uint32_t) base;
    asm ( "lgdt (%0)" : : "p"(&GDTR) );
}
static inline uint32_t * cpuid(uint32_t code, uint32_t * where) {
  asm volatile("cpuid":"=a"(where[0]),"=b"(where[1]),
               "=c"(where[2]),"=d"(where[3]):"a"(code));
  return where;
}
static inline void wrmsr(uint32_t msr_id, uint64_t msr_value)
{
    asm volatile ( "wrmsr" : : "c" (msr_id), "A" (msr_value) );
}
static inline uint64_t rdmsr(uint32_t msr_id)
{
    uint64_t msr_value;
    asm volatile ( "rdmsr" : "=A" (msr_value) : "c" (msr_id) );
    return msr_value;
}
static inline uint64_t read_cr0(void)
{
    uint64_t val;
    asm volatile ( "mov %%cr0, %0" : "=r"(val) );
    return val;
}
static inline uint64_t read_cr1(void)
{
    uint64_t val;
    asm volatile ( "mov %%cr1, %0" : "=r"(val) );
    return val;
}
static inline uint64_t read_cr2(void)
{
    uint64_t val;
    asm volatile ( "mov %%cr2, %0" : "=r"(val) );
    return val;
}
static inline uint64_t read_cr3(void)
{
    uint64_t val;
    asm volatile ( "mov %%cr3, %0" : "=r"(val) );
    return val;
}
static inline uint64_t read_cr4(void)
{
    uint64_t val;
    asm volatile ( "mov %%cr4, %0" : "=r"(val) );
    return val;
}
static inline void write_cr0(uint32_t val)
{
    asm volatile ( "mov  %0,%%cr0" ::"r"(val));
}
static inline void write_cr1(uint32_t val)
{
    asm volatile ( "mov  %0,%%cr1" ::"r"(val));
}
static inline void write_cr2(uint32_t val)
{
    asm volatile ( "mov  %0,%%cr2" ::"r"(val));
}
static inline void write_cr3(uint32_t val)
{
    asm volatile ( "mov  %0,%%cr3" ::"r"(val));
}
static inline void write_cr4(uint32_t val)
{
    asm volatile ( "mov  %0,%%cr4" ::"r"(val));
}
static inline void cli()
{
    asm volatile ( "cli" );
}
static inline void sti()
{
    asm volatile ( "sti" );
}
static inline void iret(uint32_t ss, uint32_t esp, uint32_t flags, uint32_t cs, uint32_t eip)
{
    asm volatile ( "push  %0" ::"r"(ss));
	asm volatile ( "push  %0" ::"r"(esp));
	asm volatile ( "push  %0" ::"r"(flags));
	asm volatile ( "push  %0" ::"r"(cs));
	asm volatile ( "push  %0" ::"r"(eip));
	asm volatile ( "iret");
}
#endif