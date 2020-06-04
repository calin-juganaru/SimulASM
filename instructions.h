#pragma once

#include "pins.h"

// ============================================================================

constant _AND = 1;
constant _OR  = 2;
constant _NOT = 3;
constant _XOR = 4;

constant _ADD = 5;
constant _SUB = 6;
constant _MUL = 7;
constant _DIV = 8;

constant _INC = 9;
constant _DEC = 10;
constant _NEG = 11;
constant _MOD = 12;

constant _PSH = 13;
constant _POP = 14;
constant _SHL = 15;
constant _SHR = 16;

constant _MOV = 17;
constant _LBL = 18;
constant _NOP = 19;
constant _RET = 20;

constant _CMP = 21;
constant _JMP = 22;
constant _JE  = 23;
constant _JNE = 24;

constant _JL  = 25;
constant _JLE = 26;
constant _JG  = 27;
constant _JGE = 28;

constant _JC  = 29;
constant _JO  = 30;
constant _JS  = 31;
constant _JZ  = 32;

// ============================================================================

constant BTN_BIN = 1 << 0;
constant BTN_OCT = 1 << 1;
constant BTN_DEC = 1 << 2;
constant BTN_HEX = 1 << 3;

constant BTN_REG = 1 << 4;
constant BTN_MEM = 1 << 5;
constant BTN_IMD = 1 << 6;

constant ENTER = 1 << 7;

constant ERROR = byte(-1);

// ============================================================================

constant REG = byte(B100);
constant MEM = byte(B010);
constant IMD = byte(B001);

constant REG_REG = byte(B000);
constant MEM_IMD = byte(B011);
constant REG_IMD = byte(B101);
constant REG_MEM = byte(B110);
constant MEM_REG = byte(B111);

// ============================================================================

byte memory[32], registers[8];

constexpr byte bits[] = {0, 1, 2, 3, 4, 5, 6, 7};

auto& [ZR, LS, GR, CR, PR, AO, SO, SG] = bits;
auto& [RA, RB, RC, RD, SR, BP, IP, FR] = registers;

auto segment_text = String("        ");

// ============================================================================

function get_instruction(const char& c)
{
    if (c < 0 || c > 'F')
        return String("Err0r");
    return instructions[c];
}

// ============================================================================

function set_memory_bit(int row, byte col, boolean value = true)
{
    mem_display.setLed(row / 8, col, 7 + 8 * (row / 8) - row, value);
}

// ============================================================================

function set_memory_byte(int index)
{
    auto value = memory[index];
    for (auto col = 0; col < 8; ++col, value >>= 1)
        set_memory_bit(index, col, value % 2);
}

// ============================================================================

function set_register_bit(int row, byte col, boolean value = true)
{
    reg_display.setLed(0, 7 - row, col, value);
}

// ============================================================================

function display_register(byte index)
{
    auto value = registers[index];
    for (auto i = 0; i < 8; ++i, value >>= 1)
        set_register_bit(index, i, value % 2);
}

// ============================================================================