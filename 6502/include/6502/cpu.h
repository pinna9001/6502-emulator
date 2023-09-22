#ifndef CPU_H
#define CPU_H

#include <stdbool.h>
#include <stdint.h>

#include "6502/common.h"
#include "6502/memory.h"

#define CARRY_MASK (byte)(1 << 0)
#define ZERO_MASK (byte)(1 << 1)
#define INTERRUPT_DISABLE_MASK (byte)(1 << 2)
#define DECIMAL_MASK (byte)(1 << 3)
#define BREAK_MASK (byte)(1 << 4)
#define UNUSED_MASK (byte)(1 << 5)
#define OVERFLOW_MASK (byte)(1 << 6)
#define NEGATIVE_MASK (byte)(1 << 7)

typedef enum instructions_t {
    LDA_IMM = 0xA9,
    LDA_ZPG = 0xA5,
    LDA_ZPG_X = 0xB5,
    LDA_ABS = 0xAD,
    LDA_ABS_X = 0xBD,
    LDA_ABS_Y = 0xB9,
    LDA_X_IND = 0xA1,
    LDA_IND_Y = 0xB1,

    LDX_IMM = 0xA2,
    LDX_ZPG = 0xA6,
    LDX_ZPG_Y = 0xB6,
    LDX_ABS = 0xAE,
    LDX_ABS_Y = 0xBE,

    LDY_IMM = 0xA0,
    LDY_ZPG = 0xA4,
    LDY_ZPG_X = 0xB4,
    LDY_ABS = 0xAC,
    LDY_ABS_X = 0xBC,

    STA_ZPG = 0x85,
    STA_ZPG_X = 0x95,
    STA_ABS = 0x8D,
    STA_ABS_X = 0x9D,
    STA_ABS_Y = 0x99,
    STA_X_IND = 0x81,
    STA_IND_Y = 0x91,

    STX_ZPG = 0x86,
    STX_ZPG_Y = 0x96,
    STX_ABS = 0x8E,

    STY_ZPG = 0x84,
    STY_ZPG_X = 0x94,
    STY_ABS = 0x8C,

    TAX = 0xAA,
    TAY = 0xA8,
    TSX = 0xBA,
    TXA = 0x8A,
    TXS = 0x9A,
    TYA = 0x98,

    PHA = 0x48,
    PHP = 0x08,
    PLA = 0x68,
    PLP = 0x28,

    DEC_ZPG = 0xC6,
    DEC_ZPG_X = 0xD6,
    DEC_ABS = 0xCE,
    DEC_ABS_X = 0xDE,
    DEX = 0xCA,
    DEY = 0x88,

    INC_ZPG = 0xE6,
    INC_ZPG_X = 0xF6,
    INC_ABS = 0xEE,
    INC_ABS_X = 0xFe,
    INX = 0xE8,
    INY = 0xC8,

    ADC_IMM = 0x69,
    ADC_ZPG = 0x65,
    ADC_ZPG_X = 0x75,
    ADC_ABS = 0x6D,
    ADC_ABS_X = 0x7D,
    ADC_ABS_Y = 0x79,
    ADC_X_IND = 0x61,
    ADC_IND_Y = 0x71,
} instructions_t;

typedef struct cpu_t {
    byte accumulator;
    byte x_register;
    byte y_register;

    word program_counter;

    byte stack;

    byte status;

    memory_t* memory;

    uint64_t cycles;
} cpu_t;

int process_instruction(cpu_t* cpu);
byte fetch_byte(int* cycles, cpu_t* cpu);
byte read_byte(int* cycles, cpu_t* cpu, word address);
bool get_status_flag(cpu_t* cpu, byte flag);
void reset(cpu_t* cpu, memory_t* memory);

#endif  // CPU_H