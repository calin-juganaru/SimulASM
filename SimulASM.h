#pragma once

#include "parsing.h"
#include "execution.h"

// ============================================================================

function run_code()
{
    error(); error();
    wait_button(ENTER);
    clear_segment();

    RA = RB = RC = RD = BP = IP = FR = 0;

    for (auto i = 0; i < 8; ++i)
        display_register(i);

    while (true)
    {
        auto op_code = pop_mem();
        execute(op_code);

        for (auto i = 0; i < 32; ++i)
            set_memory_byte(i);

        for (auto i = 0; i < 8; ++i)
            display_register(i);

        wait_button(ENTER);
    }
}

// ============================================================================
