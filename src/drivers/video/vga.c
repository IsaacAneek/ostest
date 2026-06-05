#include "drivers/video/vga.h"

int cursor = 0;
volatile unsigned char *video_mem = (volatile unsigned char *)0xb8000;
unsigned char attr_byte = 0x0F;

void puts_vga(const char *string)
{
    for (int x = 0; string[x] != '\0'; x++)
    {
        video_mem[x * 2] = string[x];
        video_mem[x * 2 + 1] = attr_byte;
        cursor++;
    }
}

void puts_vga_color(const char *string, const unsigned char attrbyte)
{
    for (int x = 0; string[x] != '\0'; x++)
    {
        video_mem[x * 2] = string[x];
        video_mem[x * 2 + 1] = attrbyte;
        cursor++;
    }
}

void putc_vga(const char c)
{
    video_mem[cursor * 2] = c;
    video_mem[cursor * 2 + 1] = attr_byte;
    cursor++;
}

void putc_vga_color(const char c, const unsigned char attrbyte)
{
    video_mem[cursor * 2] = c;
    video_mem[cursor * 2 + 1] = attrbyte;
    cursor++;
}
