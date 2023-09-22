#include "6502/cpu.h"
#include "6502/memory.h"
#include "test.h"

void sta_zeropage() {
    int cycles;
    cpu_t cpu;
    memory_t memory;
    init_memory(&memory);
    reset(&cpu, &memory);
    cpu.program_counter = 0x0000;
    memory.data[0] = STA_ZPG;
    memory.data[1] = 0xFF;
    cpu.accumulator = 0x37;
    START_TESTCASE("sta_imm zeropage");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 3);
    ASSERT(memory.data[0xFF] == (byte)0x37);
    END_TESTCASE();
}

void sta_zeropage_x() {
    int cycles;
    cpu_t cpu;
    memory_t memory;
    init_memory(&memory);
    reset(&cpu, &memory);
    cpu.program_counter = 0x0000;
    memory.data[0] = STA_ZPG_X;
    memory.data[1] = 0xF0;
    cpu.accumulator = 0x37;
    cpu.x_register = 0x5;
    START_TESTCASE("sta_imm zeropage_x");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 4);
    ASSERT(memory.data[0xF5] == (byte)0x37);
    END_TESTCASE();

    cpu.program_counter = 0x0000;
    cpu.x_register = 0x50;
    START_TESTCASE("sta_imm zeropage_x wrap");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 4);
    ASSERT(memory.data[0x40] == (byte)0x37);
    END_TESTCASE();
}

void sta_absolute() {
    int cycles;
    cpu_t cpu;
    memory_t memory;
    init_memory(&memory);
    reset(&cpu, &memory);
    cpu.program_counter = 0x0000;
    memory.data[0] = STA_ABS;
    memory.data[1] = 0xF0;
    memory.data[2] = 0xE0;
    cpu.accumulator = 0x37;
    START_TESTCASE("sta_absolute");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 4);
    ASSERT(memory.data[0xE0F0] == (byte)0x37);
    END_TESTCASE();
}

void sta_absolute_x() {
    int cycles;
    cpu_t cpu;
    memory_t memory;
    init_memory(&memory);
    reset(&cpu, &memory);
    cpu.program_counter = 0x0000;
    memory.data[0] = STA_ABS_X;
    memory.data[1] = 0xF0;
    memory.data[2] = 0xE0;
    cpu.accumulator = 0x37;
    cpu.x_register = 0x5;
    START_TESTCASE("sta_absolute_x");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 5);
    ASSERT(memory.data[0xE0F5] == (byte)0x37);
    END_TESTCASE();

    cpu.program_counter = 0x0000;
    memory.data[1] = 0xF0;
    memory.data[2] = 0xE0;
    cpu.accumulator = 0x37;
    cpu.x_register = 0x10;
    START_TESTCASE("sta_absolute_x wrap");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 5);
    ASSERT(memory.data[0xE100] == (byte)0x37);
    END_TESTCASE();
}

void sta_absolute_y() {
    int cycles;
    cpu_t cpu;
    memory_t memory;
    init_memory(&memory);
    reset(&cpu, &memory);
    cpu.program_counter = 0x0000;
    memory.data[0] = STA_ABS_Y;
    memory.data[1] = 0xF0;
    memory.data[2] = 0xE0;
    cpu.accumulator = 0x37;
    cpu.y_register = 0x5;
    START_TESTCASE("sta_absolute_y");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 5);
    ASSERT(memory.data[0xE0F5] == (byte)0x37);
    END_TESTCASE();

    cpu.program_counter = 0x0000;
    memory.data[1] = 0xF0;
    memory.data[2] = 0xE0;
    cpu.accumulator = 0x37;
    cpu.y_register = 0x10;
    START_TESTCASE("sta_absolute_y wrap");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 5);
    ASSERT(memory.data[0xE100] == (byte)0x37);
    END_TESTCASE();
}

void sta_x_ind() {
    int cycles;
    cpu_t cpu;
    memory_t memory;
    init_memory(&memory);
    reset(&cpu, &memory);
    cpu.program_counter = 0x0000;
    memory.data[0] = STA_X_IND;
    memory.data[1] = 0xE0;
    memory.data[0xF0] = 0x30;
    memory.data[0xF1] = 0x40;
    cpu.accumulator = 0x37;
    cpu.x_register = 0x10;
    START_TESTCASE("sta_x_indirect");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 6);
    ASSERT(memory.data[0x4030] == (byte)0x37);
    END_TESTCASE();

    cpu.program_counter = 0x0000;
    memory.data[0] = STA_X_IND;
    memory.data[1] = 0xF0;
    memory.data[0x30] = 0x40;
    memory.data[0x31] = 0x30;
    cpu.accumulator = 0x37;
    cpu.x_register = 0x40;
    START_TESTCASE("sta_x_indirect wrap");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 6);
    ASSERT(memory.data[0x3040] == (byte)0x37);
    END_TESTCASE();
}

void sta_ind_y() {
    int cycles;
    cpu_t cpu;
    memory_t memory;
    init_memory(&memory);
    reset(&cpu, &memory);
    cpu.program_counter = 0x0000;
    memory.data[0] = STA_IND_Y;
    memory.data[1] = 0xF0;
    memory.data[0xF0] = 0x30;
    memory.data[0xF1] = 0x40;
    cpu.accumulator = 0x37;
    cpu.x_register = 0x10;
    START_TESTCASE("sta_indirect_y");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 6);
    ASSERT(memory.data[0x4040] == (byte)0x37);
    END_TESTCASE();

    cpu.program_counter = 0x0000;
    memory.data[0] = STA_IND_Y;
    memory.data[1] = 0xF0;
    memory.data[0xF0] = 0xF0;
    memory.data[0xF1] = 0x40;
    cpu.accumulator = 0x37;
    cpu.x_register = 0x10;
    START_TESTCASE("sta_indirect_y wrap");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 6);
    ASSERT(memory.data[0x4100] == (byte)0x37);
    END_TESTCASE();
}

int main() {
    INIT_TESTS();
    sta_zeropage();
    sta_zeropage_x();
    sta_absolute();
    sta_absolute_x();
    sta_absolute_y();
    sta_x_ind();
    sta_ind_y();
    END_TESTS();
}