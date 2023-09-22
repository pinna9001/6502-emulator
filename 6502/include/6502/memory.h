#ifndef RAM_H
#define RAM_H

#include "6502/common.h"

typedef enum memory_type_t {
    MEMORY_RAM,
    MEMORY_ROM,
} memory_type_t;

typedef struct memory_t {
    byte data[0x10000];
} memory_t;

void init_memory(memory_t* memory);
// TODO load memory
void load_memory(memory_t* memory, char* filepath, word start_address);
byte read_memory(memory_t* memory, word address);
void write_memory(memory_t* memory, word address, byte value);
void print_memory(memory_t* memory, word start_address, word number_of_bytes);

#endif  // RAM_H