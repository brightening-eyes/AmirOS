#include <types.h>
#include <screen.h>
#include "kheap.h"
#include "isr.h"
#include "paging.h"

page_directory *kernel_directory=0;
page_directory *current_directory=0;

uint *frames;
uint nframes;

uint placement_address;

#define INDEX_FROM_BIT(a) (a/(8*4))
#define OFFSET_FROM_BIT(a) (a%(8*4))

void set_frame(uint frame_address)
{
uint frame = frame_address/0x1000;
uint idx = INDEX_FROM_BIT(frame);
uint off = OFFSET_FROM_BIT(frame);
frames[idx] |= (0x1 << off);
}

void clear_frame(uint frame_address)
{
uint frame = frame_address/0x1000;
uint idx = INDEX_FROM_BIT(frame);
uint off = OFFSET_FROM_BIT(frame);
frames[idx] &= ~(0x1 << off);
}

uint test_frame(uint frame_address)
{
uint frame = frame_address/0x1000;
uint idx = INDEX_FROM_BIT(frame);
uint off = OFFSET_FROM_BIT(frame);
return (frames[idx] & (0x1 << off));
}

uint first_frame()
{
uint i, j;
for (i = 0; i < INDEX_FROM_BIT(nframes); i++)
{
if (frames[i] != 0xFFFFFFFF) // nothing free, exit early.
{
for (j = 0; j < 32; j++)
{
uint toTest = 0x1 << j;
if ( !(frames[i]&toTest) )
{
return i*4*8+j;
}
}
}
}
}

void alloc_frame(page *page, int is_kernel, int is_writeable)
{
if (page->frame != 0)
{
return;
    }
else
{
uint idx = first_frame();
if (idx == (uint)-1)
{

        }
set_frame(idx*0x1000);
page->present = 1;
page->rw = (is_writeable)?1:0;
page->user = (is_kernel)?0:1;
page->frame = idx;
    }
}

void free_frame(page *page)
{
uint frame;
if (!(frame=page->frame))
{
return;
}
else
{
clear_frame(frame);
page->frame = 0x0;
}
}

void paging_init()
{
uint mem_end_page = 0x1000000;    
nframes = mem_end_page / 0x1000;
frames = (uint*)kmalloc(INDEX_FROM_BIT(nframes));
memset(frames, 0, INDEX_FROM_BIT(nframes));    
    kernel_directory = (page_directory*)kmalloc_a(sizeof(page_directory));
    current_directory = kernel_directory;
int i = 0;
while (i < placement_address)
{
alloc_frame( get_page(i, 1, kernel_directory), 0, 0);
i += 0x1000;
}
isr_register_event(page_fault, 14);
switch_page_directory(kernel_directory);
}

void switch_page_directory(page_directory *dir)
{
current_directory = dir;
asm volatile("mov %0, %%cr3":: "r"(&dir->tablesPhysical));
uint cr0;
asm volatile("mov %%cr0, %0": "=r"(cr0));
cr0 |= 0x80000000;
asm volatile("mov %0, %%cr0":: "r"(cr0));
}

page *get_page(uint address, int make, page_directory *dir)
{
address /= 0x1000;
uint table_idx = address / 1024;
if (dir->tables[table_idx])
{
return &dir->tables[table_idx]->pages[address%1024];
}
else if(make)
{
uint tmp;
dir->tables[table_idx] = (page_table*)kmalloc_ap(sizeof(page_table), &tmp);
dir->tablesPhysical[table_idx] = tmp | 0x7;
return &dir->tables[table_idx]->pages[address%1024];
}
else
{
return 0;
}
}

void page_fault(registers regs)
{
uint faulting_address;
asm volatile("mov %%cr2, %0" : "=r" (faulting_address));    
int present   = !(regs.errcode & 0x1);
int rw = regs.errcode & 0x2;
int us = regs.errcode & 0x4;
    int reserved = regs.errcode&0x8;
    int id = regs.errcode&0x10;
print("page fault occured!\n:");
if (present)
{
print("the page isn't present!");
}
if (rw)
{
print("the page isn't writable!");
}
if (us)
{
print("the page isn't accessable by user!");
}
    if (reserved)
{
print("the page is reserved!");
}
}
