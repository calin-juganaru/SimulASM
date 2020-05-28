#pragma once

#include "pair.h"
#include "instructions.h"

#define DIE(cond) if (cond == ERROR) error()
#define exit_err() error(); return

using pointer = byte*;
using ref = byte&;
using cref = const ref;
using cvref = volatile cref;

// ============================================================================

function error()
{
    for (auto i = 0; i < 3; ++i)
    {
        module.setLEDs(255);
        delay(100);
        module.setLEDs(0);
        delay(100);
    }
}

// ============================================================================

function push_mem(auto value)
{
    SR = (SR + 1) % 32;
    memory[SR] = value;
}

// ============================================================================

function pop_mem()
{
    auto value = memory[IP];
    IP = (IP + 1) % 32;
    return value;
}

// ============================================================================

function pop_stack()
{
    auto value = memory[SR];
    SR = (SR - 1) % 32;
    return value;
}

// ============================================================================

function print_segment()
{
    module.setDisplayToString(segment_text.c_str());
}

// ============================================================================

function clear_segment()
{
    segment_text = "        ";
    print_segment();
}

// ============================================================================

function get_key()
{
    auto aux = 0;
    while (!aux)
        aux = numpad.getKey();
    return aux - 1;
}

// ============================================================================

function get_button()
{
    auto aux = byte();
    while (!aux)
        aux = module.getButtons();

    for (auto i = 0; i < 8; ++i)
        if (aux & (1 << i))
          return byte(1 << i);

    return ERROR;
}

// ============================================================================

constexpr auto wait_button = [](const byte& button)
{
    auto aux = module.getButtons();
    while (!(aux & button))
        aux = module.getButtons();
    return aux;
};

// ============================================================================

function read_value(byte base = 10)
{
    auto value = byte();

    while (get_button() != ENTER)
    {
        auto aux = get_key();
        value = value * base + aux;
        auto index = 4;
        for (auto i: String(value))
            segment_text[index++] = i;

        print_segment();
    }

    return value;
}

// ============================================================================

function get_reg()
{
    auto index = read_value();
    while (index > 3)
    {
        error();
        index = read_value();
    }

    return index;
}

// ============================================================================

function get_mem()
{
    auto index = read_value();
    while (index > 31)
    {
        error();
        index = read_value();
    }

    return index;
}

// ============================================================================
