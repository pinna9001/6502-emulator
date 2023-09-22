#include <stdio.h>
#include <stdlib.h>

#include "6502/common.h"
#include "6502/cpu.h"
#include "6502/memory.h"

int main() {
    cpu_t cpu;
    memory_t memory;
    init_memory(&memory);
    reset(&cpu, &memory);
    cpu.accumulator = 0x11;
    memory.data[0] = STA_IND_Y;
    memory.data[1] = 0x70;
    memory.data[2] = 0x31;
    memory.data[0x0070] = 0xF3;
    memory.data[0x0071] = 0x34;
    memory.data[0x3553] = 0x23;
    cpu.y_register = 0x060;
    int cycles = process_instruction(&cpu);
    printf("Akkumulator: %x\n", cpu.accumulator);
    printf("Status: %x\n", cpu.status);
    printf("Cycles: %d\n", cycles);
    print_memory(&memory, 0x3550, 0x20);
    return 0;
}