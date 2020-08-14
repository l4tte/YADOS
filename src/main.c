/* main.c
 * YADOS Main C file
 * Contains functions to be used in other files as defined in system.h
 */

#include <stdint.h>
#include "gdt/gdt.c"
#include "idt/idt.c"
#include "idt/isrs.c"
#include "print/print.c"

/* Copy memory from src into dest */
unsigned char *memcpy(unsigned char *dest, const unsigned char *src, int count)
{
  for (int i=0; i < count; i++)
  {
    dest[i] = src[i];
  }
  return dest;
}

/* Set memory in dest to val */
unsigned char *memset(unsigned char *dest, unsigned char val, int count)
{
  for (int i=0; i < count; i++)
  {
    dest[i] = val;
  }
  return dest;
}

/* memset but unsigned short */
unsigned short *memsetw(unsigned short *dest, unsigned short val, int count)
{
  for (unsigned short i=0; i < count; i++)
  {
    dest[i] = val;
  }
  return dest;
}

/* Get length of str and return as int */
int strlen(const char *str)
{
  int count = 0;
  for (int i=0; str[i] != 0x00; i++)
  {
    count++;
  }
  return count;
}

/* Standard inportb asm function. Get input of an IO port */
unsigned char inportb (unsigned short _port)
{
    unsigned char rv;
    __asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "dN" (_port));
    return rv;
}

/* Write to IO ports and send bytes to device */
void outportb (unsigned short _port, unsigned char _data)
{
    __asm__ __volatile__ ("outb %1, %0" : : "dN" (_port), "a" (_data));
}

char *strcat(char *dest, const char *src)
{
  char *rdest = dest;

  while (*dest)
    dest++;
  while (*dest++ = *src++);
  return rdest;
}

/* Returns base to the power of power */
int pow(int base, int power)
{
  for (int i = 1; i < power; i++)
  {
    base = base * base;
  }
  return base;
}

/* print a green checkmark with message if check is 0,
 * print a grey dot with message if check is 1
 * Otherwise print a red X
 * Used for console output */
void check(char* msg, int checkmark)
{
  int col = gettextcolor();
  puts("[ ");
  if (checkmark == 0)
  {
    settextcolor(0x0a, 0x00);
    puts("-");
  } else if (checkmark == 1) {
    settextcolor(0x08, 0x00);
    puts(".");
  } else {
    settextcolor(0x0c, 0x00);
    puts("x");
  }
  setrawtextcol(col);
  puts(" ]   ");
  puts(msg);
}

int kmain()
{
  gdt_install();
  init_video();
  check("Booting YADOS...\n", 1);
  {
    char* gdtloc;
    itoa(&gdt, gdtloc, 16);
    check(strcat("GDT loaded at 0x", gdtloc) , 0);
  }  

  // Loop forever
  for(;;);
}
