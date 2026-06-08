#include <stdarg.h>
#include "include/drivers/video/vga.h"
#include "include/drivers/interrupt/interrupt.h"
#include "include/drivers/pic8259/pic8259.h"
#include "include/inlineasm/inlineasm.h"

extern int cursor;

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

volatile unsigned int ScanCode = 0;

void ISR_keyboard_handler_01() {
    unsigned char key;
    outb(0x20, 0x20);   // Send EOI
    ScanCode = inb(0x60);
}

void main()
{
    idt_init();
    asm volatile("int $0x30");
    idt_set_gate(0x21, (unsigned int)ISR_keyboard_handler_01, 0x08, 0x8E);
    // kernel keeps restarting if called idt_init()
    // check it
    // putc_vga('b');
    PIC_init();
    // kprintf("Hello world for %c %d times from myOS", 'e', 123);
    asm volatile("sti");

    // only prints 'D' if key pressed once but never works after
    // prolly problem with Interrupt masking and
    // slave PIC cascade identity
    // see line:49 pic8259.c
    while(1)
    {
        if(ScanCode)
        {
            if(ScanCode)
            {
                putc_vga('D');
                ScanCode = 0;
            }
        }

    };
}