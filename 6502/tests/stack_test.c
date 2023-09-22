#include "test.h"

#include "6502/cpu.h"
#include "6502/memory.h"

void pha_pla() {
    int cycles;
    byte previous_stack;
    cpu_t cpu;
    memory_t memory;
    init_memory(&memory);
    reset(&cpu, &memory);
    previous_stack = cpu.stack;
    cpu.program_counter = 0x0000;
    memory.data[0] = PHA;
    cpu.accumulator = 0xFF;
    START_TESTCASE("pha");
    cycles=process_instruction(&cpu);
    ASSERT(cycles == 3);
    ASSERT(memory.data[0x100 | (cpu.stack + 1)] == 0xFF);
    ASSERT(cpu.stack == previous_stack - 1);
    END_TESTCASE();

    cpu.program_counter = 0x0000;
    memory.data[0] = PLA;
    cpu.accumulator = 0x00;
    START_TESTCASE("pla negative");
    cycles=process_instruction(&cpu);
    ASSERT(cycles == 4);
    ASSERT(cpu.accumulator == 0xFF);
    ASSERT(cpu.stack == previous_stack);
    ASSERT(get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(!get_status_flag(&cpu, ZERO_MASK));
    END_TESTCASE();

    cpu.program_counter = 0x0000;
    memory.data[0] = PHA;
    cpu.accumulator = 0x00;
    process_instruction(&cpu);

    cpu.program_counter = 0x0000;
    memory.data[0] = PLA;
    cpu.accumulator = 0xFF;
    START_TESTCASE("pla zero");
    cycles=process_instruction(&cpu);
    ASSERT(cycles == 4);
    ASSERT(cpu.accumulator == 0x00);
    ASSERT(cpu.stack == previous_stack);
    ASSERT(!get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(get_status_flag(&cpu, ZERO_MASK));
    END_TESTCASE();

    cpu.program_counter = 0x0000;
    memory.data[0] = PHA;
    cpu.accumulator = 0x13;
    process_instruction(&cpu);

    cpu.program_counter = 0x0000;
    memory.data[0] = PLA;
    cpu.accumulator = 0x00;
    START_TESTCASE("pla positive");
    cycles=process_instruction(&cpu);
    ASSERT(cycles == 4);
    ASSERT(cpu.accumulator == 0x13);
    ASSERT(cpu.stack == previous_stack);
    ASSERT(!get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(!get_status_flag(&cpu, ZERO_MASK));
    END_TESTCASE();
}

void php_plp() {
    int cycles;
    byte previous_stack;
    cpu_t cpu;
    memory_t memory;
    init_memory(&memory);
    reset(&cpu, &memory);
    previous_stack = cpu.stack;
    cpu.program_counter = 0x0000;
    memory.data[0] = PHP;
    cpu.status = NEGATIVE_MASK | ZERO_MASK | UNUSED_MASK | BREAK_MASK;
    START_TESTCASE("php");
    cycles=process_instruction(&cpu);
    ASSERT(cycles == 3);
    ASSERT(memory.data[0x100 | (cpu.stack + 1)] == NEGATIVE_MASK | ZERO_MASK | UNUSED_MASK | BREAK_MASK);
    ASSERT(cpu.stack == previous_stack - 1);
    END_TESTCASE();

    cpu.program_counter = 0x0000;
    memory.data[0] = PLP;
    cpu.status = 0x00;
    START_TESTCASE("plp");
    cycles=process_instruction(&cpu);
    ASSERT(cycles == 4);
    ASSERT(cpu.status == NEGATIVE_MASK | ZERO_MASK | UNUSED_MASK | BREAK_MASK);
    ASSERT(cpu.stack == previous_stack);
    END_TESTCASE();
}

int main() {
    INIT_TESTS();
    pha_pla();
    php_plp();
    END_TESTS();
}