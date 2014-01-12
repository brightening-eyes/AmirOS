#include <types.h>
#include "gdt.h"
#include "idt.h"
#include "timer.h"
#include "keyboard.h"
#include "init.h"
#include "paging.h"

void init()
{
gdt_init();
idt_init();
paging_init();
timer_init(50);
keyboard_init();
}
