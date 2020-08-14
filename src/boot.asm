; Constants for multiboot header
MBALIGN  equ  1 << 0
MEMINFO  equ  1 << 1
FLAGS    equ  MBALIGN | MEMINFO
MAGIC    equ  0x1BADB002
CHECKSUM equ -(MAGIC + FLAGS)

[GLOBAL start]
[GLOBAL gdt_flush]
[GLOBAL idt_load]
[EXTERN kmain]

section .text

align 4
  dd MAGIC
  dd FLAGS
  dd CHECKSUM


jmp start
idt_load:
  extern idtp
  lidt [idtp]
  ret

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
  ret
start:
  mov esp, stack
  extern kmain
  call kmain
  ; If kmain returns, then it crashed
  extern puts
  push crash
  call puts
.hang:
  hlt
  jmp .hang

crash: db "Kernel has crashed. Halting...", 0x0

SECTION .bss
    resb 8192               ; This reserves 8KBytes of memory here
stack:
