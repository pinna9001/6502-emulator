#include "6502/cpu.h"

#include <stdio.h>

#include "6502/common.h"
#include "6502/memory.h"

word zeropage_address(int* cycles, cpu_t* cpu);
word zeropage_x_address(int* cycles, cpu_t* cpu);
word zeropage_y_address(int* cycles, cpu_t* cpu);
word absolute_address(int* cycles, cpu_t* cpu);
word absolute_x_address(int* cycles, cpu_t* cpu);
word absolute_x_address_5(int* cycles, cpu_t* cpu);
word absolute_y_address(int* cycles, cpu_t* cpu);
word indirect_address(int* cycles, cpu_t* cpu);
word x_indirect_address(int* cycles, cpu_t* cpu);
word indirect_y_address(int* cycles, cpu_t* cpu);
sbyte relative_address(int* cycles, cpu_t* cpu);

void increment(int* cycles, cpu_t* cpu, word address);
void decrement(int* cycles, cpu_t* cpu, word address);

// TODO decimal mode to function or to extra function (enables/disables through instructions SED CLD)
void add(int* cycles, cpu_t* cpu, byte value);
void sub(int* cycles, cpu_t* cpu, byte value);

void and (int* cycles, cpu_t* cpu, byte value);
void eor(int* cycles, cpu_t* cpu, byte value);
void or (int* cycles, cpu_t* cpu, byte value);

void push_stack(int* cycles, cpu_t* cpu, byte value);
byte pull_stack(int* cycles, cpu_t* cpu);

void set_carry_flag(cpu_t* cpu);
void clear_carry_flag(cpu_t* cpu);
void set_overflow_flag(cpu_t* cpu);
void clear_overflow_flag(cpu_t* cpu);
void set_negative_flag(cpu_t* cpu, byte value);
void set_zero_flag(cpu_t* cpu, byte value);

byte fetch_byte(int* cycles, cpu_t* cpu) {
    byte data = read_memory(cpu->memory, cpu->program_counter);
    cpu->program_counter++;
    (*cycles)++;
    return data;
}

byte read_byte(int* cycles, cpu_t* cpu, word address) {
    byte data = read_memory(cpu->memory, address);
    (*cycles)++;
    return data;
}

void write_byte(int* cycles, cpu_t* cpu, word address, byte data) {
    write_memory(cpu->memory, address, data);
    (*cycles)++;
}

int process_instruction(cpu_t* cpu) {
    int used_cycles = 0;
    instructions_t instruction = fetch_byte(&used_cycles, cpu);
    switch (instruction) {
        case LDA_IMM: {
            cpu->accumulator = fetch_byte(&used_cycles, cpu);
            set_negative_flag(cpu, cpu->accumulator);
            set_zero_flag(cpu, cpu->accumulator);
            break;
        }
        case LDA_ZPG: {
            word address = zeropage_address(&used_cycles, cpu);
            cpu->accumulator = read_byte(&used_cycles, cpu, address);
            set_negative_flag(cpu, cpu->accumulator);
            set_zero_flag(cpu, cpu->accumulator);
            break;
        }
        case LDA_ZPG_X: {
            word address = zeropage_x_address(&used_cycles, cpu);
            cpu->accumulator = read_byte(&used_cycles, cpu, address);
            set_negative_flag(cpu, cpu->accumulator);
            set_zero_flag(cpu, cpu->accumulator);
            break;
        }
        case LDA_ABS: {
            word address = absolute_address(&used_cycles, cpu);
            cpu->accumulator = read_byte(&used_cycles, cpu, address);
            set_negative_flag(cpu, cpu->accumulator);
            set_zero_flag(cpu, cpu->accumulator);
            break;
        }
        case LDA_ABS_X: {
            word address = absolute_x_address(&used_cycles, cpu);
            cpu->accumulator = read_byte(&used_cycles, cpu, address);
            set_negative_flag(cpu, cpu->accumulator);
            set_zero_flag(cpu, cpu->accumulator);
            break;
        }
        case LDA_ABS_Y: {
            word address = absolute_y_address(&used_cycles, cpu);
            cpu->accumulator = read_byte(&used_cycles, cpu, address);
            set_negative_flag(cpu, cpu->accumulator);
            set_zero_flag(cpu, cpu->accumulator);
            break;
        }
        case LDA_X_IND: {
            word address = x_indirect_address(&used_cycles, cpu);
            cpu->accumulator = read_byte(&used_cycles, cpu, address);
            set_negative_flag(cpu, cpu->accumulator);
            set_zero_flag(cpu, cpu->accumulator);
            break;
        }
        case LDA_IND_Y: {
            word address = indirect_y_address(&used_cycles, cpu);
            cpu->accumulator = read_byte(&used_cycles, cpu, address);
            set_negative_flag(cpu, cpu->accumulator);
            set_zero_flag(cpu, cpu->accumulator);
            break;
        }
        case LDX_IMM: {
            cpu->x_register = fetch_byte(&used_cycles, cpu);
            set_negative_flag(cpu, cpu->x_register);
            set_zero_flag(cpu, cpu->x_register);
            break;
        }
        case LDX_ZPG: {
            word address = zeropage_address(&used_cycles, cpu);
            cpu->x_register = read_byte(&used_cycles, cpu, address);
            set_negative_flag(cpu, cpu->x_register);
            set_zero_flag(cpu, cpu->x_register);
            break;
        }
        case LDX_ZPG_Y: {
            word address = zeropage_y_address(&used_cycles, cpu);
            cpu->x_register = read_byte(&used_cycles, cpu, address);
            set_negative_flag(cpu, cpu->x_register);
            set_zero_flag(cpu, cpu->x_register);
            break;
        }
        case LDX_ABS: {
            word address = absolute_address(&used_cycles, cpu);
            cpu->x_register = read_byte(&used_cycles, cpu, address);
            set_negative_flag(cpu, cpu->x_register);
            set_zero_flag(cpu, cpu->x_register);
            break;
        }
        case LDX_ABS_Y: {
            word address = absolute_y_address(&used_cycles, cpu);
            cpu->x_register = read_byte(&used_cycles, cpu, address);
            set_negative_flag(cpu, cpu->x_register);
            set_zero_flag(cpu, cpu->x_register);
            break;
        }
        case LDY_IMM: {
            cpu->y_register = fetch_byte(&used_cycles, cpu);
            set_negative_flag(cpu, cpu->y_register);
            set_zero_flag(cpu, cpu->y_register);
            break;
        }
        case LDY_ZPG: {
            word address = zeropage_address(&used_cycles, cpu);
            cpu->y_register = read_byte(&used_cycles, cpu, address);
            set_negative_flag(cpu, cpu->y_register);
            set_zero_flag(cpu, cpu->y_register);
            break;
        }
        case LDY_ZPG_X: {
            word address = zeropage_x_address(&used_cycles, cpu);
            cpu->y_register = read_byte(&used_cycles, cpu, address);
            set_negative_flag(cpu, cpu->y_register);
            set_zero_flag(cpu, cpu->y_register);
            break;
        }
        case LDY_ABS: {
            word address = absolute_address(&used_cycles, cpu);
            cpu->y_register = read_byte(&used_cycles, cpu, address);
            set_negative_flag(cpu, cpu->y_register);
            set_zero_flag(cpu, cpu->y_register);
            break;
        }
        case LDY_ABS_X: {
            word address = absolute_x_address(&used_cycles, cpu);
            cpu->y_register = read_byte(&used_cycles, cpu, address);
            set_negative_flag(cpu, cpu->y_register);
            set_zero_flag(cpu, cpu->y_register);
            break;
        }
        case STA_ZPG: {
            word address = zeropage_address(&used_cycles, cpu);
            write_byte(&used_cycles, cpu, address, cpu->accumulator);
            break;
        }
        case STA_ZPG_X: {
            word address = zeropage_x_address(&used_cycles, cpu);
            write_byte(&used_cycles, cpu, address, cpu->accumulator);
            break;
        }
        case STA_ABS: {
            word address = absolute_address(&used_cycles, cpu);
            write_byte(&used_cycles, cpu, address, cpu->accumulator);
            break;
        }
        case STA_ABS_X: {
            word address = absolute_x_address_5(&used_cycles, cpu);
            write_byte(&used_cycles, cpu, address, cpu->accumulator);
            break;
        }
        case STA_ABS_Y: {
            word address = absolute_y_address(&used_cycles, cpu);
            // correct cyclecount if no page was crossed as STA_ABS_Y always needs 5 cycles
            if (used_cycles == 3) {
                used_cycles++;
            }
            write_byte(&used_cycles, cpu, address, cpu->accumulator);
            break;
        }
        case STA_X_IND: {
            word address = x_indirect_address(&used_cycles, cpu);
            write_byte(&used_cycles, cpu, address, cpu->accumulator);
            break;
        }
        case STA_IND_Y: {
            word address = indirect_y_address(&used_cycles, cpu);
            // correct cyclecount if no page was crossed as STA_IND_Y always needs 6 cycles
            if (used_cycles == 4) {
                used_cycles++;
            }
            write_byte(&used_cycles, cpu, address, cpu->accumulator);
            break;
        }
        case STX_ZPG: {
            word address = zeropage_address(&used_cycles, cpu);
            write_byte(&used_cycles, cpu, address, cpu->x_register);
            break;
        }
        case STX_ZPG_Y: {
            word address = zeropage_y_address(&used_cycles, cpu);
            write_byte(&used_cycles, cpu, address, cpu->x_register);
            break;
        }
        case STX_ABS: {
            word address = absolute_address(&used_cycles, cpu);
            write_byte(&used_cycles, cpu, address, cpu->x_register);
            break;
        }
        case STY_ZPG: {
            word address = zeropage_address(&used_cycles, cpu);
            write_byte(&used_cycles, cpu, address, cpu->y_register);
            break;
        }
        case STY_ZPG_X: {
            word address = zeropage_x_address(&used_cycles, cpu);
            write_byte(&used_cycles, cpu, address, cpu->y_register);
            break;
        }
        case STY_ABS: {
            word address = absolute_address(&used_cycles, cpu);
            write_byte(&used_cycles, cpu, address, cpu->y_register);
            break;
        }
        case TAX: {
            cpu->x_register = cpu->accumulator;
            used_cycles++;
            set_negative_flag(cpu, cpu->x_register);
            set_zero_flag(cpu, cpu->x_register);
            break;
        }
        case TAY: {
            cpu->y_register = cpu->accumulator;
            used_cycles++;
            set_negative_flag(cpu, cpu->y_register);
            set_zero_flag(cpu, cpu->y_register);
            break;
        }
        case TSX: {
            cpu->x_register = cpu->stack;
            used_cycles++;
            set_negative_flag(cpu, cpu->x_register);
            set_zero_flag(cpu, cpu->x_register);
            break;
        }
        case TXA: {
            cpu->accumulator = cpu->x_register;
            used_cycles++;
            set_negative_flag(cpu, cpu->accumulator);
            set_zero_flag(cpu, cpu->accumulator);
            break;
        }
        case TXS: {
            cpu->stack = cpu->x_register;
            used_cycles++;
            break;
        }
        case TYA: {
            cpu->accumulator = cpu->y_register;
            used_cycles++;
            set_negative_flag(cpu, cpu->accumulator);
            set_zero_flag(cpu, cpu->accumulator);
            break;
        }
        case PHA: {
            push_stack(&used_cycles, cpu, cpu->accumulator);
            break;
        }
        case PHP: {
            push_stack(&used_cycles, cpu, cpu->status);
            break;
        }
        case PLA: {
            cpu->accumulator = pull_stack(&used_cycles, cpu);
            set_negative_flag(cpu, cpu->accumulator);
            set_zero_flag(cpu, cpu->accumulator);
            break;
        }
        case PLP: {
            cpu->status = pull_stack(&used_cycles, cpu);
            break;
        }
        case DEC_ZPG: {
            word address = zeropage_address(&used_cycles, cpu);
            decrement(&used_cycles, cpu, address);
            break;
        }
        case DEC_ZPG_X: {
            word address = zeropage_x_address(&used_cycles, cpu);
            decrement(&used_cycles, cpu, address);
            break;
        }
        case DEC_ABS: {
            word address = absolute_address(&used_cycles, cpu);
            decrement(&used_cycles, cpu, address);
            break;
        }
        case DEC_ABS_X: {
            word address = absolute_x_address_5(&used_cycles, cpu);
            decrement(&used_cycles, cpu, address);
            break;
        }
        case DEX: {
            cpu->x_register--;
            used_cycles++;
            set_negative_flag(cpu, cpu->x_register);
            set_zero_flag(cpu, cpu->x_register);
            break;
        }
        case DEY: {
            cpu->y_register--;
            used_cycles++;
            set_negative_flag(cpu, cpu->y_register);
            set_zero_flag(cpu, cpu->y_register);
            break;
        }
        case INC_ZPG: {
            word address = zeropage_address(&used_cycles, cpu);
            increment(&used_cycles, cpu, address);
            break;
        }
        case INC_ZPG_X: {
            word address = zeropage_x_address(&used_cycles, cpu);
            increment(&used_cycles, cpu, address);
            break;
        }
        case INC_ABS: {
            word address = absolute_address(&used_cycles, cpu);
            increment(&used_cycles, cpu, address);
            break;
        }
        case INC_ABS_X: {
            word address = absolute_x_address_5(&used_cycles, cpu);
            increment(&used_cycles, cpu, address);
            break;
        }
        case INX: {
            cpu->x_register++;
            used_cycles++;
            set_negative_flag(cpu, cpu->x_register);
            set_zero_flag(cpu, cpu->x_register);
            break;
        }
        case INY: {
            cpu->y_register++;
            used_cycles++;
            set_negative_flag(cpu, cpu->y_register);
            set_zero_flag(cpu, cpu->y_register);
            break;
        }
        case ADC_IMM: {
            byte value = fetch_byte(&used_cycles, cpu);
            add(&used_cycles, cpu, value);
            break;
        }
        case ADC_ZPG: {
            word address = zeropage_address(&used_cycles, cpu);
            byte value = read_byte(&used_cycles, cpu, address);
            add(&used_cycles, cpu, value);
            break;
        }
        case ADC_ZPG_X: {
            word address = zeropage_x_address(&used_cycles, cpu);
            byte value = read_byte(&used_cycles, cpu, address);
            add(&used_cycles, cpu, value);
            break;
        }
        case ADC_ABS: {
            word address = absolute_address(&used_cycles, cpu);
            byte value = read_byte(&used_cycles, cpu, address);
            add(&used_cycles, cpu, value);
            break;
        }
        case ADC_ABS_X: {
            word address = absolute_x_address(&used_cycles, cpu);
            byte value = read_byte(&used_cycles, cpu, address);
            add(&used_cycles, cpu, value);
            break;
        }
        case ADC_ABS_Y: {
            word address = absolute_y_address(&used_cycles, cpu);
            byte value = read_byte(&used_cycles, cpu, address);
            add(&used_cycles, cpu, value);
            break;
        }
        case ADC_X_IND: {
            word address = x_indirect_address(&used_cycles, cpu);
            byte value = read_byte(&used_cycles, cpu, address);
            add(&used_cycles, cpu, value);
            break;
        }
        case ADC_IND_Y: {
            word address = indirect_y_address(&used_cycles, cpu);
            byte value = read_byte(&used_cycles, cpu, address);
            add(&used_cycles, cpu, value);
            break;
        }
        case SBC_IMM: {
            byte value = fetch_byte(&used_cycles, cpu);
            sub(&used_cycles, cpu, value);
            break;
        }
        case SBC_ZPG: {
            word address = zeropage_address(&used_cycles, cpu);
            byte value = read_byte(&used_cycles, cpu, address);
            sub(&used_cycles, cpu, value);
            break;
        }
        case SBC_ZPG_X: {
            word address = zeropage_x_address(&used_cycles, cpu);
            byte value = read_byte(&used_cycles, cpu, address);
            sub(&used_cycles, cpu, value);
            break;
        }
        case SBC_ABS: {
            word address = absolute_address(&used_cycles, cpu);
            byte value = read_byte(&used_cycles, cpu, address);
            sub(&used_cycles, cpu, value);
            break;
        }
        case SBC_ABS_X: {
            word address = absolute_x_address(&used_cycles, cpu);
            byte value = read_byte(&used_cycles, cpu, address);
            sub(&used_cycles, cpu, value);
            break;
        }
        case SBC_ABS_Y: {
            word address = absolute_y_address(&used_cycles, cpu);
            byte value = read_byte(&used_cycles, cpu, address);
            sub(&used_cycles, cpu, value);
            break;
        }
        case SBC_X_IND: {
            word address = x_indirect_address(&used_cycles, cpu);
            byte value = read_byte(&used_cycles, cpu, address);
            sub(&used_cycles, cpu, value);
            break;
        }
        case SBC_IND_Y: {
            word address = indirect_y_address(&used_cycles, cpu);
            byte value = read_byte(&used_cycles, cpu, address);
            sub(&used_cycles, cpu, value);
            break;
        }
        case AND_IMM: {
            byte value = fetch_byte(&used_cycles, cpu);
            and(&used_cycles, cpu, value);
            break;
        }
        case AND_ZPG: {
            word address = zeropage_address(&used_cycles, cpu);
            byte value = read_byte(&used_cycles, cpu, address);
            and(&used_cycles, cpu, value);
            break;
        }
        case AND_ZPG_X: {
            word address = zeropage_address_x(&used_cycles, cpu);
            byte value = read_byte(&used_cycles, cpu, address);
            and(&used_cycles, cpu, value);
            break;
        }
        case AND_ABS: {
            word address = absolute_address(&used_cycles, cpu);
            byte value = read_byte(&used_cycles, cpu, address);
            and(&used_cycles, cpu, value);
            break;
        }
        case AND_ABS_X: {
            word address = absolute_x_address(&used_cycles, cpu);
            byte value = read_byte(&used_cycles, cpu, address);
            and(&used_cycles, cpu, value);
            break;
        }
        case AND_ABS_Y: {
            word address = absolute_y_address(&used_cycles, cpu);
            byte value = read_byte(&used_cycles, cpu, address);
            and(&used_cycles, cpu, value);
            break;
        }
        case AND_X_IND: {
            word address = x_indirect_address(&used_cycles, cpu);
            byte value = read_byte(&used_cycles, cpu, address);
            and(&used_cycles, cpu, value);
            break;
        }
        case AND_IND_Y: {
            word address = indirect_y_address(&used_cycles, cpu);
            byte value = read_byte(&used_cycles, cpu, address);
            and(&used_cycles, cpu, value);
            break;
        }
        case EOR_IMM: {
            byte value = fetch_byte(&used_cycles, cpu);
            eor(&used_cycles, cpu, value);
            break;
        }
        case EOR_ZPG: {
            word address = zeropage_address(&used_cycles, cpu);
            byte value = read_byte(&used_cycles, cpu, address);
            eor(&used_cycles, cpu, value);
            break;
        }
        case EOR_ZPG_X: {
            word address = zeropage_address_x(&used_cycles, cpu);
            byte value = read_byte(&used_cycles, cpu, address);
            eor(&used_cycles, cpu, value);
            break;
        }
        case EOR_ABS: {
            word address = absolute_address(&used_cycles, cpu);
            byte value = read_byte(&used_cycles, cpu, address);
            eor(&used_cycles, cpu, value);
            break;
        }
        case EOR_ABS_X: {
            word address = absolute_x_address(&used_cycles, cpu);
            byte value = read_byte(&used_cycles, cpu, address);
            eor(&used_cycles, cpu, value);
            break;
        }
        case EOR_ABS_Y: {
            word address = absolute_y_address(&used_cycles, cpu);
            byte value = read_byte(&used_cycles, cpu, address);
            eor(&used_cycles, cpu, value);
            break;
        }
        case EOR_X_IND: {
            word address = x_indirect_address(&used_cycles, cpu);
            byte value = read_byte(&used_cycles, cpu, address);
            eor(&used_cycles, cpu, value);
            break;
        }
        case EOR_IND_Y: {
            word address = indirect_y_address(&used_cycles, cpu);
            byte value = read_byte(&used_cycles, cpu, address);
            eor(&used_cycles, cpu, value);
            break;
        }
        case ORA_IMM: {
            byte value = fetch_byte(&used_cycles, cpu);
            or(&used_cycles, cpu, value);
            break;
        }
        case ORA_ZPG: {
            word address = zeropage_address(&used_cycles, cpu);
            byte value = read_byte(&used_cycles, cpu, address);
            or(&used_cycles, cpu, value);
            break;
        }
        case ORA_ZPG_X: {
            word address = zeropage_address_x(&used_cycles, cpu);
            byte value = read_byte(&used_cycles, cpu, address);
            or(&used_cycles, cpu, value);
            break;
        }
        case ORA_ABS: {
            word address = absolute_address(&used_cycles, cpu);
            byte value = read_byte(&used_cycles, cpu, address);
            or(&used_cycles, cpu, value);
            break;
        }
        case ORA_ABS_X: {
            word address = absolute_x_address(&used_cycles, cpu);
            byte value = read_byte(&used_cycles, cpu, address);
            or(&used_cycles, cpu, value);
            break;
        }
        case ORA_ABS_Y: {
            word address = absolute_y_address(&used_cycles, cpu);
            byte value = read_byte(&used_cycles, cpu, address);
            or(&used_cycles, cpu, value);
            break;
        }
        case ORA_X_IND: {
            word address = x_indirect_address(&used_cycles, cpu);
            byte value = read_byte(&used_cycles, cpu, address);
            or(&used_cycles, cpu, value);
            break;
        }
        case ORA_IND_Y: {
            word address = indirect_y_address(&used_cycles, cpu);
            byte value = read_byte(&used_cycles, cpu, address);
            or(&used_cycles, cpu, value);
            break;
        }
    }
    cpu->cycles += used_cycles;
    return used_cycles;
}

