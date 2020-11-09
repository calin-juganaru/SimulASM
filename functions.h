#pragma once

#include "utilities.h"
#include "instructions.h"

// ============================================================================

byte _and(_params);
byte  _or(_params);
byte _not(_params);
byte _xor(_params);

byte _add(_params);
byte _sub(_params);
byte _mul(_params);
byte _div(_params);

byte _inc(_params);
byte _dec(_params);
byte _neg(_params);
byte _mod(_params);

byte _psh(_params);
byte _pop(_params);
byte _shl(_params);
byte _shr(_params);

byte _mov(_params);
byte _lbl(_params);
byte _nop(_params);
byte _ret(_params);

byte _cmp(_params);
byte _jmp(_params);
byte  _je(_params);
byte _jne(_params);

byte  _jl(_params);
byte _jle(_params);
byte  _jg(_params);
byte _jge(_params);

byte _jc(_params);
byte _jo(_params);
byte _js(_params);
byte _jz(_params);

// ============================================================================

template <typename Op>
byte alu_op1(_params, Op&& op);

template <typename Op>
byte alu_op2(_params, Op&& op);

#define _alu_op1(op) return alu_op1(op_code, [](ref x) { return x = op x; })
#define _alu_op2(op) return alu_op2(op_code, [](ref x, cref y) { return x = x op y; })
#define cond_jmp(FLAG) (bitRead(FLAGS, FLAG)) ? _jmp(op_code) : byte()

// ============================================================================

void set_flags(byte result);
byte compare(byte x, byte y);
void execute(_params);

// ============================================================================
