#pragma once

// ============================================================================

#define parse_op(X, Y) case _##X: parse_##Y(); break
#define break_if(cond) if (cond) break

// ============================================================================

byte parse_operand(ref op_code, byte operand);
void parse_op1(byte op_code, byte operand);
void parse_op2(byte op_code);

// ============================================================================

byte parse_and(_params);
byte parse_or(_params);
byte parse_not(_params);
byte parse_xor(_params);

byte parse_add(_params);
byte parse_sub(_params);
byte parse_mul(_params);
byte parse_div(_params);

byte parse_inc(_params);
byte parse_dec(_params);
byte parse_neg(_params);
byte parse_mod(_params);

byte parse_psh(_params);
byte parse_pop(_params);
byte parse_shl(_params);
byte parse_shr(_params);

byte parse_mov(_params);
byte parse_lbl(_params);
byte parse_nop(_params);
byte parse_ret(_params);

byte parse_cmp(_params);
byte parse_jmp(_params);
byte parse_je(_params);
byte parse_jne(_params);

byte parse_jl(_params);
byte parse_jle(_params);
byte parse_jg(_params);
byte parse_jge(_params);

byte parse_jc(_params);
byte parse_jo(_params);
byte parse_js(_params);
byte parse_jz(_params);

// ============================================================================
