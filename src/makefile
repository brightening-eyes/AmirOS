target=i686-pc-elf
cc=$(target)-gcc
cpp=$(target)-g++
incdir=../include
CFLAGS=-I $(incdir) -ffreestanding -nostdinc -std=gnu99 -Wall -Wextra
LDFLAGS=-T ../linker/link.ld -nostdlib -nodefaultlibs
ASFLAGS=-f elf
obj=asm.o gdt.o idt.o init.o irq.o isr.o kheap.o keyboard.o main.o memory.o paging.o timer.o vga.o

default: image

all: $(obj) link

clean:
	rm -rf $(obj) ../iso/boot/amiros ../amiros.iso

.s.o:
	nasm $(ASFLAGS) $< -o $@

.c.o:
	$(cc) -c $(CFLAGS) $< -o $@

link: all
	$(cc) $(LDFLAGS) $(obj) -o ../iso/boot/amiros

image: link
	mkisofs -R -b boot/grub/stage2_eltorito -no-emul-boot -V "AmirOS" -boot-load-size 4 -boot-info-table -o ../AmirOS.iso ../iso
