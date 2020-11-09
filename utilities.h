#pragma once

// ============================================================================

#define function inline
#define constant constexpr auto
#define var register auto

using func_t = byte (*)(byte);

#define DIE(cond) if (cond == ERROR) error()
#define exit_err(x) error(); return x

#define _params byte op_code

using pointer = byte*;
using ref = byte&;
using cref = const byte&;

// ============================================================================
