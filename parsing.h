#pragma once

#include "execution.h"
#include "instructions.h"

// =============================================================================

function parse_operand(ref op_code, byte operand)
{
    auto value = ERROR;
    lcd_print(" ");

    if ((operand & REG) && (get_button() == BTN_REG))
    {
        lcd_print("reg ");
        op_code |= byte(1 << 2);
        value = get_reg();
    }

    else if ((operand & MEM) && (get_button() == BTN_MEM))
    {
        lcd_print("mem ");
        op_code |= byte(1 << 1);
        value = get_mem();
    }

    else if ((operand & IMD) && (get_button() == BTN_IMD))
    {
        lcd_print("imd ");
        op_code |= byte(1);
        value = read_value();
    }

    return value;
}

// =============================================================================

function parse_type_1(byte op_code, byte operand)
{
    op_code <<= 3;
    auto value = parse_operand(op_code, operand);

    push_mem(op_code);
    push_mem(value);
}

// =============================================================================

function parse_type_2(byte op_code)
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
        if (op_code & REG) op_code |= 1; ///
    }
    else if (op_code & REG)
    {
        op_code ^= REG;
        second = parse_operand(op_code, REG | MEM | IMD);
        if (op_code & REG)
             op_code ^= REG;
        else op_code |= REG;
    }
    else exit_err();

    push_mem(op_code);
    push_mem(first);
    push_mem(second);
}

// =============================================================================

function parse_instruction(byte op_code)
{
    auto case_code = byte();

    lcd_print(instructions[op_code]);

    append_bit(case_code, belongs(op_code, _AND, _XOR, _ADD, _SUB,
                                      _OR, _MOV, _SHL, _SHR, _CMP));
    append_bit(case_code, belongs(op_code,_MUL, _DIV, _MOD));
    append_bit(case_code, belongs(op_code,_NOT, _INC, _DEC, _NEG, _POP));
    append_bit(case_code, belongs(op_code,_JE, _JL, _JG, _JC, _JO, _JS, _JZ));
    append_bit(case_code, belongs(op_code,_JMP, _JNE, _JLE, _JGE, _PSH));
    append_bit(case_code, belongs(op_code,_LBL));
    append_bit(case_code, belongs(op_code,_RET));
    append_bit(case_code, belongs(op_code,_NOP));

    switch (case_code)
    {
        case 0b1000'0000: parse_type_2(op_code);                   break;
        case 0b0100'0000: parse_type_1(op_code, REG);              break;
        case 0b0010'0000: parse_type_1(op_code, REG | MEM);        break;
        case 0b0001'0000: parse_type_1(op_code, REG | MEM | IMD);  break;
        case 0b0000'1000: parse_type_1(op_code, REG | MEM | IMD);  break;
        case 0b0000'0100: parse_type_1(op_code, IMD);              break;
        case 0b0000'0010: push_mem(byte(_RET << 3)); run_code();
        case 0b0000'0001: push_mem(byte()); break;
        default: error(); break;
    }

    newline;
}

// =============================================================================
