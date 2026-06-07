#ifndef DRIVERS_INTERRUPT_INTERRUPT_H_
#define DRIVERS_INTERRUPT_INTERRUPT_H_

extern void idt_load();
void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags);
void idt_init();

#endif // DRIVERS_INTERRUPT_INTERRUPT_H_