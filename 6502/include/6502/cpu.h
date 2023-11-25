#ifndef CPU_H
#define CPU_H

#include "6502/common.h"
#include "6502/memory.h"

#include <stdbool.h>
#include <stdint.h>

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

    SBC_IMM = 0xE9,
    SBC_ZPG = 0xE5,
    SBC_ZPG_X = 0xF5,
    SBC_ABS = 0xED,
    SBC_ABS_X = 0xFD,
    SBC_ABS_Y = 0xF9,
    SBC_X_IND = 0xE1,
    SBC_IND_Y = 0xF1,

    AND_IMM = 0x29,
    AND_ZPG = 0x25,
    AND_ZPG_X = 0x35,
    AND_ABS = 0x2D,
    AND_ABS_X = 0x3D,
    AND_ABS_Y = 0x39,
    AND_X_IND = 0x21,
    AND_IND_Y = 0x31,

    EOR_IMM = 0x49,
    EOR_ZPG = 0x45,
    EOR_ZPG_X = 0x55,
    EOR_ABS = 0x4D,
    EOR_ABS_X = 0x5D,
    EOR_ABS_Y = 0x59,
    EOR_X_IND = 0x41,
    EOR_IND_Y = 0x51,

    ORA_IMM = 0x09,
    ORA_ZPG = 0x05,
    ORA_ZPG_X = 0x15,
    ORA_ABS = 0x0D,
    ORA_ABS_X = 0x1D,
    ORA_ABS_Y = 0x19,
    ORA_X_IND = 0x01,
    ORA_IND_Y = 0x11,

// TODO add instructions to switch
    ASL_A = 0x0A,
    ASL_ZPG = 0x06,
    ASL_ZPG_X = 0x16,
    ASL_ABS = 0x0E,
    ASL_ABS_X = 0x1E,

    LSR_A = 0x4A,
    LSR_ZPG = 0x46,
    LSR_ZPG_X = 0x56,
    LSR_ABS = 0x4E,
    LSR_ABS_X = 0x5E,

    ROL_A = 0x2A,
    ROL_ZPG = 0x26,
    ROL_ZPG_X = 0x36,
    ROL_ABS = 0x2E,
    ROL_ABS_X = 0x3E,

    ROR_A = 0x6A,
    ROR_ZPG = 0x66,
    ROR_ZPG_X = 0x76,
    ROR_ABS = 0x6E,
    ROR_ABS_X = 0x7E,

    CLC = 0x18,
    CLD = 0xD8,
    CLI = 0x58,
    CLV = 0xB8,

    SEC = 0x38,
    SED = 0xF8,
    SEI = 0x78,

    CMP_IMM = 0xC9,
    CMP_ZPG = 0xC5,
    CMP_ZPG_X = 0xD5,
    CMP_ABS = 0xCD,
    CMP_ABS_X = 0xDD,
    CMP_ABS_Y = 0xD9,
    CMP_X_IND = 0xC1,
    CMP_IND_Y = 0xD1,

    CPX_IMM = 0xE0,
    CPX_ZPG = 0xE4,
    CPX_ABS = 0xEC,

    CPY_IMM = 0xC0,
    CPY_ZPG = 0xC4,
    CPY_ABS = 0xCC,

    BCC = 0x90,
    BCS = 0xB0,
    BEQ = 0xF0,
    BMI = 0x30,
    BNE = 0xD0,
    BPL = 0x10,
    BVC = 0x50,
    BVS = 0x70,

    JMP_ABS = 0x4C,
    JMP_IND = 0x6C,
    JSR = 0x20,
    RTS = 0x60,

    BRK = 0x00,
    RTI = 0x40,

    BIT_ZPG = 0x24,
    BIT_ABS = 0x2C,
    NOP = 0xEA,
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