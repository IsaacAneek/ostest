#include "drivers/video/vga.h"

#define COL 80
#define ROW 25

int cursor = 0;
volatile unsigned char *video_mem = (volatile unsigned char *)0xb8000;
unsigned char attr_byte = 0x0F;

void newline() {
    int current_col = cursor / COL;
    cursor = (current_col + 1) * COL;
}

void clearscreen() {
    int counter = 0;
    for(int i = 0; i < COL; i++) {
        for(int j = 0; j < ROW; j++) {
            video_mem[counter++] = ' ';
            video_mem[counter++] = attr_byte;
        }
    }
    cursor = 0;
}

void backspace() {
    cursor--;
    video_mem[cursor * 2] = ' ';
    video_mem[cursor * 2 + 1] = attr_byte;
}

void puts_vga(const char *string)
{
    for (int x = 0; string[x] != '\0'; x++)
    {
        putc_vga(string[x]);
    }
}

void puts_vga_color(const char *string, const unsigned char attrbyte)
{
    for (int x = 0; string[x] != '\0'; x++)
    {
        putc_vga_color(string[x], attrbyte);
    }
}

void putc_vga(const char c)
{
    if(c == '\n') {
        newline();
        return;
    }
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
