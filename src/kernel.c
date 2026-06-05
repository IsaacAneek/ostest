#include <stdarg.h>
#include "include/drivers/video/vga.h"

void kprintf(char *format, ...)
{
    char *traverse;
    int a;

    va_list arg;
    va_start(arg, format);

    char token[256];
    int i = 0;

    while(*format) {
        if(*format == '%') {
            format++;
            switch(*format) {
                case 'c':
                    a = va_arg(arg, int);
                    token[i++] = a;
                    break;
                case 'd':
                    a = va_arg(arg, int);
                    int tmp_num = a;
                    int tmp_digit = 1;
                    while(tmp_num > 0) {
                        tmp_num /= 10;
                        tmp_digit *= 10;
                    }

                    tmp_digit /= 10;

                    while(tmp_digit > 0) {
                        int msb = a / tmp_digit;
                        a = a - (msb * tmp_digit);
                        tmp_digit /= 10;
                        token[i++] = msb + '0';
                    }

                    break;
            }
        }
        else {
            token[i++] = *format;
        }
        format++;
    }

    va_end(arg);

    token[i] = '\0';
    puts_vga(token);
}

void main()
{
    kprintf("Hello world for %c %d times from myOS", 'e', 123);
    return;
}