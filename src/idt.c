#include <types.h>
#include <memory.h>
#include "io.h"
#include "idt.h"

idt idt_desc[256];
idt_ptr idt_desc_ptr;

/*
*initialize the IDT
*/
void idt_init()
{
idt_desc_ptr.limit=sizeof(idt);
idt_desc_ptr.base=(uint)&idt_desc;
memset(&idt_desc, 0, sizeof(idt)*256);
    outb(0x20, 0x11);
    outb(0xA0, 0x11);
    outb(0x21, 0x20);
    outb(0xA1, 0x28);
    outb(0x21, 0x04);
    outb(0xA1, 0x02);
    outb(0x21, 0x01);
    outb(0xA1, 0x01);
    outb(0x21, 0x0);
    outb(0xA1, 0x0);
    idt_set_gate( 0, (uint)isr0 , 0x08, 0x8E);
    idt_set_gate( 1, (uint)isr1 , 0x08, 0x8E);
    idt_set_gate( 2, (uint)isr2 , 0x08, 0x8E);
    idt_set_gate( 3, (uint)isr3 , 0x08, 0x8E);
    idt_set_gate( 4, (uint)isr4 , 0x08, 0x8E);
    idt_set_gate( 5, (uint)isr5 , 0x08, 0x8E);
    idt_set_gate( 6, (uint)isr6 , 0x08, 0x8E);
    idt_set_gate( 7, (uint)isr7 , 0x08, 0x8E);
    idt_set_gate( 8, (uint)isr8 , 0x08, 0x8E);
    idt_set_gate( 9, (uint)isr9 , 0x08, 0x8E);
    idt_set_gate(10, (uint)isr10, 0x08, 0x8E);
    idt_set_gate(11, (uint)isr11, 0x08, 0x8E);
    idt_set_gate(12, (uint)isr12, 0x08, 0x8E);
    idt_set_gate(13, (uint)isr13, 0x08, 0x8E);
    idt_set_gate(14, (uint)isr14, 0x08, 0x8E);
    idt_set_gate(15, (uint)isr15, 0x08, 0x8E);
    idt_set_gate(16, (uint)isr16, 0x08, 0x8E);
    idt_set_gate(17, (uint)isr17, 0x08, 0x8E);
    idt_set_gate(18, (uint)isr18, 0x08, 0x8E);
    idt_set_gate(19, (uint)isr19, 0x08, 0x8E);
    idt_set_gate(20, (uint)isr20, 0x08, 0x8E);
    idt_set_gate(21, (uint)isr21, 0x08, 0x8E);
    idt_set_gate(22, (uint)isr22, 0x08, 0x8E);
    idt_set_gate(23, (uint)isr23, 0x08, 0x8E);
    idt_set_gate(24, (uint)isr24, 0x08, 0x8E);
    idt_set_gate(25, (uint)isr25, 0x08, 0x8E);
    idt_set_gate(26, (uint)isr26, 0x08, 0x8E);
    idt_set_gate(27, (uint)isr27, 0x08, 0x8E);
    idt_set_gate(28, (uint)isr28, 0x08, 0x8E);
    idt_set_gate(29, (uint)isr29, 0x08, 0x8E);
    idt_set_gate(30, (uint)isr30, 0x08, 0x8E);
    idt_set_gate(31, (uint)isr31, 0x08, 0x8E);
    idt_set_gate(32, (uint)irq0, 0x08, 0x8E);
    idt_set_gate(33, (uint)irq1, 0x08, 0x8E);
    idt_set_gate(34, (uint)irq2, 0x08, 0x8E);
    idt_set_gate(35, (uint)irq3, 0x08, 0x8E);
    idt_set_gate(36, (uint)irq4, 0x08, 0x8E);
    idt_set_gate(37, (uint)irq5, 0x08, 0x8E);
    idt_set_gate(38, (uint)irq6, 0x08, 0x8E);
    idt_set_gate(39, (uint)irq7, 0x08, 0x8E);
    idt_set_gate(40, (uint)irq8, 0x08, 0x8E);
    idt_set_gate(41, (uint)irq9, 0x08, 0x8E);
    idt_set_gate(42, (uint)irq10, 0x08, 0x8E);
    idt_set_gate(43, (uint)irq11, 0x08, 0x8E);
    idt_set_gate(44, (uint)irq12, 0x08, 0x8E);
    idt_set_gate(45, (uint)irq13, 0x08, 0x8E);
    idt_set_gate(46, (uint)irq14, 0x08, 0x8E);
    idt_set_gate(47, (uint)irq15, 0x08, 0x8E);
idt_setup();
}

/*
*this function set's the IDT
*/
void idt_set_gate(uint number, uint base, uint selector, uint flags)
{
idt_desc[number].low_base=base & 0xFFFF;
idt_desc[number].high_base=(base>>16)&0xFFFF;
idt_desc[number].selector=selector;
idt_desc[number].always0=0;
idt_desc[number].flags=flags;
}
