#include "6502/cpu.h"
#include "6502/memory.h"
#include "test.h"

void dec_zeropage() {
    int cycles;
    cpu_t cpu;
    memory_t memory;
    init_memory(&memory);
    reset(&cpu, &memory);
    cpu.program_counter = 0x0000;
    memory.data[0] = DEC_ZPG;
    memory.data[1] = 0x12;
    memory.data[0x12] = 0x00;
    START_TESTCASE("decrement_zeropage negative");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 5);
    ASSERT(get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(!get_status_flag(&cpu, ZERO_MASK));
    ASSERT(memory.data[0x12] == (byte)0xFF);
    END_TESTCASE();

    cpu.program_counter = 0x0000;
    memory.data[0x12] = 0x1;
    START_TESTCASE("decrement_zeropage zero");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 5);
    ASSERT(!get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(get_status_flag(&cpu, ZERO_MASK));
    ASSERT(memory.data[0x12] == (byte)0x00);
    END_TESTCASE();

    cpu.program_counter = 0x0000;
    memory.data[0x12] = 0x10;
    START_TESTCASE("decrement_zeropage positive");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 5);
    ASSERT(!get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(!get_status_flag(&cpu, ZERO_MASK));
    ASSERT(memory.data[0x12] == (byte)0x0F);
    END_TESTCASE();
}

void dec_zeropage_x() {
    int cycles;
    cpu_t cpu;
    memory_t memory;
    init_memory(&memory);
    reset(&cpu, &memory);
    cpu.program_counter = 0x0000;
    memory.data[0] = DEC_ZPG_X;
    memory.data[1] = 0x10;
    memory.data[0x12] = 0x0;
    cpu.x_register = 0x2;
    START_TESTCASE("dec_zeropage_x negative");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 6);
    ASSERT(get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(!get_status_flag(&cpu, ZERO_MASK));
    ASSERT(memory.data[0x12] == (byte)0xFF);
    END_TESTCASE();

    cpu.program_counter = 0x0000;
    memory.data[0x12] = 0x1;
    START_TESTCASE("dec_zeropage_x zero");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 6);
    ASSERT(!get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(get_status_flag(&cpu, ZERO_MASK));
    ASSERT(memory.data[0x12] == (byte)0x00);
    END_TESTCASE();

    cpu.program_counter = 0x0000;
    memory.data[0x12] = 0x13;
    START_TESTCASE("dec_zeropage_x positive");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 6);
    ASSERT(!get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(!get_status_flag(&cpu, ZERO_MASK));
    ASSERT(memory.data[0x12] == (byte)0x12);
    END_TESTCASE();

    cpu.program_counter = 0x0000;
    memory.data[1] = 0xF0;
    memory.data[0x10] = 0x0;
    cpu.x_register = 0x20;
    START_TESTCASE("dec_zeropage_x wrap");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 6);
    ASSERT(get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(!get_status_flag(&cpu, ZERO_MASK));
    ASSERT(memory.data[0x10] == (byte)0xFF);
    END_TESTCASE();
}

void dec_absolute() {
    int cycles;
    cpu_t cpu;
    memory_t memory;
    init_memory(&memory);
    reset(&cpu, &memory);
    cpu.program_counter = 0x0000;
    memory.data[0] = DEC_ABS;
    memory.data[1] = 0x12;
    memory.data[2] = 0x23;
    memory.data[0x2312] = 0x00;
    START_TESTCASE("decrement_absolute negative");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 6);
    ASSERT(get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(!get_status_flag(&cpu, ZERO_MASK));
    ASSERT(memory.data[0x2312] == (byte)0xFF);
    END_TESTCASE();

    cpu.program_counter = 0x0000;
    memory.data[0x2312] = 0x1;
    START_TESTCASE("decrement_absolute zero");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 6);
    ASSERT(!get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(get_status_flag(&cpu, ZERO_MASK));
    ASSERT(memory.data[0x2312] == (byte)0x00);
    END_TESTCASE();

    cpu.program_counter = 0x0000;
    memory.data[0x2312] = 0x10;
    START_TESTCASE("decrement_absolute positive");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 6);
    ASSERT(!get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(!get_status_flag(&cpu, ZERO_MASK));
    ASSERT(memory.data[0x2312] == (byte)0x0F);
    END_TESTCASE();
}

void dec_absolute_x() {
    int cycles;
    cpu_t cpu;
    memory_t memory;
    init_memory(&memory);
    reset(&cpu, &memory);
    cpu.program_counter = 0x0000;
    memory.data[0] = DEC_ABS_X;
    memory.data[1] = 0x10;
    memory.data[2] = 0x23;
    memory.data[0x2312] = 0x0;
    cpu.x_register = 0x2;
    START_TESTCASE("dec_absolute_x negative");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 7);
    ASSERT(get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(!get_status_flag(&cpu, ZERO_MASK));
    ASSERT(memory.data[0x2312] == (byte)0xFF);
    END_TESTCASE();

    cpu.program_counter = 0x0000;
    memory.data[0x2312] = 0x1;
    START_TESTCASE("dec_absolute_x zero");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 7);
    ASSERT(!get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(get_status_flag(&cpu, ZERO_MASK));
    ASSERT(memory.data[0x2312] == (byte)0x00);
    END_TESTCASE();

    cpu.program_counter = 0x0000;
    memory.data[0x2312] = 0x13;
    START_TESTCASE("dec_absolute_x positive");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 7);
    ASSERT(!get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(!get_status_flag(&cpu, ZERO_MASK));
    ASSERT(memory.data[0x2312] == (byte)0x12);
    END_TESTCASE();

    cpu.program_counter = 0x0000;
    memory.data[1] = 0xF0;
    memory.data[2] = 0x23;
    memory.data[0x2400] = 0x0;
    cpu.x_register = 0x10;
    START_TESTCASE("dec_absolute_x wrap");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 7);
    ASSERT(get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(!get_status_flag(&cpu, ZERO_MASK));
    ASSERT(memory.data[0x2400] == (byte)0xFF);
    END_TESTCASE();
}

void dex() {
    int cycles;
    cpu_t cpu;
    memory_t memory;
    init_memory(&memory);
    reset(&cpu, &memory);
    cpu.program_counter = 0x0000;
    memory.data[0] = DEX;
    cpu.x_register = 0x0;
    START_TESTCASE("dex negative");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 2);
    ASSERT(get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(!get_status_flag(&cpu, ZERO_MASK));
    ASSERT(cpu.x_register == (byte)0xFF);
    END_TESTCASE();

    cpu.program_counter = 0x0000;
    cpu.x_register = 0x01;
    START_TESTCASE("dex zero");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 2);
    ASSERT(!get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(get_status_flag(&cpu, ZERO_MASK));
    ASSERT(cpu.x_register == (byte)0x00);
    END_TESTCASE();

    cpu.program_counter = 0x0000;
    cpu.x_register = 0x10;
    START_TESTCASE("dex positive");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 2);
    ASSERT(!get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(!get_status_flag(&cpu, ZERO_MASK));
    ASSERT(cpu.x_register == (byte)0x0F);
    END_TESTCASE();
}

void dey() {
    int cycles;
    cpu_t cpu;
    memory_t memory;
    init_memory(&memory);
    reset(&cpu, &memory);
    cpu.program_counter = 0x0000;
    memory.data[0] = DEY;
    cpu.y_register = 0x0;
    START_TESTCASE("dey negative");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 2);
    ASSERT(get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(!get_status_flag(&cpu, ZERO_MASK));
    ASSERT(cpu.y_register == (byte)0xFF);
    END_TESTCASE();

    cpu.program_counter = 0x0000;
    cpu.y_register = 0x01;
    START_TESTCASE("dey zero");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 2);
    ASSERT(!get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(get_status_flag(&cpu, ZERO_MASK));
    ASSERT(cpu.y_register == (byte)0x00);
    END_TESTCASE();

    cpu.program_counter = 0x0000;
    cpu.y_register = 0x10;
    START_TESTCASE("dey positive");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 2);
    ASSERT(!get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(!get_status_flag(&cpu, ZERO_MASK));
    ASSERT(cpu.y_register == (byte)0x0F);
    END_TESTCASE();
}

int main() {
    INIT_TESTS();
    dec_zeropage();
    dec_zeropage_x();
    dec_absolute();
    dec_absolute_x();
    dex();
    dey();
    END_TESTS();
}