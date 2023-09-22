#include "6502/cpu.h"
#include "6502/memory.h"
#include "test.h"

void ldx_imm() {
    int cycles;
    cpu_t cpu;
    memory_t memory;
    init_memory(&memory);
    reset(&cpu, &memory);
    cpu.program_counter = 0x0000;
    memory.data[0] = LDX_IMM;
    memory.data[1] = 0xFF;
    START_TESTCASE("ldx_imm negative");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 2);
    ASSERT(cpu.x_register == 0xFF);
    ASSERT(get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(!get_status_flag(&cpu, ZERO_MASK));
    END_TESTCASE();

    cpu.program_counter = 0x0000;
    memory.data[0] = LDX_IMM;
    memory.data[1] = 0x00;
    START_TESTCASE("ldx_imm zero");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 2);
    ASSERT(cpu.x_register == 0x00);
    ASSERT(!get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(get_status_flag(&cpu, ZERO_MASK));
    END_TESTCASE();

    cpu.program_counter = 0x0000;
    memory.data[0] = LDX_IMM;
    memory.data[1] = 0x13;
    START_TESTCASE("ldx_imm positive");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 2);
    ASSERT(cpu.x_register == 0x13);
    ASSERT(!get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(!get_status_flag(&cpu, ZERO_MASK));
    END_TESTCASE();
}

void ldx_zeropage() {
    int cycles;
    cpu_t cpu;
    memory_t memory;
    init_memory(&memory);
    reset(&cpu, &memory);
    cpu.program_counter = 0x0000;
    memory.data[0] = LDX_ZPG;
    memory.data[1] = 0x55;
    memory.data[0x55] = 0xFF;
    START_TESTCASE("ldx_zeropage negative");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 3);
    ASSERT(cpu.x_register == 0xFF);
    ASSERT(get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(!get_status_flag(&cpu, ZERO_MASK));
    END_TESTCASE();

    cpu.program_counter = 0x0000;
    memory.data[0x55] = 0x00;
    START_TESTCASE("ldx_zeropage zero");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 3);
    ASSERT(cpu.x_register == 0x00);
    ASSERT(!get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(get_status_flag(&cpu, ZERO_MASK));
    END_TESTCASE();

    cpu.program_counter = 0x0000;
    memory.data[0x55] = 0x13;
    START_TESTCASE("ldx_zeropage positive");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 3);
    ASSERT(cpu.x_register == 0x13);
    ASSERT(!get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(!get_status_flag(&cpu, ZERO_MASK));
    END_TESTCASE();
}

void ldx_zeropage_y() {
    int cycles;
    cpu_t cpu;
    memory_t memory;
    init_memory(&memory);
    reset(&cpu, &memory);
    cpu.program_counter = 0x0000;
    memory.data[0] = LDX_ZPG_Y;
    memory.data[1] = 0x55;
    memory.data[0x65] = 0xFF;
    cpu.y_register = 0x10;
    START_TESTCASE("ldx_zeropage_y negative");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 4);
    ASSERT(cpu.x_register == 0xFF);
    ASSERT(get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(!get_status_flag(&cpu, ZERO_MASK));
    END_TESTCASE();

    cpu.program_counter = 0x0000;
    memory.data[0] = LDX_ZPG_Y;
    memory.data[1] = 0x55;
    memory.data[0x65] = 0x00;
    cpu.y_register = 0x10;
    START_TESTCASE("ldx_zeropage_y zero");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 4);
    ASSERT(cpu.x_register == 0x00);
    ASSERT(!get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(get_status_flag(&cpu, ZERO_MASK));
    END_TESTCASE();

    cpu.program_counter = 0x0000;
    memory.data[0] = LDX_ZPG_Y;
    memory.data[1] = 0x55;
    memory.data[0x65] = 0x13;
    cpu.y_register = 0x10;
    START_TESTCASE("ldx_zeropage_y positive");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 4);
    ASSERT(cpu.x_register == 0x13);
    ASSERT(!get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(!get_status_flag(&cpu, ZERO_MASK));
    END_TESTCASE();

    cpu.program_counter = 0x0000;
    memory.data[0] = LDX_ZPG_Y;
    memory.data[1] = 0x55;
    memory.data[0x45] = 0x13;
    cpu.y_register = 0xF0;
    START_TESTCASE("ldx_zeropage_y wrap");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 4);
    ASSERT(cpu.x_register == 0x13);
    ASSERT(!get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(!get_status_flag(&cpu, ZERO_MASK));
    END_TESTCASE();
}

