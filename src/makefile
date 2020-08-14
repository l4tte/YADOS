ASMARGS=-felf32
COMPARGS=-x c -c -C -std=gnu99 -nostdlib -ffreestanding -Wall -Wextra -O2 -m32

compile: boot.asm main.c
	nasm $(ASMARGS) boot.asm -o ../build/asm.o
	@#i686-elf-gcc -x c main.c -o ../build/kernel.o -c -C -std=gnu99 -nostdlib -ffreestanding -Wall -Wextra -ffreestanding -O2
	nasm $(ASMARGS) idt/idt.asm -o ../build/idt.o
	i686-elf-gcc $(COMPARGS) main.c -o ../build/kernel.o
	i686-elf-gcc -T linker.ld -o ../isodir/boot/yados.bin -ffreestanding -O2 -nostdlib ../build/asm.o ../build/idt.o ../build/kernel.o -lgcc
	grub-mkrescue -o ../yados.iso ../isodir

emu: ../yados.iso
	qemu-system-i386 -cdrom ../yados.iso
