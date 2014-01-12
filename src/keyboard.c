#include <types.h>
#include "isr.h"
#include "io.h"
#include "irq.h"
#include <keyboard.h>
#include "keyboard.h"

const uchar keycodes[128]=
{
0, 27, '1', '2', '3', '4', '5', '6', '7', '8', /* 9 */ '9', '0', '-', '=', '\b', /* Backspace */ '\t', /* Tab */ 'q', 'w', 'e', 'r', /* 19 */ 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\r', /* Enter key */ 0, /* 29 - Control */ 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', /* 39 */ '\'', '`', 0, /* Left shift */ '\\', 'z', 'x', 'c', 'v', 'b', 'n', /* 49 */ 'm', ',', '.', '/', 0, /* Right shift */ '*', 0, /* Alt */ ' ', /* Space bar */ 0, /* Caps lock */ 0, /* 59 - F1 key ... > */ 0, 0, 0, 0, 0, 0, 0, 0, 0, /* < ... F10 */ 0, /* 69 - Num lock*/ 0, /* Scroll Lock */ 0, /* Home key */ 0, /* Up Arrow */ 0, /* Page Up */ '-', 0, /* Left Arrow */ 0, 0, /* Right Arrow */ '+', 0, /* 79 - End key*/ 0, /* Down Arrow */ 0, /* Page Down */ 0, /* Insert Key */ 0, /* Delete Key */ 0, 0, 0, 0, /* F11 Key */ 0, /* F12 Key */ 0, /* All other keys are undefined */ 
};

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
if(k==keycodes[58]&&capslock==true)
{
capslock=false;
}
if(k==keycodes[69]&&numlock==true)
{
numlock=false;
}
if(key==keycodes[70]&&scrolllock==true)
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
return keycodes[key];
}
