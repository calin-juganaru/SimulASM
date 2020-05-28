#pragma once

#include "operations.h"

// ============================================================================

function parse_operand(ref op_code, byte operand)
{
    auto value = ERROR;

    if (operand | _REG)
    {
        op_code |= byte(1) << 2;
        value = get_reg();
    }

    else if (operand | _MEM)
    {
        op_code |= byte(1) << 1;
        value = get_mem();
    }

    else if (operand | _IMD)
    {
        op_code |= byte(1);
        value = read_value();
    }

    else error();

    return value;
}

// ============================================================================

function op_type_1(byte op_code, byte operand)
{
    op_code <<= 3;
    auto value = parse_operand(op_code, operand);

    push_mem(op_code);
    push_mem(value);
}

// ============================================================================

function op_type_2(byte op_code)
{
    op_code <<= 3;
    auto first = parse_operand(op_code, _REG | _MEM);

    auto second = byte();
    if (op_code | _MEM)
    {
        second = parse_operand(op_code, _REG | _IMD);
        if (op_code | _REG) op_code |= 1;
    }
    else if (op_code | _REG)
    {
        second = parse_operand(op_code, _REG | _MEM | _IMD);
        if (op_code | _REG) op_code ^= byte(1 << 2);
    }
    else exit_err();

    push_mem(op_code);
    push_mem(first);
    push_mem(second);
}

// ============================================================================

function parse_nop() { push_mem(byte()); }
function parse_lbl() { op_type_1(_LBL, _IMD); }
function parse_ret() { push_mem(byte(_RET << 3)); }

function parse_or() { op_type_2(_OR); }

function parse_and() { op_type_2(_AND); }
function parse_xor() { op_type_2(_XOR); }
function parse_add() { op_type_2(_ADD); }
function parse_sub() { op_type_2(_SUB); }
function parse_mov() { op_type_2(_MOV); }
function parse_shl() { op_type_2(_SHL); }
function parse_shr() { op_type_2(_SHR); }
function parse_cmp() { op_type_2(_CMP); }

function parse_mul() { op_type_1(_MUL, _REG); }
function parse_div() { op_type_1(_DIV, _REG); }
function parse_mod() { op_type_1(_MOD, _REG); }

function parse_not() { op_type_1(_NOT, _REG | _MEM); }
function parse_inc() { op_type_1(_INC, _REG | _MEM); }
function parse_dec() { op_type_1(_DEC, _REG | _MEM); }
function parse_neg() { op_type_1(_NEG, _REG | _MEM); }
function parse_pop() { op_type_1(_POP, _REG | _MEM); }

function parse_je() { op_type_1(_JE, _REG | _MEM | _IMD); }
function parse_jl() { op_type_1(_JL, _REG | _MEM | _IMD); }
function parse_jg() { op_type_1(_JG, _REG | _MEM | _IMD); }
function parse_jc() { op_type_1(_JC, _REG | _MEM | _IMD); }
function parse_jo() { op_type_1(_JO, _REG | _MEM | _IMD); }
function parse_js() { op_type_1(_JS, _REG | _MEM | _IMD); }
function parse_jz() { op_type_1(_JZ, _REG | _MEM | _IMD); }

function parse_jmp() { op_type_1(_JMP, _REG | _MEM | _IMD); }
function parse_jne() { op_type_1(_JNE, _REG | _MEM | _IMD); }
function parse_jle() { op_type_1(_JLE, _REG | _MEM | _IMD); }
function parse_jge() { op_type_1(_JGE, _REG | _MEM | _IMD); }

function parse_push() { op_type_1(_PSH, _REG | _MEM | _IMD); }

// ============================================================================
