CC = i686-elf-gcc
CFLAGS = -ffreestanding -O2 -Wall -Wextra
LDFLAGS = -T linker.ld -ffreestanding -nostdlib

all: os.iso

kernel.bin:
	$(CC) $(CFLAGS) -c kernel/kernel.c -o kernel.o
	$(CC) $(CFLAGS) -c kernel/terminal.c -o terminal.o
	$(CC) $(CFLAGS) -c kernel/string.c -o string.o
	$(CC) $(LDFLAGS) kernel.o terminal.o string.o -o kernel.bin

os.iso: kernel.bin
	mkdir -p iso/boot/grub
	cp kernel.bin iso/boot/kernel.bin
	cp boot/grub.cfg iso/boot/grub/grub.cfg
	grub-mkrescue -o os.iso iso

run: os.iso
	qemu-system-i386 -cdrom os.iso

clean:
	rm -rf *.o *.bin iso os.iso