void reset(cpu_t* cpu, memory_t* memory) {
    if (memory != NULL) {
        cpu->memory = memory;
    }
    cpu->program_counter = 0x0000;
    cpu->stack = 0xFD;
    cpu->status = UNUSED_MASK;
    cpu->cycles = 7;
    byte low_pc = read_memory(cpu->memory, 0xFFFC);
    byte high_pc = read_memory(cpu->memory, 0xFFFD);
    cpu->program_counter = low_pc | ((word)high_pc << 8);
}

word zeropage_address(int* cycles, cpu_t* cpu) {
    byte address = fetch_byte(cycles, cpu);
    return address;
}

word zeropage_x_address(int* cycles, cpu_t* cpu) {
    byte address = fetch_byte(cycles, cpu);
    address += cpu->x_register;
    (*cycles)++;
    return address;
}

word zeropage_y_address(int* cycles, cpu_t* cpu) {
    byte address = fetch_byte(cycles, cpu);
    address += cpu->y_register;
    (*cycles)++;
    return address;
}

word absolute_address(int* cycles, cpu_t* cpu) {
    word address = fetch_byte(cycles, cpu);
    address |= (((word)fetch_byte(cycles, cpu)) << 8);
    return address;
}

word absolute_x_address(int* cycles, cpu_t* cpu) {
    word address = fetch_byte(cycles, cpu);
    address += cpu->x_register;
    if (address >= 0x100) {
        (*cycles)++;
    }
    address += (((word)fetch_byte(cycles, cpu)) << 8);
    return address;
}

