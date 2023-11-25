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
    cpu.status |= CARRY_MASK;
    cpu.accumulator = 0x00;
    memory.data[0] = LDA_IMM;
    memory.data[1] = 0xFF;
    memory.data[2] = STA_ZPG;
    memory.data[3] = 0x33;
    int cycles = process_instruction(&cpu);
    cycles += process_instruction(&cpu);
    printf("Akkumulator: %x\n", cpu.accumulator);
    printf("Status: %x\n", cpu.status);
    printf("Cycles: %d\n", cycles);
    print_memory(&memory, 0x0, 0x100);
    return 0;
}