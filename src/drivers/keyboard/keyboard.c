#include "drivers/keyboard/keyboard.h"
#include "drivers/interrupt/interrupt.h"
#include "inlineasm/inlineasm.h"
#include "drivers/video/vga.h"

volatile unsigned int ScanCode = 0;
extern void isr_keyb_wrapper();

#define BACKSPACE 0x0E
#define ENTER 0x1C

static char key_buffer[256];

#define SC_MAX 57
const char sc_ascii[] = { '?', '?', '1', '2', '3', '4', '5', '6',     
    '7', '8', '9', '0', '-', '=', '?', '?', 'Q', 'W', 'E', 'R', 'T', 'Y', 
        'U', 'I', 'O', 'P', '[', ']', '\n', '?', 'A', 'S', 'D', 'F', 'G', 
        'H', 'J', 'K', 'L', ';', '\'', '`', '?', '\\', 'Z', 'X', 'C', 'V', 
        'B', 'N', 'M', ',', '.', '/', '?', '?', '?', ' '};


void ISR_keyboard_handler_01()
{
    unsigned char key;
    outb(0x20, 0x20); // Send EOI

    //PS/2 controller sends scan code bytes into port 0x60
    unsigned char scancode = inb(0x60);
    
    if (scancode > SC_MAX) return;
    if (scancode == BACKSPACE) {
        //backspace(key_buffer);
        //kprint_backspace();
        backspace();
    } else if (scancode == ENTER) {
        putc_vga('\n');
        // user_input(key_buffer); /* kernel-controlled function */
        // key_buffer[0] = '\0';
    } else {
        char letter = sc_ascii[(int)scancode];
        /* Remember that kprint only accepts char[] */
        putc_vga(letter);
    }

}

void keyboard_init()
{
    idt_set_gate(0x21, (unsigned int)isr_keyb_wrapper, 0x08, 0x8E);
}