#pragma once

#include "operations.h"

// ============================================================================

#define parse_op(X, Y) case _##X: parse_##Y(); break
#define break_if(cond) if (cond) break

// ============================================================================

function parse_operand(ref op_code, byte operand)
{
    auto value = ERROR;

    if ((operand & REG) && (get_button() == BTN_REG))
    {
        op_code |= byte(1 << 2);
        value = get_reg();
    }

    else if ((operand & MEM) && (get_button() == BTN_MEM))
    {
        op_code |= byte(1 << 1);
        value = get_mem();
    }

    else if ((operand & IMD) && (get_button() == BTN_IMD))
    {
        op_code |= byte(1);
        value = read_value();
    }

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
    auto first = parse_operand(op_code, REG | MEM);

    auto index = 4;
    for (auto i: String(first))
        segment_text[index++] = ' ';
    print_segment();

    wait_button(BTN_REG | BTN_MEM | BTN_IMD);

    auto second = byte();
    if (op_code & MEM)
    {
        second = parse_operand(op_code, REG | IMD);
        if (op_code & REG) op_code |= 1;
    }
    else if (op_code & REG)
    {
        op_code ^= REG;
        second = parse_operand(op_code, REG | MEM | IMD);
        if (op_code & REG)
             op_code ^= REG;
        else op_code |= REG;
    }

    //else exit_err();

    push_mem(op_code);
    push_mem(first);
    push_mem(second);
}

// ============================================================================

function parse_nop() { push_mem(byte()); }
function parse_lbl() { op_type_1(_LBL, IMD); }
//function parse_ret() { push_mem(byte(_RET << 3)); }

function parse_or() { op_type_2(_OR); }

function parse_and() { op_type_2(_AND); }
function parse_xor() { op_type_2(_XOR); }
function parse_add() { op_type_2(_ADD); }
function parse_sub() { op_type_2(_SUB); }
function parse_mov() { op_type_2(_MOV); }
function parse_shl() { op_type_2(_SHL); }
function parse_shr() { op_type_2(_SHR); }
function parse_cmp() { op_type_2(_CMP); }

function parse_mul() { op_type_1(_MUL, REG); }
function parse_div() { op_type_1(_DIV, REG); }
function parse_mod() { op_type_1(_MOD, REG); }

function parse_not() { op_type_1(_NOT, REG | MEM); }
function parse_inc() { op_type_1(_INC, REG | MEM); }
function parse_dec() { op_type_1(_DEC, REG | MEM); }
function parse_neg() { op_type_1(_NEG, REG | MEM); }
function parse_pop() { op_type_1(_POP, REG | MEM); }

function parse_je() { op_type_1(_JE, REG | MEM | IMD); }
function parse_jl() { op_type_1(_JL, REG | MEM | IMD); }
function parse_jg() { op_type_1(_JG, REG | MEM | IMD); }
function parse_jc() { op_type_1(_JC, REG | MEM | IMD); }
function parse_jo() { op_type_1(_JO, REG | MEM | IMD); }
function parse_js() { op_type_1(_JS, REG | MEM | IMD); }
function parse_jz() { op_type_1(_JZ, REG | MEM | IMD); }

function parse_jmp() { op_type_1(_JMP, REG | MEM | IMD); }
function parse_jne() { op_type_1(_JNE, REG | MEM | IMD); }
function parse_jle() { op_type_1(_JLE, REG | MEM | IMD); }
function parse_jge() { op_type_1(_JGE, REG | MEM | IMD); }

function parse_push() { op_type_1(_PSH, REG | MEM | IMD); }

// ============================================================================
