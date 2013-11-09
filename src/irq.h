#ifndef _AMIROS_IRQ_
#define _AMIROS_IRQ_

typedef void (*irq_event)(struct registers);

void irq_register_event(irq_event*, uint);
void irq_unregister_event(uint);
void irq_handler(registers);

#endif