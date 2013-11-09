incdir=../include
CFLAGS=-I $(incdir) -ffreestanding -nostdinc -std=gnu99 -w
LDFLAGS=-T ../linker/link.ld -nostdlib -nodefaultlibs -lgcc
ASFLAGS=-f elf
obj=asm.o gdt.o idt.o init.o irq.o isr.o keyboard.o main.o memory.o timer.o vga.o

default: image

all: $(obj) link

clean:
	rm -rf $(obj) ../iso/boot/amiros ../amiros.iso

.s.o:
	nasm $(ASFLAGS) $< -o $@

.c.o:
	gcc -c $(CFLAGS) $< -o $@

link: all
	gcc $(LDFLAGS) $(obj) -o ../iso/boot/amiros

image: link
	mkisofs -R -b boot/grub/stage2_eltorito -no-emul-boot -V "AmirOS" -boot-load-size 4 -boot-info-table -o ../AmirOS.iso ../iso
