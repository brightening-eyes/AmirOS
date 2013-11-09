#include <types.h>
#include "gdt.h"

gdt gdt_desc[5];
gdt_ptr gdt_desc_ptr;
tss tss_desc;

/*
*initialize the GDT
*/
void gdt_init()
{
gdt_desc_ptr.limit=(sizeof(gdt)*5);
gdt_desc_ptr.base=(uint)&gdt_desc_ptr;
gdt_set_gate(0, 0, 0, 0, 0);
gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);
gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);
set_tss(5, 0x10, 0x0);
gdt_setup((uint)&gdt_desc_ptr);
}

/*
*this function set's the GDT
*/
void gdt_set_gate(uint number, uint base, uint limit, uint access, uint granularity)
{
gdt_desc[number].low_base=(base &0xFFFF);
gdt_desc[number].middle_base=(base >> 16) & 0xFF;
gdt_desc[number].high_base=(base >> 24) & 0xFF;
gdt_desc[number].low_limit=(limit &0xFFFF);
gdt_desc[number].granularity=(limit>>16) &0x0F;
gdt_desc[number].granularity |= granularity & 0xF0;
gdt_desc[number].access      = access;
}

/*
*this function set's the tss
*/
void set_tss(uint number, uint ss0, uint esp0)
{
uint base=(uint)&tss_desc;
uint limit=base+sizeof(&tss_desc);
gdt_set_gate(number, base, limit, 0xE9, 0x00);
memset(&tss_desc, 0, sizeof(tss_desc));
tss_desc.ss0=ss0;
tss_desc.esp0=esp0;
tss_desc.cs=0x0B;
tss_desc.ss=0x13;
tss_desc.ds=0x13;
tss_desc.es=0x13;
tss_desc.fs=0x13;
tss_desc.gs=0x13;
}

/*
*this function update's the task
*/
void set_stack(uint stack)
{
tss_desc.esp0=stack;
}
