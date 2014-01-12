#include <types.h>
#include "kheap.h"

extern uint end;
uint placement_address = (uint)&end;
uint kmalloc_int(uint sz, int align, uint *phys)
{
if (align == 1 && (placement_address & 0xFFFFF000) )
{
placement_address &= 0xFFFFF000;
placement_address += 0x1000;
}
if (phys)
{
*phys = placement_address;
}
uint tmp = placement_address;
placement_address += sz;
return tmp;
}

uint kmalloc_a(uint sz)
{
return kmalloc_int(sz, 1, 0);
}

uint kmalloc_p(uint sz, uint *phys)
{
return kmalloc_int(sz, 0, phys);
}

uint kmalloc_ap(uint sz, uint *phys)
{
return kmalloc_int(sz, 1, phys);
}

uint kmalloc(uint sz)
{
return kmalloc_int(sz, 0, 0);
}
