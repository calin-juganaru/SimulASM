#pragma once

// ============================================================================

#define function static inline
#define constant constexpr auto
#define var register auto

#define _params byte op_code

using func_t = byte (*)(byte);

#define DIE(cond) if (cond == ERROR) error()
#define exit_err() error(); return

using pointer = byte*;
using ref = byte&;
using cref = const byte&;

// ============================================================================
