#include <types.h>
#include "gdt.h"

gdt gdt_desc[5];
gdt_ptr gdt_desc_ptr;

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
gdt_setup();
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
