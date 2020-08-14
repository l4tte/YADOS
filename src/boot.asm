; Constants for multiboot header
MBALIGN  equ  1 << 0
MEMINFO  equ  1 << 1
FLAGS    equ  MBALIGN | MEMINFO
MAGIC    equ  0x1BADB002
CHECKSUM equ -(MAGIC + FLAGS)

[GLOBAL start]
[GLOBAL gdt_flush]
[EXTERN kmain]

section .multiboot
  align 4
    dd MAGIC
    dd FLAGS
    dd CHECKSUM

section .text
jmp start
gdt_flush:
  extern gp         ; Will be defined in C file
                    ; GDT Pointer
  lgdt [gp]
  mov ax, 0x10      ; 0x10 is the offset in the GDT to our data segment
  mov ds, ax
  mov es, ax
  mov fs, ax
  mov gs, ax
  mov ss, ax
start:
  extern kmain
  call kmain
.hang:
  hlt
  jmp .hang

SECTION .bss
    resb 8192               ; This reserves 8KBytes of memory here
_sys_stack:
