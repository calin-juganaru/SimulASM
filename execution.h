#pragma once

#include "operations.h"

// ============================================================================

#define exec_op(X, Y) case _##X: exec_##Y(types); break

// ============================================================================

function exec_nop(byte op_code)
{
    push_mem(byte());
}

// ============================================================================

function exec_and(byte op_code)
{
    auto x = pop_mem(), y = pop_mem();

    if (op_code == REG_REG)
        registers[x] &= registers[y];

    else if (op_code == REG_MEM)
        registers[x] &= memory[y];

    else if (op_code == MEM_REG)
        memory[x] &= registers[y];

    else if (op_code == REG_IMD)
        registers[x] &= y;

    else if (op_code == MEM_IMD)
        memory[x] &= y;

    else exit_err();
}

// ============================================================================

function exec_or(byte op_code)
{
    if (op_code == REG_REG)
    {
        auto& x = registers[pop_mem()];
        auto  y = registers[pop_mem()];
        x |= y;
    }

    else if (op_code == REG_MEM)
    {
        auto& x = registers[pop_mem()];
        auto  y = memory[pop_mem()];
        x |= y;
    }

    else if (op_code == MEM_REG)
    {
        auto& x = memory[pop_mem()];
        auto  y = registers[pop_mem()];
        x |= y;
    }

    else if (op_code == REG_IMD)
    {
        auto& x = registers[pop_mem()];
        auto  y = pop_mem();
        x |= y;
    }

    else if (op_code == MEM_IMD)
    {
        auto& x = memory[pop_mem()];
        auto  y = pop_mem();
        x |= y;
    }

    else exit_err();
}

// ============================================================================

function exec_not(byte op_code)
{
    if (op_code == REG)
    {
        auto& x = registers[pop_mem()];
        x = ~x;
    }

    else if (op_code == MEM)
    {
        auto& x = memory[pop_mem()];
        x = ~x;
    }

    else exit_err();
}

// ============================================================================

function exec_xor(byte op_code)
{
    if (op_code == REG_REG)
    {
        auto& x = registers[pop_mem()];
        auto  y = registers[pop_mem()];
        x ^= y;
    }

    else if (op_code == REG_MEM)
    {
        auto& x = registers[pop_mem()];
        auto  y = memory[pop_mem()];
        x ^= y;
    }

    else if (op_code == MEM_REG)
    {
        auto& x = memory[pop_mem()];
        auto  y = registers[pop_mem()];
        x ^= y;
    }

    else if (op_code == REG_IMD)
    {
        auto& x = registers[pop_mem()];
        auto  y = pop_mem();
        x ^= y;
    }

    else if (op_code == MEM_IMD)
    {
        auto& x = memory[pop_mem()];
        auto  y = pop_mem();
        x ^= y;
    }

    else exit_err();
}

// ============================================================================

function exec_add(byte op_code)
{
    if (op_code == REG_REG)
    {
        auto& x = registers[pop_mem()];
        auto  y = registers[pop_mem()];
        x += y;
    }

    else if (op_code == REG_MEM)
    {
        auto& x = registers[pop_mem()];
        auto  y = memory[pop_mem()];
        x += y;
    }

    else if (op_code == MEM_REG)
    {
        auto& x = memory[pop_mem()];
        auto  y = registers[pop_mem()];
        x += y;
    }

    else if (op_code == REG_IMD)
    {
        auto& x = registers[pop_mem()];
        auto  y = pop_mem();
        x += y;
    }

    else if (op_code == MEM_IMD)
    {
        auto& x = memory[pop_mem()];
        auto  y = pop_mem();
        x += y;
    }

    else exit_err();
}

// ============================================================================

function exec_sub(byte op_code)
{
    if (op_code == REG_REG)
    {
        auto& x = registers[pop_mem()];
        auto  y = registers[pop_mem()];
        x -= y;
    }

    else if (op_code == REG_MEM)
    {
        auto& x = registers[pop_mem()];
        auto  y = memory[pop_mem()];
        x -= y;
    }

    else if (op_code == MEM_REG)
    {
        auto& x = memory[pop_mem()];
        auto  y = registers[pop_mem()];
        x -= y;
    }

    else if (op_code == REG_IMD)
    {
        auto& x = registers[pop_mem()];
        auto  y = pop_mem();
        x -= y;
    }

    else if (op_code == MEM_IMD)
    {
        auto& x = memory[pop_mem()];
        auto  y = pop_mem();
        x -= y;
    }

    else exit_err();
}

