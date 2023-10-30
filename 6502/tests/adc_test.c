#include "6502/cpu.h"
#include "6502/memory.h"
#include "test.h"

void adc_imm() {
    int cycles;
    cpu_t cpu;
    memory_t memory;
    init_memory(&memory);
    reset(&cpu, &memory);
    cpu.program_counter = 0x0000;
    cpu.accumulator = 0xF0;
    memory.data[0] = ADC_IMM;
    memory.data[1] = 0x0F;
    START_TESTCASE("adc_imm negative");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 2);
    ASSERT(get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(!get_status_flag(&cpu, ZERO_MASK));
    ASSERT(cpu.accumulator == (byte)0xFF);
    END_TESTCASE();

    cpu.program_counter = 0x0000;
    cpu.accumulator = 0xF0;
    memory.data[0] = ADC_IMM;
    memory.data[1] = 0x0F;
    cpu.status |= CARRY_MASK;
    START_TESTCASE("adc_imm zero");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 2);
    ASSERT(!get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(get_status_flag(&cpu, ZERO_MASK));
    ASSERT(cpu.accumulator == (byte)0x00);
    END_TESTCASE();

    cpu.program_counter = 0x0000;
    cpu.accumulator = 0xF0;
    memory.data[0] = ADC_IMM;
    memory.data[1] = 0x10;
    cpu.status |= CARRY_MASK;
    START_TESTCASE("adc_imm positive");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 2);
    ASSERT(!get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(!get_status_flag(&cpu, ZERO_MASK));
    ASSERT(cpu.accumulator == (byte)0x01);
    END_TESTCASE();

    cpu.program_counter = 0x0000;
    cpu.accumulator = 0xF0;
    memory.data[0] = ADC_IMM;
    memory.data[1] = 0x20;
    cpu.status &= ~CARRY_MASK;
    START_TESTCASE("adc_imm positive no_carry");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 2);
    ASSERT(!get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(!get_status_flag(&cpu, ZERO_MASK));
    ASSERT(cpu.accumulator == (byte)0x10);
    END_TESTCASE();
}

int main() {
    INIT_TESTS();
    adc_imm();
    END_TESTS();
}