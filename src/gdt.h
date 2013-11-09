#ifndef _AMIROS_GDT_H_
#define _AMIROS_GDT_H_

/*
*GDT functions
*/
extern void gdt_setup(uint);
extern void usermode_setup();
void set_tss(uint, uint, uint);
void set_stack(uint);
void gdt_init();
void gdt_set_gate(uint, uint, uint, uint, uint);

/*
*the GDT (Global Descripter table) structure
*/
struct gdt
{
uint low_limit;
uint low_base;
uint middle_base;
uint high_base;
uint access;
uint granularity;
} __attribute__((packed));
typedef struct gdt gdt;

/*
*the GDT pointer
*/
struct gdt_ptr
{
uint limit;
uint base;
} __attribute__((packed));
typedef struct gdt_ptr gdt_ptr;

struct tss
{
uint previous_task;
uint eax;
uint ebx;
uint ecx;
uint edx;
uint esp;
uint esp0;
uint esp1;
uint esp2;
uint ebp;
uint eci;
uint edi;
uint es;
uint cs;
uint ss;
uint ss0;
uint ss1;
uint ss2;
uint ds;
uint fs;
uint gs;
uint cr3;
uint eip;
uint flags;
uint ldt;
uint trap;
uint base_iomap;
}__attribute__((packed));

typedef struct tss tss;

#endif