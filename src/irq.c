#include <types.h>
#include "io.h"
#include "isr.h"
#include "irq.h"

pointer irq_handlers[16]=
{
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

void irq_register_handler(irq_event *event, uint n)
{
irq_handlers[n]=&event;
}

void irq_unregister_handler(uint n)
{
irq_handlers[n]=0;
}

void irq_handler(registers r)
{
irq_event event;
event=irq_handlers[r.errnum-32];
if(event)
{
event(r);
if(r.errnum>=40)
{
outb(0xA0, 0X20);
}
outb(0X20, 0X20);
}
}
