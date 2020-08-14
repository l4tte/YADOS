; Interrupts:
; 0        	Division By Zero Exception
; 1        	Debug Exception
; 2 	      Non Maskable Interrupt Exception
; 3        	Breakpoint Exception
; 4        	Into Detected Overflow Exception
; 5        	Out of Bounds Exception
; 6         Invalid Opcode Exception
; 7 	      No Coprocessor Exception
; 8        	Double Fault Exception
; 9 	      Coprocessor Segment Overrun Exception
; 10 	      Bad TSS Exception
; 11 	      Segment Not Present Exception
; 12 	      Stack Fault Exception
; 13 	      General Protection Fault Exception
; 14 	      Page Fault Exception
; 15        Unknown Interrupt Exception
; 16       	Coprocessor Fault Exception
; 17       	Alignment Check Exception (486+)
; 18        Machine Check Exception (Pentium/586+)
; 19 to 31 	Reserved Exceptions

; Make all of the registers global
[GLOBAL isr0 ]
[GLOBAL isr1 ]
[GLOBAL isr2 ]
[GLOBAL isr3 ]
[GLOBAL isr4 ]
[GLOBAL isr5 ]
[GLOBAL isr6 ]
[GLOBAL isr7 ]
[GLOBAL isr8 ]
[GLOBAL isr9 ]
[GLOBAL isr10]
[GLOBAL isr11]
[GLOBAL isr12]
[GLOBAL isr13]
[GLOBAL isr14]
[GLOBAL isr15]
[GLOBAL isr16]
[GLOBAL isr17]
[GLOBAL isr18]
[GLOBAL isr19]
[GLOBAL isr20]
[GLOBAL isr21]
[GLOBAL isr22]
[GLOBAL isr23]
[GLOBAL isr24]
[GLOBAL isr25]
[GLOBAL isr26]
[GLOBAL isr27]
[GLOBAL isr28]
[GLOBAL isr29]
[GLOBAL isr30]
[GLOBAL isr31]

; Divide by zero exception
isr0:
  cli         ; stop more interrupts from being raised
  push byte 0 ; pops a dummy error code to keep a uniform stack frame
  push byte 0
  jmp isr_common_stub

; Debug exception
isr1:
  cli
  push byte 0
  push byte 1
  jmp isr_common_stub
isr2:
  cli
  push byte 0
  push byte 2
  jmp isr_common_stub
isr3:
  cli
  push byte 0
  push byte 3
  jmp isr_common_stub
isr4:
  cli
  push byte 0
  push byte 4
  jmp isr_common_stub
isr5:
  cli
  push byte 0
  push byte 5
  jmp isr_common_stub
isr6:
  cli
  push byte 0
  push byte 6
  jmp isr_common_stub
isr7:
  cli
  push byte 0
  push byte 7
  jmp isr_common_stub
; Double fault exception
isr8:
  cli
  push byte 8 ; Dont push a 0 value onto the stack
              ; Double fault exception pushes one automatically
  jmp isr_common_stub
isr9:
  cli
  push byte 0
  push byte 9
  jmp isr_common_stub
isr10:
  cli
  push byte 10 
  jmp isr_common_stub
isr11:
  cli
  push byte 11
  jmp isr_common_stub
isr12:
  cli
  push byte 12
  jmp isr_common_stub
isr13:
  cli
  push byte 13
  jmp isr_common_stub
isr14:
  cli
  push byte 14
  jmp isr_common_stub
isr15:
  cli
  push byte 0
  push byte 15
  jmp isr_common_stub
isr16:
  cli
  push byte 0
  push byte 16
  jmp isr_common_stub
isr17:
  cli
  push byte 0
  push byte 17
  jmp isr_common_stub
isr18:
  cli
  push byte 0
  push byte 18
  jmp isr_common_stub
isr19:
  cli
  push byte 0
  push byte 19
  jmp isr_common_stub
isr20:
  cli
  push byte 0
  push byte 20
  jmp isr_common_stub
isr21:
  cli
  push byte 0
  push byte 21
  jmp isr_common_stub
isr22:
  cli
  push byte 0
  push byte 22
  jmp isr_common_stub
isr23:
  cli
  push byte 0
  push byte 23
  jmp isr_common_stub
isr24:
  cli
  push byte 0
  push byte 24
  jmp isr_common_stub
isr25:
  cli
  push byte 0
  push byte 25
  jmp isr_common_stub
isr26:
  cli
  push byte 0
  push byte 26
  jmp isr_common_stub
isr27:
  cli
  push byte 0
  push byte 27
  jmp isr_common_stub
isr28:
  cli
  push byte 0
  push byte 28
  jmp isr_common_stub
isr29:
  cli
  push byte 0
  push byte 29
  jmp isr_common_stub
isr30:
  cli
  push byte 0
  push byte 30
  jmp isr_common_stub
isr31:
  cli
  push byte 0
  push byte 31
  jmp isr_common_stub

extern fault_handler ; defined in c

; save the processor state, set
; up for kernel mode segments, call the C-level fault handler,
; and then restores the stack frame
isr_common_stub:
    pusha
    push ds
    push es
    push fs
    push gs
    mov ax, 0x10   ; Load the Kernel Data Segment descriptor
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov eax, esp   ; Push us the stack
    push eax
    mov eax, fault_handler
    call eax       ; preserves the 'eip' register
    pop eax
    pop gs
    pop fs
    pop es
    pop ds
    popa
    add esp, 8     ; Cleans up the pushed error code and pushed ISR number
    iret           ; pops 5 things at once: CS, EIP, EFLAGS, SS, and ESP
