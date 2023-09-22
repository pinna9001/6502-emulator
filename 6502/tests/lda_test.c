#include "6502/cpu.h"
#include "6502/memory.h"
#include "test.h"

void lda_imm() {
    int cycles;
    cpu_t cpu;
    memory_t memory;
    init_memory(&memory);
    reset(&cpu, &memory);
    cpu.program_counter = 0x0000;
    memory.data[0] = LDA_IMM;
    memory.data[1] = 0xFF;
    START_TESTCASE("lda_imm negative");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 2);
    ASSERT(get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(!get_status_flag(&cpu, ZERO_MASK));
    ASSERT(cpu.accumulator == (byte)0xFF);
    END_TESTCASE();

    cpu.program_counter = 0x0000;
    memory.data[1] = 0x00;
    START_TESTCASE("lda_imm zero");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 2);
    ASSERT(!get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(get_status_flag(&cpu, ZERO_MASK));
    ASSERT(cpu.accumulator == (byte)0x00);
    END_TESTCASE();

    cpu.program_counter = 0x0000;
    memory.data[1] = 0x12;
    START_TESTCASE("lda_imm positive");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 2);
    ASSERT(!get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(!get_status_flag(&cpu, ZERO_MASK));
    ASSERT(cpu.accumulator == (byte)0x12);
    END_TESTCASE();
}

void lda_zeropage() {
    int cycles;
    cpu_t cpu;
    memory_t memory;
    init_memory(&memory);
    reset(&cpu, &memory);
    cpu.program_counter = 0x0000;
    memory.data[0] = LDA_ZPG;
    memory.data[1] = 0x55;
    memory.data[0x55] = 0xFF;
    START_TESTCASE("lda_zeropage negative");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 3);
    ASSERT(get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(!get_status_flag(&cpu, ZERO_MASK));
    ASSERT(cpu.accumulator == (byte)0xFF);
    END_TESTCASE();

    cpu.program_counter = 0x0000;
    memory.data[0x55] = 0x00;
    START_TESTCASE("lda_zeropage zero");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 3);
    ASSERT(!get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(get_status_flag(&cpu, ZERO_MASK));
    ASSERT(cpu.accumulator == (byte)0x00);
    END_TESTCASE();

    cpu.program_counter = 0x0000;
    memory.data[0x55] = 0x12;
    START_TESTCASE("lda_zeropage positive");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 3);
    ASSERT(!get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(!get_status_flag(&cpu, ZERO_MASK));
    ASSERT(cpu.accumulator == (byte)0x12);
    END_TESTCASE();
}

void lda_zeropage_x() {
    int cycles;
    cpu_t cpu;
    memory_t memory;
    init_memory(&memory);
    reset(&cpu, &memory);
    cpu.program_counter = 0x0000;
    memory.data[0] = LDA_ZPG_X;
    memory.data[1] = 0x55;
    memory.data[0x58] = 0xFF;
    cpu.x_register = 0x3;
    START_TESTCASE("lda_zeropage_x negative");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 4);
    ASSERT(get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(!get_status_flag(&cpu, ZERO_MASK));
    ASSERT(cpu.accumulator == (byte)0xFF);
    END_TESTCASE();

    cpu.program_counter = 0x0000;
    memory.data[0x58] = 0x00;
    START_TESTCASE("lda_zeropage_x zero");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 4);
    ASSERT(!get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(get_status_flag(&cpu, ZERO_MASK));
    ASSERT(cpu.accumulator == (byte)0x00);
    END_TESTCASE();

    cpu.program_counter = 0x0000;
    memory.data[0x58] = 0x12;
    START_TESTCASE("lda_zeropage_x positive");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 4);
    ASSERT(!get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(!get_status_flag(&cpu, ZERO_MASK));
    ASSERT(cpu.accumulator == (byte)0x12);
    END_TESTCASE();

    cpu.program_counter = 0x0000;
    memory.data[0] = LDA_ZPG_X;
    memory.data[1] = 0xFF;
    memory.data[0x58] = 0x14;
    cpu.x_register = 0x59;
    START_TESTCASE("lda_zeropage_x wrap");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 4);
    ASSERT(!get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(!get_status_flag(&cpu, ZERO_MASK));
    ASSERT(cpu.accumulator == (byte)0x14);
    END_TESTCASE();
}

void lda_abs() {
    int cycles;
    cpu_t cpu;
    memory_t memory;
    init_memory(&memory);
    reset(&cpu, &memory);
    cpu.program_counter = 0x0000;
    memory.data[0] = LDA_ABS;
    memory.data[1] = 0x58;
    memory.data[2] = 0x00;
    memory.data[0x58] = 0xFF;
    START_TESTCASE("lda_abs negative");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 4);
    ASSERT(get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(!get_status_flag(&cpu, ZERO_MASK));
    ASSERT(cpu.accumulator == (byte)0xFF);
    END_TESTCASE();

    cpu.program_counter = 0x0000;
    memory.data[0x58] = 0x00;
    START_TESTCASE("lda_abs zero");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 4);
    ASSERT(!get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(get_status_flag(&cpu, ZERO_MASK));
    ASSERT(cpu.accumulator == (byte)0x00);
    END_TESTCASE();

    cpu.program_counter = 0x0000;
    memory.data[0x58] = 0x13;
    START_TESTCASE("lda_abs positive");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 4);
    ASSERT(!get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(!get_status_flag(&cpu, ZERO_MASK));
    ASSERT(cpu.accumulator == (byte)0x13);
    END_TESTCASE();
}

void lda_abs_x() {
    int cycles;
    cpu_t cpu;
    memory_t memory;
    init_memory(&memory);
    reset(&cpu, &memory);
    cpu.program_counter = 0x0000;
    memory.data[0] = LDA_ABS_X;
    memory.data[1] = 0x58;
    memory.data[2] = 0x00;
    memory.data[0x59] = 0xFF;
    cpu.x_register = 0x01;
    START_TESTCASE("lda_abs_x negative");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 4);
    ASSERT(get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(!get_status_flag(&cpu, ZERO_MASK));
    ASSERT(cpu.accumulator == (byte)0xFF);
    END_TESTCASE();

    cpu.program_counter = 0x0000;
    memory.data[0x59] = 0x00;
    START_TESTCASE("lda_abs_x zero");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 4);
    ASSERT(!get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(get_status_flag(&cpu, ZERO_MASK));
    ASSERT(cpu.accumulator == (byte)0x00);
    END_TESTCASE();

    cpu.program_counter = 0x0000;
    memory.data[0x59] = 0x13;
    START_TESTCASE("lda_abs_x positive");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 4);
    ASSERT(!get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(!get_status_flag(&cpu, ZERO_MASK));
    ASSERT(cpu.accumulator == (byte)0x13);
    END_TESTCASE();

    cpu.program_counter = 0x0000;
    memory.data[1] = 0xFF;
    memory.data[2] = 0x00;
    memory.data[0x100] = 0xFF;
    START_TESTCASE("lda_abs_x wrap");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 5);
    ASSERT(get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(!get_status_flag(&cpu, ZERO_MASK));
    ASSERT(cpu.accumulator == (byte)0xFF);
    END_TESTCASE();
}

void lda_abs_y() {
    int cycles;
    cpu_t cpu;
    memory_t memory;
    init_memory(&memory);
    reset(&cpu, &memory);
    cpu.program_counter = 0x0000;
    memory.data[0] = LDA_ABS_Y;
    memory.data[1] = 0x58;
    memory.data[2] = 0x00;
    memory.data[0x59] = 0xFF;
    cpu.y_register = 0x01;
    START_TESTCASE("lda_abs_y negative");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 4);
    ASSERT(get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(!get_status_flag(&cpu, ZERO_MASK));
    ASSERT(cpu.accumulator == (byte)0xFF);
    END_TESTCASE();

    cpu.program_counter = 0x0000;
    memory.data[0x59] = 0x00;
    START_TESTCASE("lda_abs_y zero");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 4);
    ASSERT(!get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(get_status_flag(&cpu, ZERO_MASK));
    ASSERT(cpu.accumulator == (byte)0x00);
    END_TESTCASE();

    cpu.program_counter = 0x0000;
    memory.data[0x59] = 0x13;
    START_TESTCASE("lda_abs_y positive");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 4);
    ASSERT(!get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(!get_status_flag(&cpu, ZERO_MASK));
    ASSERT(cpu.accumulator == (byte)0x13);
    END_TESTCASE();

    cpu.program_counter = 0x0000;
    memory.data[1] = 0xFF;
    memory.data[2] = 0x00;
    memory.data[0x100] = 0xFF;
    START_TESTCASE("lda_abs_y wrap");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 5);
    ASSERT(get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(!get_status_flag(&cpu, ZERO_MASK));
    ASSERT(cpu.accumulator == (byte)0xFF);
    END_TESTCASE();
}

