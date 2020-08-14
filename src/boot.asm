; Yet Another Decent Bootloader
[BITS 16]

; Move data segement to 0x07c0 to load program at 0x07c0
    mov ax, 0x07C0
    mov ds, ax

    cli ; Disable interrupts

    jmp main

print:
   mov ah, 0x0E
   mov bh, 0
.loop:
   lodsb
   or al, al  ;zero=end of str
   jz .done    ;get out
   int 0x10
   jmp .loop
.done:
   ret

clear_screen:
  pusha
  mov ah, 0x00
  mov al, 0x03
  int 10h
  popa
  ret

; GDT STUFF
gdt:
.gdt_code:
  ; 8 byte long empty descriptor
  dq 0x00
  
  


main:
  call clear_screen
  mov si, msg
  call print
  jmp $


; Data
    msg db 'Starting boot sequence...', 0x0a, 0x0D, 0

; End sig
    times 510-($-$$) db 0
    db 0x55
    db 0xAA
