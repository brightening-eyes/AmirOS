#include <types.h>
#include "isr.h"
#include "irq.h"
#include "io.h"
#include "timer.h"

uint timer_tics;

void timer(registers r)
{
int hz;
int divisor=1193180/hz;
outb(0x43, 0x36);
outb(0x40, divisor&0xFF);
outb(0x40, divisor>>8);
timer_tics++;
while(timer_tics%100==0);
}

void timer_init()
{
irq_register_handler(timer, 0);
}

void wait(uint seconds)
{
seconds=seconds+timer_tics;
for(;seconds>timer_tics;--seconds)
{
for(;;);
}
}
