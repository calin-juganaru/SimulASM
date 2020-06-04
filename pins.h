#pragma once

#include <Keypad.h>
#include <TM1638.h>
#include <LedControl.h>
#include <LiquidCrystal_I2C.h>

// ============================================================================

#define function static inline auto
#define constant constexpr auto

// ============================================================================

constant MEM_DATA_IN = 48;
constant MEM_LOAD    = 46;
constant MEM_CLOCK   = 44;

constant REG_DATA_IN = 23;
constant REG_LOAD    = 52;
constant REG_CLOCK   = 50;

constant TM1638_DATA   = 2;
constant TM1638_CLOCK  = 3;
constant TM1638_STROBE = 4;

constant I2C_ADDR = 0x3F;
constant LCD_ROWS = 20;
constant LCD_COLS = 4;

// ============================================================================

auto mem_display = LedControl(MEM_DATA_IN, MEM_CLOCK, MEM_LOAD, 4);
auto reg_display = LedControl(REG_DATA_IN, REG_CLOCK, REG_LOAD, 1);
auto lcd_display = LiquidCrystal_I2C(I2C_ADDR, LCD_ROWS, LCD_COLS);
auto module = TM1638(TM1638_DATA, TM1638_CLOCK, TM1638_STROBE);

// ============================================================================

byte ROW_PIN[3][4] =
{
    {28, 26, 24, 22},
    {29, 42, 40, 38},
    {45, 43, 41, 39}
};

byte COL_PIN[3][4] =
{
    {30, 34, 32, 36},
    {31, 33, 35, 37},
    {47, 49, 51, 53}
};

// ============================================================================

char keys[2][4][4] =
{
    {
        {4, 8, 12, 16},
        {3, 7, 11, 15},
        {2, 6, 10, 14},
        {1, 5,  9, 13}
    },
    {
        {20, 24, 28, 32},
        {19, 23, 27, 31},
        {18, 22, 26, 30},
        {17, 21, 25, 29}
    }
};

// ============================================================================

Keypad cmd_pads[] =
{
    Keypad(makeKeymap(keys[0]), ROW_PIN[0], COL_PIN[0], 4, 4),
    Keypad(makeKeymap(keys[1]), ROW_PIN[1], COL_PIN[1], 4, 4)
};

auto numpad = Keypad(makeKeymap(keys[0]), ROW_PIN[2], COL_PIN[2], 4, 4);

// ============================================================================

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

const String buttons[] =
{
    "BIN", "OCT", "DEC", "HEX",
    "REG", "MEM", "IMD", "ENT"
};

// ============================================================================
