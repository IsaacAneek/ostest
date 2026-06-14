#include <stdarg.h>
#include "include/drivers/video/vga.h"
#include "include/drivers/interrupt/interrupt.h"
#include "include/drivers/pic8259/pic8259.h"
#include "include/inlineasm/inlineasm.h"
#include "include/drivers/keyboard/keyboard.h"
#include "include/drivers/stdio/stdio.h"

extern int cursor;
extern int ScanCode;



void main()
{
    idt_init();
    keyboard_init();
    PIC_init();
    // putc_vga('b');
    //asm volatile("int $0x30");
    kprintf("Hello world for %c %d times from myOS", 'e', 123);
    asm volatile("sti");

    // test keyboard
    while (1)
    {
        if (ScanCode)
        {
            putc_vga('D');
            ScanCode = 0;
        }
    };
}