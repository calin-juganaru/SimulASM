#include "functions.h"

// ======================================================================================

template <typename Op>
inline byte alu_op1(_params, Op&& op)
{
    auto x = pop_mem();

    switch (op_code)
    {
        case REG: return op(registers[x]);
        case MEM: return op(memory[x]);
        case IMD: return op(x);
        default: exit_err(ERROR);
    }
}

// ======================================================================================

template <typename Op>
inline byte alu_op2(_params, Op&& op)
{
    auto x = pop_mem(), y = pop_mem();

    switch (op_code)
    {
        case REG_REG: return op(registers[x], registers[y]);
        case REG_MEM: return op(registers[x], memory[y]);
        case MEM_REG: return op(memory[x], registers[y]);
        case REG_IMD: return op(registers[x], y);
        case MEM_IMD: return op(memory[x], y);
        default: exit_err(ERROR);
    }
}

// ======================================================================================

inline byte _and(_params) { _alu_op2(&); }
inline byte _or (_params) { _alu_op2(|); }
inline byte _not(_params) { _alu_op1(~); }
inline byte _xor(_params) { _alu_op2(^); }

inline byte _add(_params) { _alu_op2(+); }
inline byte _sub(_params) { _alu_op2(-); }
inline byte _mul(_params) {}
inline byte _div(_params) {}

inline byte _inc(_params) { _alu_op1(++); }
inline byte _dec(_params) { _alu_op1(--); }
inline byte _neg(_params) { _alu_op1(-); }
inline byte _mod(_params) {}

inline byte _psh(_params) { return alu_op1(op_code, [](ref x) { return push_mem(x); }); }
inline byte _pop(_params) { return alu_op1(op_code, [](ref x) { return x = pop_stack(); }); }
inline byte _shl(_params) { return alu_op2(op_code, [](ref a, cref b) { return a <<= b; }); }
inline byte _shr(_params) { return alu_op2(op_code, [](ref a, cref b) { return a >>= b; }); }

inline byte _mov(_params) { _alu_op1(); }
inline byte _lbl(_params) {}
inline byte _nop(_params) { push_mem(byte()); }
inline byte _ret(_params) {}

inline byte _cmp(_params) { return alu_op2(op_code, [](ref x, cref y) { return compare(x, y); }); }
inline byte _jmp(_params) { return alu_op1(op_code, [](ref x) { return IP = x; }); }
inline byte _je (_params) { if ( bitRead(FLAGS, ZR)) return _jmp(op_code); }
inline byte _jne(_params) { if (!bitRead(FLAGS, ZR)) return _jmp(op_code); }

inline byte _jl (_params) { return cond_jmp(LS); }
inline byte _jle(_params) { return cond_jmp(ZR) | cond_jmp(LS); }
inline byte _jg (_params) { return cond_jmp(GR); }
inline byte _jge(_params) { return cond_jmp(ZR) | cond_jmp(GR); }

inline byte _jc(_params) { return cond_jmp(CR); }
inline byte _jo(_params) { return cond_jmp(AO); }
inline byte _js(_params) { return cond_jmp(SG); }
inline byte _jz(_params) { return cond_jmp(ZR); }

// ======================================================================================

inline byte compare(byte x, byte y)
{
    auto diff = x - y;

    bitWrite(FLAGS, ZR, (diff == 0));
    bitWrite(FLAGS, GR, (diff > 0));
    bitWrite(FLAGS, LS, (diff < 0));

    return diff;
}

// ======================================================================================

inline void set_flags(byte result)
{
    if (result == 0) bitSet(FLAGS, ZR);
    else if (result < 0) bitSet(FLAGS, SG);
    if (!(result & 1)) bitSet(FLAGS, PR);
}

// ======================================================================================

inline void execute(byte op_code)
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
