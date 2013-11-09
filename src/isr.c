#include <types.h>
#include <screen.h>
#include "isr.h"

const uchar* expmsg[32]=
{
"divided by 0!",
"debug exception acurd!",
"nonmaskable interrupt exception acurd!",
"breakpoint exception acurd!",
"into detected overflow exception!",
"out of bounds!",
"invalid opcode!",
"no coprocessor available!",
"double fault!",
"coprocessor segment overrun!",
"Bad TSS!",
"segment not available!",
"stack fault!",
"genral protection fault: no permition!",
"page fault exception!",
"unknown interrupt!",
"coprocessor fault!",
"alignment check!",
"machine check exception!",
"error 19: reserved by intel!",
"error 20: reserved by intel!",
"error 21: reserved by intel!",
"error 22: reserved by intel!",
"error 23: reserved by intel!",
"error 24: reserved by intel!",
"error 25: reserved by intel!",
"error 26: reserved by intel!",
"error 27: reserved by intel!",
"error 28: reserved by intel!",
"error 29: reserved by intel!",
"error 30: reserved by intel!",
"error 31: reserved by intel!"
};

isr_event isr[32];

void isr_handler(registers r)
{
isr_event t=isr[r.errnum];
t(r);
if(r.errnum<32)
{
print((pointer)expmsg[r.errnum], "halting!");
for(;;);
}
}

void isr_register_event(isr_event *event, uint n)
{
isr[n]=&event;
}

void isr_unregister_event(uint n)
{
isr[n]=0;
}
