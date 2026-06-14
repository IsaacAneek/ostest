#include "drivers/keyboard/keyboard.h"
#include "drivers/interrupt/interrupt.h"
#include "inlineasm/inlineasm.h"

volatile unsigned int ScanCode = 0;
extern void isr_keyb_wrapper();

void ISR_keyboard_handler_01()
{
    unsigned char key;
    outb(0x20, 0x20); // Send EOI
    ScanCode = inb(0x60);
    //asm volatile("iret");
}

void keyboard_init()
{
    idt_set_gate(0x21, (unsigned int)isr_keyb_wrapper, 0x08, 0x8E);
}