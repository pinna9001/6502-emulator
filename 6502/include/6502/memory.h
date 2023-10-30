#ifndef RAM_H
#define RAM_H

#include <stdbool.h>

#include "6502/common.h"

typedef struct memory_t {
    byte data[0x10000];
} memory_t;

void init_memory(memory_t* memory);
bool load_memory(memory_t* memory, char* filepath, word start_address);
byte read_memory(memory_t* memory, word address);
void write_memory(memory_t* memory, word address, byte value);
void print_memory(memory_t* memory, word start_address, word end_address);

#endif  // RAM_H