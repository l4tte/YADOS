/* main.c
 * YADOS Main C file
 * Contains functions to be used in other files as defined in system.h
 */

#include <stdint.h>
#include "gdt/gdt.c"
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


int kmain()
{
  //gdt_install();
  init_video();
  puts("YADOS Version 0.0.1");
  // Loop forever
  for(;;);
}
