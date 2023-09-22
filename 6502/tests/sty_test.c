#include "test.h"

#include "6502/cpu.h"
#include "6502/memory.h"

void sty_zeropage() {
    int cycles;
    cpu_t cpu;
    memory_t memory;
    init_memory(&memory);
    reset(&cpu, &memory);
    cpu.program_counter = 0x0000;
    memory.data[0] = STY_ZPG;
    memory.data[1] = 0xF0;
    cpu.y_register = 0x37;
    START_TESTCASE("sty_zeropage");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 3);
    ASSERT(memory.data[0xF0] == (byte)0x37);
    END_TESTCASE();
}

void sty_zeropage_x() {
    int cycles;
    cpu_t cpu;
    memory_t memory;
    init_memory(&memory);
    reset(&cpu, &memory);
    cpu.program_counter = 0x0000;
    memory.data[0] = STY_ZPG_X;
    memory.data[1] = 0xF0;
    cpu.y_register = 0x37;
    cpu.x_register = 0x05;
    START_TESTCASE("sty_zeropage_x");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 4);
    ASSERT(memory.data[0xF5] == (byte)0x37);
    END_TESTCASE();

    cpu.program_counter = 0x0000;
    cpu.x_register = 0x20;
    START_TESTCASE("sty_zeropage_x wrap");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 4);
    ASSERT(memory.data[0x10] == (byte)0x37);
    END_TESTCASE();
}

void sty_absolute() {
    int cycles;
    cpu_t cpu;
    memory_t memory;
    init_memory(&memory);
    reset(&cpu, &memory);
    cpu.program_counter = 0x0000;
    memory.data[0] = STY_ABS;
    memory.data[1] = 0x40;
    memory.data[2] = 0x30;
    cpu.y_register = 0x37;
    START_TESTCASE("sty_absolute");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 4);
    ASSERT(memory.data[0x3040] == (byte)0x37);
    END_TESTCASE();
}

int main() {
    INIT_TESTS();
    sty_zeropage();
    sty_zeropage_x();
    sty_absolute();
    END_TESTS();
}