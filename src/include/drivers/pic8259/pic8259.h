#ifndef DRIVERS_PIC8259_PIC8259_H_
#define DRIVERS_PIC8259_PIC8259_H_
#include <stdint.h>

void PIC_remap(int offset1, int offset2);
void PIC_init();
void PIC_sendEOI(uint8_t irq);


#endif // DRIVERS_PIC8259_PIC8259_H_