word absolute_x_address_5(int* cycles, cpu_t* cpu) {
    word address = fetch_byte(cycles, cpu);
    address += cpu->x_register;
    (*cycles)++;
    address += (((word)fetch_byte(cycles, cpu)) << 8);
    return address;
}

word absolute_y_address(int* cycles, cpu_t* cpu) {
    word address = fetch_byte(cycles, cpu);
    address += cpu->y_register;
    if (address >= 0x100) {
        (*cycles)++;
    }
    address += (((word)fetch_byte(cycles, cpu)) << 8);
    return address;
}

word indirect_address(int* cycles, cpu_t* cpu) {
    word indirect_address = absolute_address(cycles, cpu);
    word address = read_byte(cycles, cpu, indirect_address);
    address |= (((word)read_byte(cycles, cpu, indirect_address + 1)) << 8);
    return address;
}

word x_indirect_address(int* cycles, cpu_t* cpu) {
    byte zeropage_address = zeropage_x_address(cycles, cpu);
    word address = read_byte(cycles, cpu, zeropage_address);
    address |= (((word)read_byte(cycles, cpu, zeropage_address + 1)) << 8);
    return address;
}

word indirect_y_address(int* cycles, cpu_t* cpu) {
    byte zeropage_addr = zeropage_address(cycles, cpu);
    word address = read_byte(cycles, cpu, zeropage_addr);
    address += cpu->y_register;
    if (address >= 0x100) {
        (*cycles)++;
    }
    address += (((word)read_byte(cycles, cpu, zeropage_addr + 1)) << 8);
    return address;
}