void lda_x_ind() {
    int cycles;
    cpu_t cpu;
    memory_t memory;
    init_memory(&memory);
    reset(&cpu, &memory);
    cpu.program_counter = 0x0000;
    memory.data[0] = LDA_X_IND;
    memory.data[1] = 0x70;
    memory.data[0x75] = 0x40;
    memory.data[0x76] = 0x30;
    memory.data[0x3040] = 0xFF;
    cpu.x_register = 0x05;
    START_TESTCASE("lda_x_ind negative");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 6);
    ASSERT(get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(!get_status_flag(&cpu, ZERO_MASK));
    ASSERT(cpu.accumulator == (byte)0xFF);
    END_TESTCASE();

    cpu.program_counter = 0x0000;
    memory.data[0x3040] = 0x00;
    START_TESTCASE("lda_x_ind zero");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 6);
    ASSERT(!get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(get_status_flag(&cpu, ZERO_MASK));
    ASSERT(cpu.accumulator == (byte)0x00);
    END_TESTCASE();

    cpu.program_counter = 0x0000;
    memory.data[0] = LDA_X_IND;
    memory.data[0x3040] = 0x13;
    START_TESTCASE("lda_x_ind positive");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 6);
    ASSERT(!get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(!get_status_flag(&cpu, ZERO_MASK));
    ASSERT(cpu.accumulator == (byte)0x13);
    END_TESTCASE();

    cpu.program_counter = 0x0000;
    memory.data[0] = LDA_X_IND;
    memory.data[1] = 0x5F;
    memory.data[0x5E] = 0x40;
    memory.data[0x5F] = 0x30;
    memory.data[0x3040] = 0x13;
    cpu.x_register = 0xFF;
    START_TESTCASE("lda_x_ind wrap");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 6);
    ASSERT(!get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(!get_status_flag(&cpu, ZERO_MASK));
    ASSERT(cpu.accumulator == (byte)0x13);
    END_TESTCASE();
}

void lda_ind_y() {
    int cycles;
    cpu_t cpu;
    memory_t memory;
    init_memory(&memory);
    reset(&cpu, &memory);
    cpu.program_counter = 0x0000;
    memory.data[0] = LDA_IND_Y;
    memory.data[1] = 0x70;
    memory.data[0x70] = 0x40;
    memory.data[0x71] = 0x30;
    memory.data[0x3045] = 0xFF;
    cpu.y_register = 0x05;
    START_TESTCASE("lda_ind_y negative");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 5);
    ASSERT(get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(!get_status_flag(&cpu, ZERO_MASK));
    ASSERT(cpu.accumulator == (byte)0xFF);
    END_TESTCASE();

    cpu.program_counter = 0x0000;
    memory.data[0x3045] = 0x00;
    START_TESTCASE("lda_ind_y zero");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 5);
    ASSERT(!get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(get_status_flag(&cpu, ZERO_MASK));
    ASSERT(cpu.accumulator == (byte)0x00);
    END_TESTCASE();

    cpu.program_counter = 0x0000;
    memory.data[0x3045] = 0x13;
    START_TESTCASE("lda_ind_y positive");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 5);
    ASSERT(!get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(!get_status_flag(&cpu, ZERO_MASK));
    ASSERT(cpu.accumulator == (byte)0x13);
    END_TESTCASE();

    cpu.program_counter = 0x0000;
    memory.data[0x3130] = 0x13;
    cpu.y_register = 0xF0;
    START_TESTCASE("lda_ind_y wrap");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 6);
    ASSERT(!get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(!get_status_flag(&cpu, ZERO_MASK));
    ASSERT(cpu.accumulator == (byte)0x13);
    END_TESTCASE();
}

int main() {
    INIT_TESTS();
    lda_imm();
    lda_zeropage();
    lda_zeropage_x();
    lda_abs();
    lda_abs_x();
    lda_abs_y();
    lda_x_ind();
    lda_ind_y();
    END_TESTS();
}