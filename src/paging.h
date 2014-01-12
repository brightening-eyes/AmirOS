#ifndef _AMIROS_PAGING_H_
#define _AMIROS_PAGING_H_

typedef struct page
{
uint present    : 1;
uint rw         : 1;
uint user       : 1;
uint accessed   : 1;
uint dirty      : 1;
uint unused     : 7;
uint frame      : 20;
}page;

typedef struct page_table
{
    page pages[1024];
} page_table;

typedef struct page_directory
{
    page_table *tables[1024];
uint tablesPhysical[1024];
uint physicalAddr;
} page_directory;

void paging_init();
void switch_page_directory(page_directory*);
page* get_page(uint, int, page_directory*);
void page_fault(registers);

#endif
