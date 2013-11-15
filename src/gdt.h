#ifndef _AMIROS_GDT_H_
#define _AMIROS_GDT_H_

/*
*GDT functions
*/
extern void gdt_setup();
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

#endif