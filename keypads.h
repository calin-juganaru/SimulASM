#pragma once

#include <Keypad.h>

// =============================================================================

constexpr byte ROW_PIN[3][4] =
{
    {28, 26, 24, 22},
    {29, 42, 40, 38},
    {45, 43, 41, 39}
};

constexpr byte COL_PIN[3][4] =
{
    {30, 34, 32, 36},
    {31, 33, 35, 37},
    {47, 49, 51, 53}
};

// =============================================================================

constexpr char keys[2][4][4] =
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

// =============================================================================

const Keypad cmd_pads[] =
{
    Keypad(makeKeymap(keys[0]), ROW_PIN[0], COL_PIN[0], 4, 4),
    Keypad(makeKeymap(keys[1]), ROW_PIN[1], COL_PIN[1], 4, 4)
};

const auto numpad = Keypad(makeKeymap(keys[0]), ROW_PIN[2], COL_PIN[2], 4, 4);

// =============================================================================

function get_key()
{
    auto aux = 0;
    while (!aux)
        aux = numpad.getKey();
    return aux - 1;
}

// =============================================================================

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

// =============================================================================

function wait_button(cref button)
{
    auto aux = module.getButtons();
    while (!(aux & button))
        aux = module.getButtons();
    return aux;
}

// =============================================================================

function read_value(byte base = 10)
{
    auto value = byte();

    while (get_button() != ENTER)
    {
        auto aux = get_key();
        lcd_print(string(aux));
        value = value * base + aux;
        auto index = 4;
        for (auto i: String(value))
            segment_text[index++] = i;

        print_segment();
    }

    return value;
}

// =============================================================================

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

// =============================================================================

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

// =============================================================================