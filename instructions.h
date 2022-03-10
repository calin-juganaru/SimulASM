#pragma once

#include "constants.h"

#define _alu_op1(op) return alu_op1(op_code, [](ref x) { return x = op x; })
#define _alu_op2(op) return alu_op2(op_code, [](ref x, cref y) { return x = x op y; })
#define cond_jmp(FLAG) (bitRead(FLAGS, FLAG)) ? _jmp(op_code) : byte()

// =============================================================================

template <typename Operation>
function alu_op1(_params, Operation&& operation)
{
    auto x = pop_mem();

    switch (op_code)
    {
        case REG: return operation(registers[x]);
        case MEM: return operation(memory[x]);
        case IMD: return operation(x);
    }
}

// =============================================================================

template <typename Operation>
function alu_op2(_params, Operation&& operation)
{
    auto x = pop_mem(), y = pop_mem();

    switch (op_code)
    {
        case REG_REG: return operation(registers[x], registers[y]);
        case REG_MEM: return operation(registers[x],    memory[y]);
        case MEM_REG: return operation(   memory[x], registers[y]);
        case REG_IMD: return operation(registers[x], y);
        case MEM_IMD: return operation(   memory[x], y);
    }
}

// =============================================================================

function compare(byte x, byte y)
{
    auto diff = x - y;

    bitWrite(FLAGS, ZR, (diff == 0));
    bitWrite(FLAGS, GR, (diff > 0));
    bitWrite(FLAGS, LS, (diff < 0));

    return diff;
}

// =============================================================================

function _and(_params) { _alu_op2(&); }
function _or (_params) { _alu_op2(|); }
function _not(_params) { _alu_op1(~); }
function _xor(_params) { _alu_op2(^); }

function _add(_params) { _alu_op2(+); }
function _sub(_params) { _alu_op2(-); }
function _mul(_params) { /* ... */ }
function _div(_params) { /* ... */ }

function _inc(_params) { _alu_op1(++); }
function _dec(_params) { _alu_op1(--); }
function _neg(_params) { _alu_op1(-);  }
function _mod(_params) { /* ... */ }

function _psh(_params) { return alu_op1(op_code, [](cref x) { return push_mem(x); }); }
function _pop(_params) { return alu_op1(op_code, [](ref x) { return x = pop_stack(); }); }
function _shl(_params) { return alu_op2(op_code, [](ref a, cref b) { return a <<= b; }); }
function _shr(_params) { return alu_op2(op_code, [](ref a, cref b) { return a >>= b; }); }

function _mov(_params) { _alu_op1(); }
function _lbl(_params) { /* ... */ }
function _nop(_params) { push_mem(byte()); }
function _ret(_params) { /* ... */ }

function _cmp(_params) { return alu_op2(op_code, [](ref x, cref y) { return compare(x, y); }); }
function _jmp(_params) { return alu_op1(op_code, [](ref x) { return IP = x; }); }
function _je (_params) { if ( bitRead(FLAGS, ZR)) return _jmp(op_code); }
function _jne(_params) { if (!bitRead(FLAGS, ZR)) return _jmp(op_code); }

function _jl (_params) { return cond_jmp(LS); }
function _jle(_params) { return cond_jmp(ZR) | cond_jmp(LS); }
function _jg (_params) { return cond_jmp(GR); }
function _jge(_params) { return cond_jmp(ZR) | cond_jmp(GR); }

function _jc(_params) { return cond_jmp(CR); }
function _jo(_params) { return cond_jmp(AO); }
function _js(_params) { return cond_jmp(SG); }
function _jz(_params) { return cond_jmp(ZR); }

// =============================================================================

function set_flags(byte result)
{
    if (result == 0)     bitSet(FLAGS, ZR);
    else if (result < 0) bitSet(FLAGS, SG);
    if (!(result & 1))   bitSet(FLAGS, PR);
}

// =============================================================================

function get_instruction(const char& c)
{
    if (c < 0 || c > 'F')
        return String("Err0r");
    return instructions[c];
}

// =============================================================================
