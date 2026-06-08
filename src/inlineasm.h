#ifndef INLINEASM_H_
#define INLINEASM_H_
#include <stdint.h>

static inline void outb(uint16_t port, uint8_t val);
static inline uint8_t inb(uint16_t port);
static inline void lidt(void* base, uint16_t size);

#endif // INLINEASM_H_