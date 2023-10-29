#include "6502/memory.h"

#include <stdbool.h>
#include <stdio.h>

void init_memory(memory_t* memory) {
    for (int i = 0; i < sizeof(memory->data); i++) {
        memory->data[i] = 0;
    }
}

long get_file_size(FILE* file) {
    fseek(file, 0L, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0L, SEEK_SET);
    return file_size;
}

bool load_memory(memory_t* memory, char* filepath, word start_address) {
    FILE* file = fopen(filepath, "rb");
    if (file == NULL) {
        char error_msg[300];
        sprintf(error_msg, "Couldn't open file %s", filepath);
        perror(error_msg);
        return false;
    }
    long file_size = get_file_size(file);
    size_t written = fread(&memory->data[start_address], sizeof(byte), file_size, file);
    fclose(file);
    if (written != file_size)
    {
        perror("Didn't read all the bytes from the file");
        return false;
    }
    return true;
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