sbyte relative_address(int* cycles, cpu_t* cpu) {
    byte offset = fetch_byte(cycles, cpu);
    return (sbyte)offset;
}

void increment(int* cycles, cpu_t* cpu, word address) {
    byte data = read_byte(cycles, cpu, address);
    data++;
    (*cycles)++;
    set_negative_flag(cpu, data);
    set_zero_flag(cpu, data);
    write_byte(cycles, cpu, address, data);
}

void decrement(int* cycles, cpu_t* cpu, word address) {
    byte data = read_byte(cycles, cpu, address);
    data--;
    (*cycles)++;
    set_negative_flag(cpu, data);
    set_zero_flag(cpu, data);
    write_byte(cycles, cpu, address, data);
}

void add(int* cycles, cpu_t* cpu, byte value) {
    word result = cpu->accumulator;
    bool same_sign_operands = (cpu->accumulator & 0x80) ^ (value & 0x80) == 0;
    result += value;
    result += (get_status_flag(cpu, CARRY_MASK) ? 1 : 0);

    if (result > 0xFF) {
        set_carry_flag(cpu);
    } else {
        clear_carry_flag(cpu);
    }

    if (same_sign_operands) {
        if ((value & 0x80) ^ (result & 0x80) != 0) {  // different signs of result and operands
            set_overflow_flag(cpu);
        } else {
            clear_overflow_flag(cpu);
        }
    }
    cpu->accumulator = (byte)(result & 0xFF);
    set_negative_flag(cpu, cpu->accumulator);
    set_zero_flag(cpu, cpu->accumulator);
}

