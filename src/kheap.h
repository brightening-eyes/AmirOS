
#ifndef _AMIROS_KHEAP_H_
#define _AMIROS_KHEAP_H_

uint kmalloc_int(uint sz, int align, uint *phys);
uint kmalloc_a(uint sz);
uint kmalloc_p(uint sz, uint *phys);
uint kmalloc_ap(uint sz, uint *phys);
uint kmalloc(uint sz);

#endif