// ============================================================================

function exec_inc(byte op_code)
{
    if (op_code == REG)
    {
        auto& x = registers[pop_mem()];
        x = x + 1;
    }

    else if (op_code == MEM)
    {
        auto& x = memory[pop_mem()];
        x = x + 1;
    }

    else exit_err();
}

// ============================================================================

function exec_dec(byte op_code)
{
    if (op_code == REG)
    {
        auto& x = registers[pop_mem()];
        x = x - 1;
    }

    else if (op_code == MEM)
    {
        auto& x = memory[pop_mem()];
        x = x - 1;
    }

    else exit_err();
}

// ============================================================================

function exec_neg(byte op_code)
{
    if (op_code == REG)
    {
        auto& x = registers[pop_mem()];
        x = -x;
    }

    else if (op_code == MEM)
    {
        auto& x = memory[pop_mem()];
        x = -x;
    }

    else exit_err();
}

// ============================================================================

function exec_shl(byte op_code)
{
    if (op_code == REG_REG)
    {
        auto& x = registers[pop_mem()];
        auto  y = registers[pop_mem()];
        x <<= y;
    }

    else if (op_code == REG_MEM)
    {
        auto& x = registers[pop_mem()];
        auto  y = memory[pop_mem()];
        x <<= y;
    }

    else if (op_code == MEM_REG)
    {
        auto& x = memory[pop_mem()];
        auto  y = registers[pop_mem()];
        x <<= y;
    }

    else if (op_code == REG_IMD)
    {
        auto& x = registers[pop_mem()];
        auto  y = pop_mem();
        x <<= y;
    }

    else if (op_code == MEM_IMD)
    {
        auto& x = memory[pop_mem()];
        auto  y = pop_mem();
        x <<= y;
    }

    else exit_err();
}

// ============================================================================

function exec_shr(byte op_code)
{
    if (op_code == REG_REG)
    {
        auto& x = registers[pop_mem()];
        auto  y = registers[pop_mem()];
        x >>= y;
    }

    else if (op_code == REG_MEM)
    {
        auto& x = registers[pop_mem()];
        auto  y = memory[pop_mem()];
        x >>= y;
    }

    else if (op_code == MEM_REG)
    {
        auto& x = memory[pop_mem()];
        auto  y = registers[pop_mem()];
        x >>= y;
    }

    else if (op_code == REG_IMD)
    {
        auto& x = registers[pop_mem()];
        auto  y = pop_mem();
        x >>= y;
    }

    else if (op_code == MEM_IMD)
    {
        auto& x = memory[pop_mem()];
        auto  y = pop_mem();
        x >>= y;
    }

    else exit_err();
}

// ============================================================================

function exec_mov(byte op_code)
{
    if (op_code == REG_REG)
    {
        auto& x = registers[pop_mem()];
        auto  y = registers[pop_mem()];
        x = y;
    }

    else if (op_code == REG_MEM)
    {
        auto& x = registers[pop_mem()];
        auto  y = memory[pop_mem()];
        x = y;
    }

    else if (op_code == MEM_REG)
    {
        auto& x = memory[pop_mem()];
        auto  y = registers[pop_mem()];
        x = y;
    }

    else if (op_code == REG_IMD)
    {
        auto& x = registers[pop_mem()];
        auto  y = pop_mem();
        x = y;
    }

    else if (op_code == MEM_IMD)
    {
        auto& x = memory[pop_mem()];
        auto  y = pop_mem();
        x = y;
    }

    else exit_err();
}

// ============================================================================

function exec_push(byte op_code)
{
    if (op_code == REG)
    {
        auto index = pop_mem();
        push_mem(registers[index]);
    }

    else if (op_code == MEM)
    {
        auto index = pop_mem();
        push_mem(memory[index]);
    }

    else if (op_code == IMD)
    {
        auto value = pop_mem();
        push_mem(value);
    }

    else exit_err();
}

// ============================================================================

