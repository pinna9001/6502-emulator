#include "6502/cpu.h"
#include "6502/memory.h"
#include "test.h"

void inc_zeropage() {
    int cycles;
    cpu_t cpu;
    memory_t memory;
    init_memory(&memory);
    reset(&cpu, &memory);
    cpu.program_counter = 0x0000;
    memory.data[0] = INC_ZPG;
    memory.data[1] = 0x12;
    memory.data[0x12] = 0xFE;
    START_TESTCASE("increment_zeropage negative");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 5);
    ASSERT(get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(!get_status_flag(&cpu, ZERO_MASK));
    ASSERT(memory.data[0x12] == (byte)0xFF);
    END_TESTCASE();

    cpu.program_counter = 0x0000;
    memory.data[0x12] = 0xFF;
    START_TESTCASE("increment_zeropage zero");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 5);
    ASSERT(!get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(get_status_flag(&cpu, ZERO_MASK));
    ASSERT(memory.data[0x12] == (byte)0x00);
    END_TESTCASE();

    cpu.program_counter = 0x0000;
    memory.data[0x12] = 0x0E;
    START_TESTCASE("increment_zeropage positive");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 5);
    ASSERT(!get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(!get_status_flag(&cpu, ZERO_MASK));
    ASSERT(memory.data[0x12] == (byte)0x0F);
    END_TESTCASE();
}

void inc_zeropage_x() {
    int cycles;
    cpu_t cpu;
    memory_t memory;
    init_memory(&memory);
    reset(&cpu, &memory);
    cpu.program_counter = 0x0000;
    memory.data[0] = INC_ZPG_X;
    memory.data[1] = 0x10;
    memory.data[0x12] = 0xFE;
    cpu.x_register = 0x2;
    START_TESTCASE("inc_zeropage_x negative");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 6);
    ASSERT(get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(!get_status_flag(&cpu, ZERO_MASK));
    ASSERT(memory.data[0x12] == (byte)0xFF);
    END_TESTCASE();

    cpu.program_counter = 0x0000;
    memory.data[0x12] = 0xFF;
    START_TESTCASE("inc_zeropage_x zero");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 6);
    ASSERT(!get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(get_status_flag(&cpu, ZERO_MASK));
    ASSERT(memory.data[0x12] == (byte)0x00);
    END_TESTCASE();

    cpu.program_counter = 0x0000;
    memory.data[0x12] = 0x11;
    START_TESTCASE("inc_zeropage_x positive");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 6);
    ASSERT(!get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(!get_status_flag(&cpu, ZERO_MASK));
    ASSERT(memory.data[0x12] == (byte)0x12);
    END_TESTCASE();

    cpu.program_counter = 0x0000;
    memory.data[1] = 0xF0;
    memory.data[0x10] = 0xFE;
    cpu.x_register = 0x20;
    START_TESTCASE("inc_zeropage_x wrap");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 6);
    ASSERT(get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(!get_status_flag(&cpu, ZERO_MASK));
    ASSERT(memory.data[0x10] == (byte)0xFF);
    END_TESTCASE();
}

void inc_absolute() {
    int cycles;
    cpu_t cpu;
    memory_t memory;
    init_memory(&memory);
    reset(&cpu, &memory);
    cpu.program_counter = 0x0000;
    memory.data[0] = INC_ABS;
    memory.data[1] = 0x12;
    memory.data[2] = 0x23;
    memory.data[0x2312] = 0xFE;
    START_TESTCASE("increment_absolute negative");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 6);
    ASSERT(get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(!get_status_flag(&cpu, ZERO_MASK));
    ASSERT(memory.data[0x2312] == (byte)0xFF);
    END_TESTCASE();

    cpu.program_counter = 0x0000;
    memory.data[0x2312] = 0xFF;
    START_TESTCASE("increment_absolute zero");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 6);
    ASSERT(!get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(get_status_flag(&cpu, ZERO_MASK));
    ASSERT(memory.data[0x2312] == (byte)0x00);
    END_TESTCASE();

    cpu.program_counter = 0x0000;
    memory.data[0x2312] = 0x0E;
    START_TESTCASE("increment_absolute positive");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 6);
    ASSERT(!get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(!get_status_flag(&cpu, ZERO_MASK));
    ASSERT(memory.data[0x2312] == (byte)0x0F);
    END_TESTCASE();
}

