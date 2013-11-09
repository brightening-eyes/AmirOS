#include <types.h>
#include "gdt.h"
#include "idt.h"
#include "timer.h"
#include "keyboard.h"
#include "init.h"

void init()
{
gdt_init();
idt_init();
timer_init();
keyboard_init();
usermode_setup();
}