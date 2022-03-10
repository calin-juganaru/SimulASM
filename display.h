#pragma once

#include <TM1638.h>
#include <LiquidCrystal_I2C.h>

#include "utilities.h"
#include "constants.h"

// =============================================================================

constant TM1638_DATA   = 2;
constant TM1638_CLOCK  = 3;
constant TM1638_STROBE = 4;

constant I2C_ADDR = 0x3F;
constant LCD_ROWS = 20;
constant LCD_COLS = 4;

// =============================================================================

auto segment_text = String(EMPTY_LINE);
auto lcd_i2c = LiquidCrystal_I2C(I2C_ADDR, LCD_ROWS, LCD_COLS);
auto module = TM1638(TM1638_DATA, TM1638_CLOCK, TM1638_STROBE);

// =============================================================================

function error()
{
    for (auto i = 0; i < 9; ++i)
    {
        module.setLEDs(ERROR);
        delay(100);
        module.setLEDs(NULL);
        delay(100);
    }
}

// =============================================================================

function lcd_print(string text)
{
    static auto row = 0;
    static auto col = 0;

    if (col > 15 || text == "\n")
    {
        col = 0;
        row = (row + 1) % 4;
        lcd_i2c.setCursor(col, row);
        lcd_i2c.print(EMPTY_LINE);
    }

    lcd_i2c.setCursor(col, row);
    lcd_i2c.print(text);
    col += text.length();
}

// =============================================================================

function print_segment() { module.setDisplayToString(segment_text.c_str()); }

// =============================================================================

function clear_segment() { segment_text = EMPTY_LINE; print_segment(); }

// =============================================================================