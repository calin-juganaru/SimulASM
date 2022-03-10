#pragma once

#include <LedControl.h>

#include "constants.h"

// =============================================================================

constant MEM_DATA_IN = 48;
constant MEM_LOAD    = 46;
constant MEM_CLOCK   = 44;

constant REG_DATA_IN = 23;
constant REG_LOAD    = 52;
constant REG_CLOCK   = 50;

// =============================================================================

const auto mem_display = LedControl(MEM_DATA_IN, MEM_CLOCK, MEM_LOAD, 4);
const auto reg_display = LedControl(REG_DATA_IN, REG_CLOCK, REG_LOAD, 1);

// =============================================================================

byte memory[32], registers[8];

constexpr byte bits[] = {0, 1, 2, 3, 4, 5, 6, 7};

// [zero, less, greater, carry, parity, arithmetic overflow, stack overflow, sign]
auto& [ZR, LS, GR, CR, PR, AO, SO, SG] = bits;

auto& [RA, RB, RC, RD, SR, BP, IP, FLAGS] = registers;

// =============================================================================

function push_mem(cref value)
{
    if (SR == 31) bitSet(FLAGS, SO);
    SR = (SR + 1) % 32;
    return memory[SR] = value;
}

// =============================================================================

function pop_mem()
{
    auto value = memory[IP];
    if (IP == 31) bitSet(FLAGS, SO);
    IP = (IP + 1) % 32;
    return value;
}

// =============================================================================

function pop_stack()
{
    auto value = memory[SR];
    if (SR == 0) bitSet(FLAGS, SO);
    SR = (SR - 1) % 32;
    return value;
}

// =============================================================================

function set_memory_bit(int row, byte col, boolean value = true)
{
    mem_display.setLed(row / 8, col, 7 + 8 * (row / 8) - row, value);
}

// =============================================================================


function set_memory_byte(int index)
{
    auto value = memory[index];
    for (auto col = 0; col < 8; ++col, value >>= 1)
        set_memory_bit(index, col, value % 2);
}

// =============================================================================

function set_register_bit(int row, byte col, boolean value = true)
{
    reg_display.setLed(0, 7 - row, col, value);
}

// =============================================================================

function display_register(byte index)
{
    auto value = registers[index];
    for (auto i = 0; i < 8; ++i, value >>= 1)
        set_register_bit(index, i, value % 2);
}

// =============================================================================