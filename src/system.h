#ifndef SYSTEM_H_
#define SYSTEM_H_

/* Defined in main.c */
extern unsigned char  *memcpy  (unsigned char *dest, const unsigned char *src, int count);
extern unsigned char  *memset  (unsigned char *dest, unsigned char val, int count);
extern unsigned short *memsetw (unsigned short *dest, unsigned short val, int count);
extern          char  *strcat  (char *dest, const char *src);
extern          int   strlen   (const char *str);
extern          int   pow      (int base, int power);
extern unsigned char  inportb  (unsigned short _port);
extern          void  outportb (unsigned short _port, unsigned char _data);

#endif
