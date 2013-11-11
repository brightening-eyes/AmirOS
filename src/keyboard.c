#include <types.h>
#include "isr.h"
#include "io.h"
#include "irq.h"
#include <keyboard.h>
#include "keyboard.h"

uchar k;
bool capslock;
bool numlock;
bool scrolllock;

void keyboard(registers r)
{
uint key=inb(0x60);
k=keycodes[key];
if((inb(0x64) & 2) == 0)
{
if(k==keycodes[58])
{
capslock=true;
}
else if(k==keycodes[69])
{
numlock=true;
}
else if(k==keycodes[70])
{
scrolllock=true;
}
}
if(capslock==1)
{
outb(0x60, 0xED2);
}
if(numlock==1)
{
outb(0x60, 0xED1);
}
if(scrolllock==1)
{
outb(0x60, 0xED0);
}
if(k==keycodes[58]&&capslock==1)
{
capslock=false;
}
if(k==keycodes[69]&&numlock==1)
{
numlock=false;
}
if(key==keycodes[70]&&scrolllock==1)
{
scrolllock=false;
}
}

void keyboard_init()
{
irq_register_handler(keyboard, 1);
}

uint get_key_ascii()
{
return (uint)k;
}

uchar convert_key_to_character(uint key)
{
return (uchar)k;
}