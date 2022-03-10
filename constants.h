#pragma once

#include "utilities.h"

// =============================================================================

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

// =============================================================================

constant BTN_BAK = 1 << 0;
constant BTN_BIN = 1 << 1;
constant BTN_DEC = 1 << 2;
constant BTN_HEX = 1 << 3;

constant BTN_REG = 1 << 4;
constant BTN_MEM = 1 << 5;
constant BTN_IMD = 1 << 6;

constant ENTER = 1 << 7;

constant ERROR = byte(-1);

// =============================================================================

constant REG = byte(B100);
constant MEM = byte(B010);
constant IMD = byte(B001);

constant REG_REG = byte(B000);
constant MEM_IMD = byte(B011);
constant REG_IMD = byte(B101);
constant REG_MEM = byte(B110);
constant MEM_REG = byte(B111);

// =============================================================================

const String buttons[] = {"BAK", "BIN", "DEC", "HEX", "REG", "MEM", "IMD", "ENT"};

// =============================================================================

const String instructions[] =
{
    "",

    "AND", "OR ", "NOT", "XOR",
    "ADD", "SUB", "MUL", "DIV",
    "INC", "DEC", "NEG", "MOD",
    "PSH", "POP", "SHL", "SHR",

    "MOV", "LBL", "NOP", "RET",
    "CMP", "JMP", "JE ", "JNE",
    "JL ", "JLE", "JG ", "JGE",
    "JC ", "JO ", "JS ", "JZ "
};

// =============================================================================
