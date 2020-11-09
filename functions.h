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

void set_flags(byte result);
byte compare(byte x, byte y);
byte execute(_params);

// ============================================================================