// the +1 for negating the value comes from the carry
// that has to be set by the programmer
void sub(int* cycles, cpu_t* cpu, byte value) {
    add(cycles, cpu, ~value);
}

void and(int* cycles, cpu_t* cpu, byte value) {
    cpu->accumulator = cpu->accumulator & value;
    set_negative_flag(cpu, cpu->accumulator);
    set_zero_flag(cpu, cpu->accumulator);
}

void eor(int* cycles, cpu_t* cpu, byte value) {
    cpu->accumulator = cpu->accumulator ^ value;
    set_negative_flag(cpu, cpu->accumulator);
    set_zero_flag(cpu, cpu->accumulator);
}

void or(int* cycles, cpu_t* cpu, byte value) {
    cpu->accumulator = cpu->accumulator | value;
    set_negative_flag(cpu, cpu->accumulator);
    set_zero_flag(cpu, cpu->accumulator);
}

void push_stack(int* cycles, cpu_t* cpu, byte value) {
    word address = 0x100 | cpu->stack;
    write_byte(cycles, cpu, address, value);
    cpu->stack--;
    (*cycles)++;
}

byte pull_stack(int* cycles, cpu_t* cpu) {
    cpu->stack++;
    *cycles += 2;
    word address = 0x100 | cpu->stack;
    return read_byte(cycles, cpu, address);
}

void set_carry_flag(cpu_t* cpu) {
    cpu->status |= CARRY_MASK;
}

void clear_carry_flag(cpu_t* cpu) {
    cpu->status &= (~CARRY_MASK);
}

void set_overflow_flag(cpu_t* cpu) {
    cpu->status |= OVERFLOW_MASK;
}

void clear_overflow_flag(cpu_t* cpu) {
    cpu->status &= (~OVERFLOW_MASK);
}

void set_negative_flag(cpu_t* cpu, byte value) {
    if ((value & NEGATIVE_MASK) != 0) {
        cpu->status |= NEGATIVE_MASK;
    } else {
        cpu->status &= (~NEGATIVE_MASK);
    }
}

void set_zero_flag(cpu_t* cpu, byte value) {
    if (value == 0) {
        cpu->status |= ZERO_MASK;
    } else {
        cpu->status &= (~ZERO_MASK);
    }
}

bool get_status_flag(cpu_t* cpu, byte flag) {
    return (cpu->status & flag) != 0;
}