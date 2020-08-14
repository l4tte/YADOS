/* ISRS.C
 * contains interrupt handlers
 * will be called from asm 
 */

#include "../system.h"
extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

void isrs_install()
{
  idt_set_gate(0, (unsigned)isr0, 0x08, 0x8e);
  idt_set_gate(1, (unsigned)isr1, 0x08, 0x8e);
  idt_set_gate(2, (unsigned)isr2, 0x08, 0x8e);
  idt_set_gate(3, (unsigned)isr3, 0x08, 0x8e);
  idt_set_gate(4, (unsigned)isr4, 0x08, 0x8e);
  idt_set_gate(5, (unsigned)isr5, 0x08, 0x8e);
  idt_set_gate(6, (unsigned)isr6, 0x08, 0x8e);
  idt_set_gate(7, (unsigned)isr7, 0x08, 0x8e);
  idt_set_gate(8, (unsigned)isr8, 0x08, 0x8e);
  idt_set_gate(9, (unsigned)isr9, 0x08, 0x8e);
  idt_set_gate(10, (unsigned)isr10, 0x08, 0x8e);
  idt_set_gate(11, (unsigned)isr11, 0x08, 0x8e);
  idt_set_gate(12, (unsigned)isr12, 0x08, 0x8e);
  idt_set_gate(13, (unsigned)isr13, 0x08, 0x8e);
  idt_set_gate(14, (unsigned)isr14, 0x08, 0x8e);
  idt_set_gate(15, (unsigned)isr15, 0x08, 0x8e);
  idt_set_gate(16, (unsigned)isr16, 0x08, 0x8e);
  idt_set_gate(17, (unsigned)isr17, 0x08, 0x8e);
  idt_set_gate(18, (unsigned)isr18, 0x08, 0x8e);
  idt_set_gate(19, (unsigned)isr19, 0x08, 0x8e);
  idt_set_gate(20, (unsigned)isr20, 0x08, 0x8e);
  idt_set_gate(21, (unsigned)isr21, 0x08, 0x8e);
  idt_set_gate(22, (unsigned)isr22, 0x08, 0x8e);
  idt_set_gate(23, (unsigned)isr23, 0x08, 0x8e);
  idt_set_gate(24, (unsigned)isr24, 0x08, 0x8e);
  idt_set_gate(25, (unsigned)isr25, 0x08, 0x8e);
  idt_set_gate(26, (unsigned)isr26, 0x08, 0x8e);
  idt_set_gate(27, (unsigned)isr27, 0x08, 0x8e);
  idt_set_gate(28, (unsigned)isr28, 0x08, 0x8e);
  idt_set_gate(29, (unsigned)isr29, 0x08, 0x8e);
  idt_set_gate(30, (unsigned)isr30, 0x08, 0x8e);
  idt_set_gate(31, (unsigned)isr31, 0x08, 0x8e);
}

unsigned char *exception_messages[] =
{
  "Division By Zero",
  "Debug",
  "Non Maskable Interrupt",
  "Breakpoint Exception",
  "Into Detected Overflow Exception",
  "Out of Bounds Exception",
  "Invalid Opcode Exception",
  "No Coprocessor Exception",
  "Double Fault Exception",
  "Coporcessor Segment Overrun Exception",
  "Bad TSS Exception",
  "Segment Not Present Exception",
  "Stack Fault Exception",
  "General Protection Fault Exception",
  "Page Fault Exception",
  "Unknown Interrupt Exception",
  "Coprocessor Fault Exception",
  "Alignment Check Exception (486+)",
  "Machine Check Exception (Pentium/586+)",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
};

/* This defines what the stack looks like after an ISR was running */
struct regs
{
  unsigned int gs, fs, es, ds;      /* pushed the segs last */
  unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;  /* pushed by 'pusha' */
  unsigned int int_no, err_code;    /* our 'push byte #' and ecodes do this */
  unsigned int eip, cs, eflags, useresp, ss;   /* pushed by the processor automatically */
};

void fault_handler(struct regs *r)
{
  /* Is this a fault whose number is from 0 to 31? */
  if (r->int_no < 32)
  {
      /* Display the description for the Exception that occurred, then halt */
      puts(exception_messages[r->int_no]);
      puts(" Exception. System Halted!\n");
      for (;;);
  }
}
