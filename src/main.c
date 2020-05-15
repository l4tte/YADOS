#include "utils/colors.h"

int cx = 0;
int cy = 0;
int cwidth = 80;

void write_newline()
{
  cy++;
  cx = 0;
}

void write_string( int color, const char *string )
{
    volatile char *video = (volatile char*)(0xB8000 | ( cx + (cy * cwidth) * 2 ));

    *video = *video | (cx * 2);
    while( *string != 0 )
    {
        *video++ = *string++;
        *video++ = color;
        cx++;
    }
}

char* itoa(int val, int base){
  if (val == 0) {
    return ("0");
  }
	static char buf[32] = {0};
	int i = 30;
	for(; val && i ; --i, val /= base)
		buf[i] = "0123456789abcdef"[val % base];
	return &buf[i+1];
}

void clear()
{
  int y = 25;
  int x = 80;
  volatile char *video = (volatile char*)0xB8000;
  for (int i = 0; i < y; i++)
  {
    for (int j = 0; j < x; j++)
    {
      *video++ = ' ';
      *video++ = 0x00;
    }
  }
}

void kmain()
{
  clear();
  write_string(COL_WHITE, "Yados v0.5.0");
  write_newline();
  write_string(COL_GREY, "TEST");
  return;
}
