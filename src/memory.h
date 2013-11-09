#ifndef _AMIROS_MEMORY_HEEP_
#define _AMIROS_MEMORY_HEEP_

uint kmalloc_int(uint, int, uint*);
uint kmalloc_a(uint);
uint kmalloc_p(uint, uint*);
uint kmalloc_ap(uint, uint*);
uint kmalloc(uint);

#endif