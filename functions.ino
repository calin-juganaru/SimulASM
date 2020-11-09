#include "functions.h"

// ======================================================================================

template <typename Op>
function byte alu_op1(_params, Op op)
{
    auto x = pop_mem();

    switch (op_code)
    {
        case REG: return op(registers[x]);
        case MEM: return op(memory[x]);
        case IMD: return op(x);
        default: exit_err();
    }
}

// ======================================================================================

template <typename Op>
function byte alu_op2(byte op_code, Op op)
{
    auto x = pop_mem(), y = pop_mem();

    switch (op_code)
    {
        case REG_REG: return op(registers[x], registers[y]);
        case REG_MEM: return op(registers[x], memory[y]);
        case MEM_REG: return op(memory[x], registers[y]);
        case REG_IMD: return op(registers[x], y);
        case MEM_IMD: return op(memory[x], y);
        default: exit_err();
    }
}

// ======================================================================================

function byte _and(_params) { return alu_op2(op_code, [](ref a, cref b) { return a &= b; }); }

// ======================================================================================

function byte _or(_params) { return alu_op2(op_code, [](ref a, cref b) { return a |= b; }); }

// ======================================================================================

function byte _not(_params) { return alu_op1(op_code, [](ref x) { return ~x; }); }

// ======================================================================================

function byte _xor(_params) { return alu_op2(op_code, [](ref a, cref b) { return a ^= b; }); }

// ======================================================================================

function byte _add(_params) { return alu_op2(op_code, [](ref a, cref b) { return a += b; }); }

// ======================================================================================

function byte _sub(_params) { return alu_op2(op_code, [](ref a, cref b) { return a -= b; }); }

// ======================================================================================

function byte _mul(_params) {}

// ======================================================================================

function byte _div(_params) {}

// ======================================================================================

function byte _inc(_params) { return alu_op1(op_code, [](ref x) { return ++x; }); }

// ======================================================================================

function byte _dec(_params) { return alu_op1(op_code, [](ref x) { return --x; }); }

// ======================================================================================

function byte _neg(_params) { return alu_op1(op_code, [](ref x) { return x = -x; }); }

// ======================================================================================

function byte _mod(_params) {}

// ======================================================================================

function byte _psh(_params) { return alu_op1(op_code, [](ref x) { return push_mem(x); }); }

// ======================================================================================

function byte _pop(_params) { return alu_op1(op_code, [](ref x) { return x = pop_stack(); }); }

// ======================================================================================

function byte _shl(_params) { return alu_op2(op_code, [](ref a, cref b) { return a <<= b; }); }

// ======================================================================================

function byte _shr(_params) { return alu_op2(op_code, [](ref a, cref b) { return a >>= b; }); }

// ======================================================================================

function byte _mov(_params) { return alu_op2(op_code, [](ref a, cref b) { return a = b; }); }

// ======================================================================================

function byte _lbl(_params) {}

// ======================================================================================

function byte _nop(_params) { push_mem(function byte()); }

// ======================================================================================

function byte _ret(_params) {}

// ======================================================================================

function byte _cmp(_params) { return alu_op2(op_code, [](ref x, cref y) { return compare(x, y); }); }

// ======================================================================================

function byte _jmp(_params) { return alu_op1(op_code, [&IP](ref x) { return IP = x; }); }

// ======================================================================================

function byte _je(_params) { if (bitRead(FLAGS, ZR)) return _jmp(op_code); }

// ======================================================================================

function byte _jne(_params) { if (!bitRead(FLAGS, ZR)) return _jmp(op_code); }

// ======================================================================================

function byte _jl(_params) { if (bitRead(FLAGS, LS)) return _jmp(op_code); }

// ======================================================================================

function byte _jle(_params) { if (bitRead(FLAGS, ZR) || bitRead(FLAGS, LS)) return _jmp(op_code); }

// ======================================================================================

function byte _jg(_params) { if (bitRead(FLAGS, GR)) return _jmp(op_code); }

// ======================================================================================

function byte _jge(_params) { if (bitRead(FLAGS, ZR) || bitRead(FLAGS, GR)) return _jmp(op_code); }

// ======================================================================================

function byte _jc(_params) { if (bitRead(FLAGS, CR)) return _jmp(op_code); }

// ======================================================================================

function byte _jo(_params) { if (bitRead(FLAGS, AO)) return _jmp(op_code); }

// ======================================================================================

function byte _js(_params) { if (bitRead(FLAGS, SG)) return _jmp(op_code); }

// ======================================================================================

function byte _jz(_params) { if (bitRead(FLAGS, ZR)) return _jmp(op_code); }

// ======================================================================================

function byte compare(byte x, byte y)
{
    auto diff = x - y;

    bitWrite(FLAGS, ZR, (diff == 0));
    bitWrite(FLAGS, GR, (diff > 0));
    bitWrite(FLAGS, LS, (diff < 0));

    return diff;
}

// ======================================================================================

function void set_flags(byte result)
{
    if (result == 0) bitSet(FLAGS, ZR);
    else if (result < 0) bitSet(FLAGS, SG);
    if (!(result & 1)) bitSet(FLAGS, PR);
}

// ======================================================================================

function byte execute(byte op_code)
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

// ======================================================================================
