; Loads the IDT defined in '_idtp' into the processor.
; This is declared in C as 'extern void idt_load();'
global idt_load
extern idtp
idt_load:
    lidt [idtp]
    ret

global isr0

extern putc_vga

isr0:
    pusha

    push dword 'a'
    call putc_vga

    add esp, 4

    popa
    iret

