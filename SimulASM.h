#pragma once

#include "parsing.h"
#include "execution.h"

// ============================================================================

inline void set_memory_bit(int row, byte col, boolean value = true)
{
    mem_display.setLed(row / 8, col, 7 + 8 * (row / 8) - row, value);
}

// ============================================================================

inline void set_memory_byte(int index)
{
    auto value = memory[index];
    for (auto col = 0; col < 8; ++col, value >>= 1)
        set_memory_bit(index, col, value % 2);
}

// ============================================================================

inline void set_register_bit(int row, byte col, boolean value = true)
{
    reg_display.setLed(0, 7 - row, col, value);
}

// ============================================================================

inline void display_register(byte index)
{
    auto value = registers[index];
    for (auto i = 0; i < 8; ++i, value >>= 1)
        set_register_bit(index, i, value % 2);
}

// ============================================================================

void fancy_leds()
{
    for (auto x = 0; x < 224; ++x)
    {
        // --------------------------------------------------------------------

        digitalWrite(LED_BUILTIN, HIGH);
        for (auto row = 0; row < 8; ++row)
            for (auto col = 0; col < 8; ++col)
                if ((registers[row] + x) & (byte(1) << col))
                    set_register_bit(row, col);

        // --------------------------------------------------------------------

        digitalWrite(LED_BUILTIN, LOW);
        for (auto row = 0; row < 32; ++row)
            for (auto col = 0; col < 8; ++col)
                if ((memory[row] + x) & (byte(1) << col))
                    set_memory_bit(row, col);

        // --------------------------------------------------------------------

        digitalWrite(LED_BUILTIN, HIGH);
        for (auto row = 0; row < 8; ++row)
            for (auto col = 0; col < 8; ++col)
                if ((registers[row] + x) & (byte(1) << col))
                    set_register_bit(row, col, false);

        // --------------------------------------------------------------------

        digitalWrite(LED_BUILTIN, LOW);
        for (auto row = 0; row < 32; ++row)
            for (auto col = 0; col < 8; ++col)
                if ((memory[row] + x) & (byte(1) << col))
                    set_memory_bit(row, col, false);

        // --------------------------------------------------------------------
    }
}

// ============================================================================
