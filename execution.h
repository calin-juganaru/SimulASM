#pragma once

#include "instructions.h"

// =============================================================================

function execute(byte op_code)
{
    static constexpr func_t functions[] =
    {
        _and, _or,  _not, _xor,
        _add, _sub, _mul, _div,
        _inc, _dec, _neg, _mod,
        _psh, _pop, _shl, _shr,

        _mov, _lbl, _nop, _ret,
        _cmp, _jmp, _je,  _jne,
        _jl,  _jle, _jg,  _jge,
        _jc,  _jo,  _js,  _jz
    };

    auto operands = op_code & 7;
    auto instruction = op_code >> 3;

    if (instruction > 31) { error(); return; }
    functions[instruction](operands);
}

// =============================================================================

function run_code()
{
    error(); error();
    wait_button(ENTER);
    clear_segment();

    RA = RB = RC = RD = BP = IP = FLAGS = 0;

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

// =============================================================================