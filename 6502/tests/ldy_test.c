#include "6502/cpu.h"
#include "6502/memory.h"
#include "test.h"

void ldy_imm() {
    int cycles;
    cpu_t cpu;
    memory_t memory;
    init_memory(&memory);
    reset(&cpu, &memory);
    cpu.program_counter = 0x0000;
    memory.data[0] = LDY_IMM;
    memory.data[1] = 0xFF;
    START_TESTCASE("ldy_imm negative");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 2);
    ASSERT(cpu.y_register == 0xFF);
    ASSERT(get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(!get_status_flag(&cpu, ZERO_MASK));
    END_TESTCASE();

    cpu.program_counter = 0x0000;
    memory.data[0] = LDY_IMM;
    memory.data[1] = 0x00;
    START_TESTCASE("ldy_imm zero");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 2);
    ASSERT(cpu.y_register == 0x00);
    ASSERT(!get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(get_status_flag(&cpu, ZERO_MASK));
    END_TESTCASE();

    cpu.program_counter = 0x0000;
    memory.data[0] = LDY_IMM;
    memory.data[1] = 0x13;
    START_TESTCASE("ldy_imm positive");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 2);
    ASSERT(cpu.y_register == 0x13);
    ASSERT(!get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(!get_status_flag(&cpu, ZERO_MASK));
    END_TESTCASE();
}

void ldy_zeropage() {
    int cycles;
    cpu_t cpu;
    memory_t memory;
    init_memory(&memory);
    reset(&cpu, &memory);
    cpu.program_counter = 0x0000;
    memory.data[0] = LDY_ZPG;
    memory.data[1] = 0x55;
    memory.data[0x55] = 0xFF;
    START_TESTCASE("ldy_zeropage negative");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 3);
    ASSERT(cpu.y_register == 0xFF);
    ASSERT(get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(!get_status_flag(&cpu, ZERO_MASK));
    END_TESTCASE();

    cpu.program_counter = 0x0000;
    memory.data[0x55] = 0x00;
    START_TESTCASE("ldy_zeropage zero");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 3);
    ASSERT(cpu.y_register == 0x00);
    ASSERT(!get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(get_status_flag(&cpu, ZERO_MASK));
    END_TESTCASE();

    cpu.program_counter = 0x0000;
    memory.data[0x55] = 0x13;
    START_TESTCASE("ldy_zeropage positive");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 3);
    ASSERT(cpu.y_register == 0x13);
    ASSERT(!get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(!get_status_flag(&cpu, ZERO_MASK));
    END_TESTCASE();
}

void ldy_zeropage_x() {
    int cycles;
    cpu_t cpu;
    memory_t memory;
    init_memory(&memory);
    reset(&cpu, &memory);
    cpu.program_counter = 0x0000;
    memory.data[0] = LDY_ZPG_X;
    memory.data[1] = 0x55;
    memory.data[0x65] = 0xFF;
    cpu.x_register = 0x10;
    START_TESTCASE("ldy_zeropage_x negative");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 4);
    ASSERT(cpu.y_register == 0xFF);
    ASSERT(get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(!get_status_flag(&cpu, ZERO_MASK));
    END_TESTCASE();

    cpu.program_counter = 0x0000;
    memory.data[0x65] = 0x00;
    cpu.x_register = 0x10;
    START_TESTCASE("ldy_zeropage_x zero");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 4);
    ASSERT(cpu.y_register == 0x00);
    ASSERT(!get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(get_status_flag(&cpu, ZERO_MASK));
    END_TESTCASE();

    cpu.program_counter = 0x0000;
    memory.data[0x65] = 0x13;
    cpu.x_register = 0x10;
    START_TESTCASE("ldy_zeropage_x positive");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 4);
    ASSERT(cpu.y_register == 0x13);
    ASSERT(!get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(!get_status_flag(&cpu, ZERO_MASK));
    END_TESTCASE();

    cpu.program_counter = 0x0000;
    memory.data[0x45] = 0x13;
    cpu.x_register = 0xF0;
    START_TESTCASE("ldy_zeropage_x wrap");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 4);
    ASSERT(cpu.y_register == 0x13);
    ASSERT(!get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(!get_status_flag(&cpu, ZERO_MASK));
    END_TESTCASE();
}

void ldy_abs() {
    int cycles;
    cpu_t cpu;
    memory_t memory;
    init_memory(&memory);
    reset(&cpu, &memory);
    cpu.program_counter = 0x0000;
    memory.data[0] = LDY_ABS;
    memory.data[1] = 0x55;
    memory.data[2] = 0x44;
    memory.data[0x4455] = 0xFF;
    START_TESTCASE("ldy_absolute negative");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 4);
    ASSERT(cpu.y_register == 0xFF);
    ASSERT(get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(!get_status_flag(&cpu, ZERO_MASK));
    END_TESTCASE();

    cpu.program_counter = 0x0000;
    memory.data[0x4455] = 0x00;
    START_TESTCASE("ldy_absolute zero");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 4);
    ASSERT(cpu.y_register == 0x00);
    ASSERT(!get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(get_status_flag(&cpu, ZERO_MASK));
    END_TESTCASE();

    cpu.program_counter = 0x0000;
    memory.data[0x4455] = 0x13;
    START_TESTCASE("ldy_absolute positive");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 4);
    ASSERT(cpu.y_register == 0x13);
    ASSERT(!get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(!get_status_flag(&cpu, ZERO_MASK));
    END_TESTCASE();
}

void ldy_abs_x() {
    int cycles;
    cpu_t cpu;
    memory_t memory;
    init_memory(&memory);
    reset(&cpu, &memory);
    cpu.program_counter = 0x0000;
    memory.data[0] = LDY_ABS_X;
    memory.data[1] = 0x50;
    memory.data[2] = 0x44;
    memory.data[0x4455] = 0xFF;
    cpu.x_register = 0x05;
    START_TESTCASE("ldy_absolute_x negative");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 4);
    ASSERT(cpu.y_register == 0xFF);
    ASSERT(get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(!get_status_flag(&cpu, ZERO_MASK));
    END_TESTCASE();

    cpu.program_counter = 0x0000;
    memory.data[0x4455] = 0x00;
    cpu.x_register = 0x05;
    START_TESTCASE("ldy_absolute_x zero");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 4);
    ASSERT(cpu.y_register == 0x00);
    ASSERT(!get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(get_status_flag(&cpu, ZERO_MASK));
    END_TESTCASE();

    cpu.program_counter = 0x0000;
    memory.data[0x4455] = 0x13;
    cpu.x_register = 0x05;
    START_TESTCASE("ldy_absolute_x positive");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 4);
    ASSERT(cpu.y_register == 0x13);
    ASSERT(!get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(!get_status_flag(&cpu, ZERO_MASK));
    END_TESTCASE();

    cpu.program_counter = 0x0000;
    memory.data[1] = 0x50;
    memory.data[2] = 0x44;
    memory.data[0x4540] = 0x13;
    cpu.x_register = 0xF0;
    START_TESTCASE("ldy_absolute_x wrap");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 5);
    ASSERT(cpu.y_register == 0x13);
    ASSERT(!get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(!get_status_flag(&cpu, ZERO_MASK));
    END_TESTCASE();
}

int main() {
    INIT_TESTS();
    ldy_imm();
    ldy_zeropage();
    ldy_zeropage_x();
    ldy_abs();
    ldy_abs_x();
    END_TESTS();
}