function exec_pop(byte op_code)
{
    auto value = pop_stack();
    auto index = pop_mem();

    if (op_code == REG)
    {
        registers[index] = value;
    }

    else if (op_code == MEM)
    {
        memory[index] = value;
    }

    else exit_err();
}

// ============================================================================

function compare(cref x, cref y)
{
    auto diff = x - y;

    bitWrite(FR, ZR, (diff == 0));
    bitWrite(FR, GR, (diff > 0));
    bitWrite(FR, LS, (diff < 0));
}

// ============================================================================

function exec_cmp(byte op_code)
{
    if (op_code == REG_REG)
    {
        auto x = registers[pop_mem()];
        auto y = registers[pop_mem()];
        compare(x, y);
    }

    else if (op_code == REG_MEM)
    {
        auto x = registers[pop_mem()];
        auto y = memory[pop_mem()];
        compare(x, y);
    }

    else if (op_code == MEM_REG)
    {
        auto x = memory[pop_mem()];
        auto y = registers[pop_mem()];
        compare(x, y);
    }

    else if (op_code == REG_IMD)
    {
        auto x = registers[pop_mem()];
        auto y = pop_mem();
        compare(x, y);
    }

    else if (op_code == MEM_IMD)
    {
        auto x = memory[pop_mem()];
        auto y = pop_mem();
        compare(x, y);
    }

    else exit_err();
}

// ============================================================================

function exec_jmp(byte op_code)
{
    if (op_code == REG)
        IP = registers[pop_mem()];

    else if (op_code == MEM)
        IP = memory[pop_mem()];

    else if (op_code == IMD)
        IP = pop_mem();

    else exit_err();
}

// ============================================================================

function exec_jne(byte op_code)
{
    if (!bitRead(FR, ZR)) exec_jmp(op_code);
}

// ============================================================================

function exec_jle(byte op_code)
{
    if (bitRead(FR, ZR) || bitRead(FR, LS)) exec_jmp(op_code);
}

// ============================================================================

function exec_jge(byte op_code)
{
    if (bitRead(FR, ZR) || bitRead(FR, GR)) exec_jmp(op_code);
}

// ============================================================================

function exec_je(byte op_code)
{
    if (bitRead(FR, ZR)) exec_jmp(op_code);
}

// ============================================================================

function exec_jl(byte op_code)
{
    if (bitRead(FR, LS)) exec_jmp(op_code);
}

// ============================================================================

function exec_jg(byte op_code)
{
    if (bitRead(FR, GR)) exec_jmp(op_code);
}

// ============================================================================

function exec_jc(byte op_code)
{
    if (bitRead(FR, CR)) exec_jmp(op_code);
}

// ============================================================================

function exec_jo(byte op_code)
{
    if (bitRead(FR, AO)) exec_jmp(op_code);
}

// ============================================================================

function exec_js(byte op_code)
{
    if (bitRead(FR, SG)) exec_jmp(op_code);
}

// ============================================================================

function exec_jz(byte op_code)
{
    if (bitRead(FR, ZR)) exec_jmp(op_code);
}

// ============================================================================

function execute(byte op_code)
{
    auto types = op_code & 7;

    switch (op_code >> 3)
    {
        exec_op(NOP, nop);
        exec_op(AND, and);
        exec_op(NOT, not);
        exec_op(XOR, xor);
        exec_op(ADD, add);
        exec_op(SUB, sub);
        //exec_op(MUL, mul);
        //exec_op(DIV, div);
        exec_op(INC, inc);
        exec_op(DEC, dec);
        exec_op(NEG, neg);
        //exec_op(MOD, mod);
        exec_op(PSH, push);
        exec_op(POP, pop);
        exec_op(SHL, shl);
        exec_op(SHR, shr);
        exec_op(MOV, mov);
        //exec_op(LBL, lbl);
        //exec_op(RET, ret);
        exec_op(CMP, cmp);
        exec_op(JMP, jmp);
        exec_op(JNE, jne);
        exec_op(JLE, jle);
        exec_op(JGE, jge);
        exec_op(JE, je);
        exec_op(JL, jl);
        exec_op(JG, jg);
        exec_op(JC, jc);
        exec_op(JO, jo);
        exec_op(JS, js);
        exec_op(JZ, jz);
        exec_op(OR, or);

        default: exit_err();
    }
}

// ============================================================================