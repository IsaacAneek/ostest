#include <stdarg.h>
#include "include/drivers/video/vga.h"
#include "include/drivers/interrupt/interrupt.h"
#include "include/drivers/pic8259/pic8259.h"
#include "include/inlineasm/inlineasm.h"
#include "include/drivers/keyboard/keyboard.h"
#include "include/drivers/stdio/stdio.h"
#include "include/drivers/hdd/hdd.h"

extern int cursor;



void main()
{
    idt_init();
    PIC_init();
    keyboard_init();
    init_ATA_HDD();
    // putc_vga('b');
    //asm volatile("int $0x30");
    //kprintf("Hello world for %c %d times from myOS", 'e', 123);
    asm volatile("sti");

    uint16_t buffer[256] = {'a'};
    read_sectors_LBA(19, 1, buffer);
    for(int i = 0; i < 256; i++) {
        putc_vga(buffer[i]);
        putc_vga(buffer[i] >> 8);
    }

    while (1)
    {

    };
}