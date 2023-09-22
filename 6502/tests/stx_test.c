#include "test.h"

#include "6502/cpu.h"
#include "6502/memory.h"

void stx_zeropage() {
    int cycles;
    cpu_t cpu;
    memory_t memory;
    init_memory(&memory);
    reset(&cpu, &memory);
    cpu.program_counter = 0x0000;
    memory.data[0] = STX_ZPG;
    memory.data[1] = 0xF0;
    cpu.x_register = 0x37;
    START_TESTCASE("stx_zeropage");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 3);
    ASSERT(memory.data[0xF0] == (byte)0x37);
    END_TESTCASE();
}

void stx_zeropage_y() {
    int cycles;
    cpu_t cpu;
    memory_t memory;
    init_memory(&memory);
    reset(&cpu, &memory);
    cpu.program_counter = 0x0000;
    memory.data[0] = STX_ZPG_Y;
    memory.data[1] = 0xF0;
    cpu.x_register = 0x37;
    cpu.y_register = 0x05;
    START_TESTCASE("stx_zeropage_y");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 4);
    ASSERT(memory.data[0xF5] == (byte)0x37);
    END_TESTCASE();

    cpu.program_counter = 0x0000;
    cpu.y_register = 0x20;
    START_TESTCASE("stx_zeropage_y wrap");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 4);
    ASSERT(memory.data[0x10] == (byte)0x37);
    END_TESTCASE();
}

void stx_absolute() {
    int cycles;
    cpu_t cpu;
    memory_t memory;
    init_memory(&memory);
    reset(&cpu, &memory);
    cpu.program_counter = 0x0000;
    memory.data[0] = STX_ABS;
    memory.data[1] = 0x40;
    memory.data[2] = 0x30;
    cpu.x_register = 0x37;
    START_TESTCASE("stx_absolute");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 4);
    ASSERT(memory.data[0x3040] == (byte)0x37);
    END_TESTCASE();
}

int main() {
    INIT_TESTS();
    stx_zeropage();
    stx_zeropage_y();
    stx_absolute();
    END_TESTS();
}