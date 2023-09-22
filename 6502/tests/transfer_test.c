#include "test.h"

#include "6502/cpu.h"
#include "6502/memory.h"

void tax() {
    int cycles;
    cpu_t cpu;
    memory_t memory;
    init_memory(&memory);
    reset(&cpu, &memory);
    cpu.program_counter = 0x0000;
    memory.data[0] = TAX;
    cpu.accumulator = 0xFF;
    START_TESTCASE("tax negative");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 2);
    ASSERT(cpu.x_register == (byte)0xFF);
    ASSERT(get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(!get_status_flag(&cpu, ZERO_MASK));
    END_TESTCASE();

    cpu.program_counter = 0x0000;
    cpu.accumulator = 0x00;
    START_TESTCASE("tax zero");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 2);
    ASSERT(cpu.x_register == (byte)0x00);
    ASSERT(!get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(get_status_flag(&cpu, ZERO_MASK));
    END_TESTCASE();

    cpu.program_counter = 0x0000;
    cpu.accumulator = 0x13;
    START_TESTCASE("tax positive");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 2);
    ASSERT(cpu.x_register == (byte)0x13);
    ASSERT(!get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(!get_status_flag(&cpu, ZERO_MASK));
    END_TESTCASE();
}

void tay() {
    int cycles;
    cpu_t cpu;
    memory_t memory;
    init_memory(&memory);
    reset(&cpu, &memory);
    cpu.program_counter = 0x0000;
    memory.data[0] = TAY;
    cpu.accumulator = 0xFF;
    START_TESTCASE("tay negative");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 2);
    ASSERT(cpu.y_register == (byte)0xFF);
    ASSERT(get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(!get_status_flag(&cpu, ZERO_MASK));
    END_TESTCASE();

    cpu.program_counter = 0x0000;
    cpu.accumulator = 0x00;
    START_TESTCASE("tay zero");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 2);
    ASSERT(cpu.y_register == (byte)0x00);
    ASSERT(!get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(get_status_flag(&cpu, ZERO_MASK));
    END_TESTCASE();

    cpu.program_counter = 0x0000;
    cpu.accumulator = 0x13;
    START_TESTCASE("tay positive");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 2);
    ASSERT(cpu.y_register == (byte)0x13);
    ASSERT(!get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(!get_status_flag(&cpu, ZERO_MASK));
    END_TESTCASE();
}

void tsx() {
    int cycles;
    cpu_t cpu;
    memory_t memory;
    init_memory(&memory);
    reset(&cpu, &memory);
    cpu.program_counter = 0x0000;
    memory.data[0] = TSX;
    cpu.stack = 0xFF;
    START_TESTCASE("tsx negative");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 2);
    ASSERT(cpu.x_register == (byte)0xFF);
    ASSERT(get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(!get_status_flag(&cpu, ZERO_MASK));
    END_TESTCASE();

    cpu.program_counter = 0x0000;
    cpu.stack = 0x00;
    START_TESTCASE("tsx zero");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 2);
    ASSERT(cpu.x_register == (byte)0x00);
    ASSERT(!get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(get_status_flag(&cpu, ZERO_MASK));
    END_TESTCASE();

    cpu.program_counter = 0x0000;
    cpu.stack = 0x13;
    START_TESTCASE("tsx positive");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 2);
    ASSERT(cpu.x_register == (byte)0x13);
    ASSERT(!get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(!get_status_flag(&cpu, ZERO_MASK));
    END_TESTCASE();
}

void txa() {
    int cycles;
    cpu_t cpu;
    memory_t memory;
    init_memory(&memory);
    reset(&cpu, &memory);
    cpu.program_counter = 0x0000;
    memory.data[0] = TXA;
    cpu.x_register = 0xFF;
    START_TESTCASE("txa negative");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 2);
    ASSERT(cpu.accumulator == (byte)0xFF);
    ASSERT(get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(!get_status_flag(&cpu, ZERO_MASK));
    END_TESTCASE();

    cpu.program_counter = 0x0000;
    cpu.x_register = 0x00;
    START_TESTCASE("txa zero");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 2);
    ASSERT(cpu.accumulator == (byte)0x00);
    ASSERT(!get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(get_status_flag(&cpu, ZERO_MASK));
    END_TESTCASE();

    cpu.program_counter = 0x0000;
    cpu.x_register = 0x13;
    START_TESTCASE("txa positive");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 2);
    ASSERT(cpu.accumulator == (byte)0x13);
    ASSERT(!get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(!get_status_flag(&cpu, ZERO_MASK));
    END_TESTCASE();
}

void txs() {
    int cycles;
    cpu_t cpu;
    memory_t memory;
    init_memory(&memory);
    reset(&cpu, &memory);
    cpu.program_counter = 0x0000;
    memory.data[0] = TXS;
    cpu.x_register = 0xFF;
    START_TESTCASE("txs");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 2);
    ASSERT(cpu.stack == (byte)0xFF);
    END_TESTCASE();
}

void tya() {
    int cycles;
    cpu_t cpu;
    memory_t memory;
    init_memory(&memory);
    reset(&cpu, &memory);
    cpu.program_counter = 0x0000;
    memory.data[0] = TYA;
    cpu.y_register = 0xFF;
    START_TESTCASE("tya negative");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 2);
    ASSERT(cpu.accumulator == (byte)0xFF);
    ASSERT(get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(!get_status_flag(&cpu, ZERO_MASK));
    END_TESTCASE();

    cpu.program_counter = 0x0000;
    cpu.y_register = 0x00;
    START_TESTCASE("tya zero");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 2);
    ASSERT(cpu.accumulator == (byte)0x00);
    ASSERT(!get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(get_status_flag(&cpu, ZERO_MASK));
    END_TESTCASE();

    cpu.program_counter = 0x0000;
    cpu.y_register = 0x13;
    START_TESTCASE("tya positive");
    cycles = process_instruction(&cpu);
    ASSERT(cycles == 2);
    ASSERT(cpu.accumulator == (byte)0x13);
    ASSERT(!get_status_flag(&cpu, NEGATIVE_MASK));
    ASSERT(!get_status_flag(&cpu, ZERO_MASK));
    END_TESTCASE();
}

int main() {
    INIT_TESTS();
    tax();
    tay();
    tsx();
    txa();
    txs();
    tya();
    END_TESTS();
}