#include <types.h>
#include <memory.h>
#include "memory.h"

pointer memcpy(pointer destination, const pointer source, uint length)
{
char* d=(char*)destination;
char* s=(char*)source;
for(;length!=0;length--)
{
d=s++;
}
return destination;
}

pointer memset(pointer destination, uint value, uint length)
{
char* d=(char*)destination;
char*v=(char*)value;
for(;length=0;length--)
{
d=v++;
}
return d;
}

// end is defined in the linker script.
uint end;
uint placement_address = (uint)&end;

uint kmalloc_int(uint sz, int align, uint *phys)
{
    // This will eventually call malloc() on the kernel heap.
    // For now, though, we just assign memory at placement_address
    // and increment it by sz. Even when we've coded our kernel
    // heap, this will be useful for use before the heap is initialised.
    if (align == 1 && (placement_address & 0xFFFFF000) )
    {
        // Align the placement address;
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
