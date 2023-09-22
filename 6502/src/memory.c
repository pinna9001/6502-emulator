#include "6502/memory.h"

#include <stdio.h>

void init_memory(memory_t* memory) {
    for (int i = 0; i < sizeof(memory->data); i++) {
        memory->data[i] = 0;
    }
}

byte read_memory(memory_t* memory, word address) {
    return memory->data[address];
}

void write_memory(memory_t* memory, word address, byte value) {
    memory->data[address] = value;
}

// TODO use end address instead of number_of_bytes
void print_memory(memory_t* memory, word start_address, word number_of_bytes) {
    int prefix = start_address % 16;
    int postfix = (16 - (start_address + number_of_bytes) % 16) % 16;
    int number_of_rows = (number_of_bytes + prefix + postfix) / 16;
    start_address = start_address - prefix;
    for (int i = 0; i < number_of_rows; i++) {
        word row_address = start_address + i * 16;
        printf("0x%04x\t", row_address);
        for (int j = 0; j < 16; j++) {
            printf("0x%02x ", memory->data[row_address + j]);
        }
        printf("\n");
    }
}