#pragma once

#include "pins.h"

// ============================================================================

//#undef DEC

#define function static inline auto
#define constant constexpr auto
#define var auto

#define parse_op(X, Y) case _##X: parse_##Y(); break
#define exec_op(X, Y) case _##X: exec_##Y(types); break
#define break_if(cond) if (cond) break

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
constant _RET = 19;
constant _CMP = 20;

constant _JMP = 21;
constant _JE  = 22;
constant _JNE = 23;
constant _JL  = 24;

constant _JLE = 25;
constant _JG  = 26;
constant _JGE = 27;
constant _JC  = 28;

constant _JO  = 29;
constant _JS  = 30;
constant _JZ  = 31;

constant _NOP = 0;

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

constant _REG = byte(B100);
constant _MEM = byte(B010);
constant _IMD = byte(B001);

// ============================================================================

constant _REG_REG = byte(B000);
constant _MEM_IMD = byte(B011);
constant _REG_IMD = byte(B101);
constant _REG_MEM = byte(B110);
constant _MEM_REG = byte(B111);

// ============================================================================

enum class Operands
{
    REG_REG = B000,
    IMD     = B001,
    MEM     = B010,
    MEM_IMD = B011,
    REG     = B100,
    REG_IMD = B101,
    REG_MEM = B110,
    MEM_REG = B111
};

// ============================================================================

byte memory[32];
byte registers[8];

auto segment_text = String("        ");

auto& RA = registers[0];
auto& RB = registers[1];
auto& RC = registers[2];
auto& RD = registers[3];

auto& SR = registers[4];
auto& BP = registers[5];
auto& IP = registers[6];
auto& FR = registers[7];

// ============================================================================

constant ZR = byte(1 << 0);
constant LS = byte(1 << 1);
constant GR = byte(1 << 2);
constant CR = byte(1 << 3);
constant PR = byte(1 << 4);
constant AO = byte(1 << 5);
constant SO = byte(1 << 6);
constant SG = byte(1 << 7);

// ============================================================================


constant is_digit = [](const char& c)
{
    return ((c >= '0' && c <= '9') || ((c >= 'A' && c <= 'F')));
};

// ============================================================================

constant is_instruction = [](const char& c)
{
    return (c > 0 && c < 32);
};

// ============================================================================

constant get_instruction = [](const char& c)
{
    if (c < 0 || c > 'F')
        return String("Err0r");
    return instructions[c];
};

// ============================================================================
