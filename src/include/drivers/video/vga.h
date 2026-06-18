#ifndef DRIVERS_VIDEO_VGA_H_
#define DRIVERS_VIDEO_VGA_H_

void puts_vga(const char *string);
void puts_vga_color(const char *string, const unsigned char attrbyte);
void putc_vga(const char c);
void putc_vga_color(const char c, const unsigned char attrbyte);
void backspace();
void clearscreen();
void newline();

#endif // DRIVERS_VIDEO_VGA_H_