void inc_absolute_x() {
    int cycles;
    cpu_t cpu;
    memory_t memory;
    init_memory(&memory);
    reset(&cpu, &memory);
    cpu.program_counter = 0x0000;
    memory.data[0] = INC_ABS_X;
    memory.data[1] = 0x10;
    memory.data[2] = 0x23;
    memory.data[0x2312] = 0xFE;
    cpu.x_register = 0x2;
    START_TESTCASE("inc_absolute_x negative");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 7);
    ASSERT(get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(!get_status_flag(&cpu, ZERO_MASK));
    ASSERT(memory.data[0x2312] == (byte)0xFF);
    END_TESTCASE();

    cpu.program_counter = 0x0000;
    memory.data[0x2312] = 0xFF;
    START_TESTCASE("inc_absolute_x zero");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 7);
    ASSERT(!get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(get_status_flag(&cpu, ZERO_MASK));
    ASSERT(memory.data[0x2312] == (byte)0x00);
    END_TESTCASE();

    cpu.program_counter = 0x0000;
    memory.data[0x2312] = 0x11;
    START_TESTCASE("inc_absolute_x positive");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 7);
    ASSERT(!get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(!get_status_flag(&cpu, ZERO_MASK));
    ASSERT(memory.data[0x2312] == (byte)0x12);
    END_TESTCASE();

    cpu.program_counter = 0x0000;
    memory.data[1] = 0xF0;
    memory.data[2] = 0x23;
    memory.data[0x2400] = 0xFE;
    cpu.x_register = 0x10;
    START_TESTCASE("inc_absolute_x wrap");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 7);
    ASSERT(get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(!get_status_flag(&cpu, ZERO_MASK));
    ASSERT(memory.data[0x2400] == (byte)0xFF);
    END_TESTCASE();
}

void inx() {
    int cycles;
    cpu_t cpu;
    memory_t memory;
    init_memory(&memory);
    reset(&cpu, &memory);
    cpu.program_counter = 0x0000;
    memory.data[0] = INX;
    cpu.x_register = 0xFE;
    START_TESTCASE("inx negative");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 2);
    ASSERT(get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(!get_status_flag(&cpu, ZERO_MASK));
    ASSERT(cpu.x_register == (byte)0xFF);
    END_TESTCASE();

    cpu.program_counter = 0x0000;
    cpu.x_register = 0xFF;
    START_TESTCASE("inx zero");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 2);
    ASSERT(!get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(get_status_flag(&cpu, ZERO_MASK));
    ASSERT(cpu.x_register == (byte)0x00);
    END_TESTCASE();

    cpu.program_counter = 0x0000;
    cpu.x_register = 0x0E;
    START_TESTCASE("inx positive");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 2);
    ASSERT(!get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(!get_status_flag(&cpu, ZERO_MASK));
    ASSERT(cpu.x_register == (byte)0x0F);
    END_TESTCASE();
}

void iny() {
    int cycles;
    cpu_t cpu;
    memory_t memory;
    init_memory(&memory);
    reset(&cpu, &memory);
    cpu.program_counter = 0x0000;
    memory.data[0] = INY;
    cpu.y_register = 0xFE;
    START_TESTCASE("iny negative");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 2);
    ASSERT(get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(!get_status_flag(&cpu, ZERO_MASK));
    ASSERT(cpu.y_register == (byte)0xFF);
    END_TESTCASE();

    cpu.program_counter = 0x0000;
    cpu.y_register = 0xFF;
    START_TESTCASE("iny zero");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 2);
    ASSERT(!get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(get_status_flag(&cpu, ZERO_MASK));
    ASSERT(cpu.y_register == (byte)0x00);
    END_TESTCASE();

    cpu.program_counter = 0x0000;
    cpu.y_register = 0x0E;
    START_TESTCASE("iny positive");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 2);
    ASSERT(!get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(!get_status_flag(&cpu, ZERO_MASK));
    ASSERT(cpu.y_register == (byte)0x0F);
    END_TESTCASE();
}

int main() {
    INIT_TESTS();
    inc_zeropage();
    inc_zeropage_x();
    inc_absolute();
    inc_absolute_x();
    inx();
    iny();
    END_TESTS();
}