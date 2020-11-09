#include "parsing.h"
#include "constants.h"

// ============================================================================

function byte parse_operand(ref op_code, byte operand)
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

function void parse_op1(byte op_code, byte operand)
{
    op_code <<= 3;
    auto value = parse_operand(op_code, operand);

    push_mem(op_code);
    push_mem(value);
}

// ============================================================================

function void parse_op2(byte op_code)
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

function void parse_nop() { push_mem(byte()); }
function void parse_lbl() { parse_op1(_LBL, IMD); }
//function void parse_ret() { push_mem(byte(_RET << 3)); }

function void parse_or() { parse_op2(_OR); }

function void parse_and() { parse_op2(_AND); }
function void parse_xor() { parse_op2(_XOR); }
function void parse_add() { parse_op2(_ADD); }
function void parse_sub() { parse_op2(_SUB); }
function void parse_mov() { parse_op2(_MOV); }
function void parse_shl() { parse_op2(_SHL); }
function void parse_shr() { parse_op2(_SHR); }
function void parse_cmp() { parse_op2(_CMP); }

function void parse_mul() { parse_op1(_MUL, REG); }
function void parse_div() { parse_op1(_DIV, REG); }
function void parse_mod() { parse_op1(_MOD, REG); }

function void parse_not() { parse_op1(_NOT, REG | MEM); }
function void parse_inc() { parse_op1(_INC, REG | MEM); }
function void parse_dec() { parse_op1(_DEC, REG | MEM); }
function void parse_neg() { parse_op1(_NEG, REG | MEM); }
function void parse_pop() { parse_op1(_POP, REG | MEM); }

function void parse_je() { parse_op1(_JE, REG | MEM | IMD); }
function void parse_jl() { parse_op1(_JL, REG | MEM | IMD); }
function void parse_jg() { parse_op1(_JG, REG | MEM | IMD); }
function void parse_jc() { parse_op1(_JC, REG | MEM | IMD); }
function void parse_jo() { parse_op1(_JO, REG | MEM | IMD); }
function void parse_js() { parse_op1(_JS, REG | MEM | IMD); }
function void parse_jz() { parse_op1(_JZ, REG | MEM | IMD); }

function void parse_jmp() { parse_op1(_JMP, REG | MEM | IMD); }
function void parse_jne() { parse_op1(_JNE, REG | MEM | IMD); }
function void parse_jle() { parse_op1(_JLE, REG | MEM | IMD); }
function void parse_jge() { parse_op1(_JGE, REG | MEM | IMD); }
function void parse_psh() { parse_op1(_PSH, REG | MEM | IMD); }

// ============================================================================
