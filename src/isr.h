#ifndef _AMIROS_ISR_
#define _AMIROS_ISR_

typedef struct registers {
uint eax;
uint ebx;
uint ecx;
uint edx;
uint eip;
uint eflags;
uint esp;
uint ebp;
uint ss;
uint useresp;
uint es;
uint fs;
uint gs;
uint ds;
uint cs;
uint eci;
uint errnum;
uint errcode;
}registers;

typedef void (*isr_event)(registers);

void isr_handler(registers r);
void isr_register_event(isr_event*, uint);
void isr_unregister_event(uint);

#endif