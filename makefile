compile: src/boot.asm
	@# nasm -felf32 src/main.asm -o build/asm.o
	@# i686-elf-gcc -x c src/main.c -o build/kernel.o -c -C -std=gnu99 -nostdlib -ffreestanding -Wall -Wextra -ffreestanding -O2
	@# i686-elf-gcc -T linker.ld -o isodir/boot/yados.bin -ffreestanding -O2 -nostdlib build/asm.o build/kernel.o -lgcc
	@# grub-mkrescue -o yados.iso isodir
	nasm src/boot.asm -f bin -o build/boot.bin


emu: build/
	qemu-system-i386 -hda build/boot.bin

clean: build/
	rm -rf build/*
