; Loads the IDT defined in '_idtp' into the processor.
; This is declared in C as 'extern void idt_load();'
global idt_load
extern idtp
extern ISR_keyboard_handler_01
idt_load:
    lidt [idtp]
    ret

global isr0
global isr_keyb_wrapper

extern putc_vga

isr0:
    pusha

    push dword 'a'
    call putc_vga

    add esp, 4

    popa
    iret

isr_keyb_wrapper:
    pusha
    call ISR_keyboard_handler_01
    popa
    iret