void ldx_abs() {
    int cycles;
    cpu_t cpu;
    memory_t memory;
    init_memory(&memory);
    reset(&cpu, &memory);
    cpu.program_counter = 0x0000;
    memory.data[0] = LDX_ABS;
    memory.data[1] = 0x55;
    memory.data[2] = 0x44;
    memory.data[0x4455] = 0xFF;
    START_TESTCASE("ldx_absolute negative");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 4);
    ASSERT(cpu.x_register == 0xFF);
    ASSERT(get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(!get_status_flag(&cpu, ZERO_MASK));
    END_TESTCASE();

    cpu.program_counter = 0x0000;
    memory.data[0x4455] = 0x00;
    START_TESTCASE("ldx_absolute zero");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 4);
    ASSERT(cpu.x_register == 0x00);
    ASSERT(!get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(get_status_flag(&cpu, ZERO_MASK));
    END_TESTCASE();

    cpu.program_counter = 0x0000;
    memory.data[0x4455] = 0x13;
    START_TESTCASE("ldx_absolute positive");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 4);
    ASSERT(cpu.x_register == 0x13);
    ASSERT(!get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(!get_status_flag(&cpu, ZERO_MASK));
    END_TESTCASE();
}

void ldx_abs_y() {
    int cycles;
    cpu_t cpu;
    memory_t memory;
    init_memory(&memory);
    reset(&cpu, &memory);
    cpu.program_counter = 0x0000;
    memory.data[0] = LDX_ABS_Y;
    memory.data[1] = 0x50;
    memory.data[2] = 0x44;
    memory.data[0x4455] = 0xFF;
    cpu.y_register = 0x05;
    START_TESTCASE("ldx_absolute_y negative");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 4);
    ASSERT(cpu.x_register == 0xFF);
    ASSERT(get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(!get_status_flag(&cpu, ZERO_MASK));
    END_TESTCASE();

    cpu.program_counter = 0x0000;
    memory.data[0x4455] = 0x00;
    cpu.y_register = 0x05;
    START_TESTCASE("ldx_absolute_y zero");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 4);
    ASSERT(cpu.x_register == 0x00);
    ASSERT(!get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(get_status_flag(&cpu, ZERO_MASK));
    END_TESTCASE();

    cpu.program_counter = 0x0000;
    memory.data[0x4455] = 0x13;
    cpu.y_register = 0x05;
    START_TESTCASE("ldx_absolute_y positive");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 4);
    ASSERT(cpu.x_register == 0x13);
    ASSERT(!get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(!get_status_flag(&cpu, ZERO_MASK));
    END_TESTCASE();

    cpu.program_counter = 0x0000;
    memory.data[1] = 0x50;
    memory.data[2] = 0x44;
    memory.data[0x4540] = 0x13;
    cpu.y_register = 0xF0;
    START_TESTCASE("ldx_absolute_y wrap");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 5);
    ASSERT(cpu.x_register == 0x13);
    ASSERT(!get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(!get_status_flag(&cpu, ZERO_MASK));
    END_TESTCASE();
}

int main() {
    INIT_TESTS();
    ldx_imm();
    ldx_zeropage();
    ldx_zeropage_y();
    ldx_abs();
    ldx_abs_y();
    END_TESTS();
}