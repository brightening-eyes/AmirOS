[bits 32]

global Boot
global gdt_setup
global idt_setup
global inb
global outb
global isr0
global isr1
global isr2
global isr3
global isr4
global isr5
global isr6
global isr7
global isr8
global isr9
global isr10
global isr11
global isr12
global isr13
global isr14
global isr15
global isr16
global isr17
global isr18
global isr19
global isr20
global isr21
global isr22
global isr23
global isr24
global isr25
global isr26
global isr27
global isr28
global isr29
global isr30
global isr31
global isr_stub
global irq0
global irq1
global irq2
global irq3
global irq4
global irq5
global irq6
global irq7
global irq8
global irq9
global irq10
global irq11
global irq12
global irq13
global irq14
global irq15
global irq_stub
extern LoadKernel
extern gdt_desc_ptr
extern idt_desc_ptr
extern isr_handler
extern irq_handler

;do not edit here!:this section is only for grub
section .boot
align 0x4
MODULEALIGN equ 1<<0
MEMINFO equ 1<<1
FLAGS equ MODULEALIGN|MEMINFO
MAGIC equ 0x1BADB002
CHECKSUM equ -(MAGIC+FLAGS)

boothdr:
dd MAGIC
dd FLAGS
dd CHECKSUM

;now you can modify
Boot:
push ebx ;takes the multiboot structure
call LoadKernel ;load are Operating System kernel
jmp $
section .text
gdt_setup:
LGDT[gdt_desc_ptr]
mov eax, 0x10
mov ds, eax
mov es, eax
mov fs, eax
mov gs, eax
mov ss, eax
jmp 0x08:.flush

.flush:
ret

idt_setup:
LIDT[idt_desc_ptr]
ret

outb:
    ; Get arguments
    mov al, [esp + 8] ; value
    mov dx, [esp + 4] ; addr

    ; Write out
    out dx, al
    ret

inb:
    ; Get argument
    mov dx, [esp + 4]

    ; Read in
    in al, dx
ret

halt:
cli
hlt
ret

disable_idt:
cli
ret

enable_idt:
sti
ret

isr0:
cli
push byte 0
push byte 0
jmp isr_stub

isr1:
cli
push byte 0
push byte 1
jmp isr_stub

isr2:
cli
push byte 0
push byte 2
jmp isr_stub

isr3:
cli
push byte 0
push byte 3
jmp isr_stub

isr4:
cli
push byte 0
push byte 4
jmp isr_stub

isr5:
cli
push byte 0
push byte 5
jmp isr_stub

isr6:
cli
push byte 0
push byte 6
jmp isr_stub

isr7:
cli
push byte 0
push byte 7
jmp isr_stub

isr8:
cli
push byte 8
jmp isr_stub

isr9:
cli
push byte 0
push byte 9
jmp isr_stub

isr10:
cli
push byte 10
jmp isr_stub

isr11:
cli
push byte 11
jmp isr_stub

isr12:
cli
push byte 12
jmp isr_stub

isr13:
cli
push byte 13
jmp isr_stub

isr14:
cli
push byte 14
jmp isr_stub

isr15:
cli
push byte 0
push byte 15
jmp isr_stub

isr16:
cli
push byte 0
push byte 16
jmp isr_stub

isr17:
cli
push byte 0
push byte 17
jmp isr_stub

isr18:
cli
push byte 0
push byte 18
jmp isr_stub

isr19:
cli
push byte 0
push byte 19
jmp isr_stub

isr20:
cli
push byte 0
push byte 20
jmp isr_stub

isr21:
cli
push byte 0
push byte 21
jmp isr_stub

isr22:
cli
push byte 0
push byte 22
jmp isr_stub

isr23:
cli
push byte 0
push byte 23
jmp isr_stub

isr24:
cli
push byte 0
push byte 24
jmp isr_stub

isr25:
cli
push byte 0
push byte 25
jmp isr_stub

isr26:
cli
push byte 0
push byte 26
jmp isr_stub

isr27:
cli
push byte 0
push byte 27
jmp isr_stub

isr28:
cli
push byte 0
push byte 28
jmp isr_stub

isr29:
cli
push byte 0
push byte 29
jmp isr_stub

isr30:
cli
push byte 0
push byte 30
jmp isr_stub

isr31:
cli
push byte 0
push byte 31
jmp isr_stub

irq0:
cli
push byte 0
push byte 32
jmp irq_stub

irq1:
cli
push byte 0
push byte 33
jmp irq_stub

irq2:
cli
push byte 0
push byte 34
jmp irq_stub

irq3:
cli
push byte 0
push byte 35
jmp irq_stub

irq4:
cli
push byte 0
push byte 36
jmp irq_stub

irq5:
cli
push byte 0
push byte 37
jmp irq_stub

irq6:
cli
push byte 0
push byte 38
jmp irq_stub

irq7:
cli
push byte 0
push byte 39
jmp irq_stub

irq8:
cli
push byte 0
push byte 40
jmp irq_stub

irq9:
cli
push byte 0
push byte 41
jmp irq_stub

irq10:
cli
push byte 0
push byte 42
jmp irq_stub

irq11:
cli
push byte 0
push byte 43
jmp irq_stub

irq12:
cli
push byte 0
push byte 44
jmp irq_stub

irq13:
cli
push byte 0
push byte 45
jmp irq_stub

irq14:
cli
push byte 0
push byte 46
jmp irq_stub

irq15:
cli
push byte 0
push byte 47
jmp irq_stub

isr_stub:
pusha
push ds
push es
push fs
push gs
mov eax, 0x10
mov ds, eax
mov es, eax
mov fs, eax
mov gs, eax
mov eax, esp
push eax
call isr_handler
pop eax
pop gs
pop fs
pop es
pop ds
popa
add esp, 8
iret

irq_stub:
pusha
push ds
push es
push fs
push gs
mov eax, 0x10
mov gs, eax
mov fs, eax
mov es, eax
mov ds, eax
mov eax, esp
push eax
call irq_handler
pop eax
pop gs
pop fs
pop ds
pop es
popa
add esp, 8
iret

section .bss
resb 8192
