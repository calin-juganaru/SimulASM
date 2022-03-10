#pragma once

// =============================================================================

#define function inline auto
#define constant constexpr auto
#define var register auto
#define _params byte op_code

using func_t = byte (*)(byte);

#define EMPTY_LINE "        "
#define newline lcd_print("\n")
#define DIE(cond) if (cond == ERROR) error()
#define exit_err(x) error(); return x
#define break_if(cond) if (cond) break

using pointer = byte*;
using ref = byte&;
using cref = const byte&;
using string = String;

// =============================================================================

template <typename... Ts>
function va_multiply(Ts... args)
{
    return (args * ...);
}

template <typename T, typename... Ts>
function belongs(T arg, Ts... args)
{
    return !va_multiply(arg ^ args...);
}

template <typename T, typename U>
function append_bit(T& value, U bit)
{
    value = (value << 1) | bit;
}

// =============================================================================

template <typename Function>
static inline void call(Function&& _function, byte count)
{
    for (auto index = byte(); index < count; ++index) _function(index);
}

// =============================================================================

/*
#define PARENS ()

#define EXPAND(...) EXPAND4(EXPAND4(EXPAND4(EXPAND4(__VA_ARGS__))))
#define EXPAND4(...) EXPAND3(EXPAND3(EXPAND3(EXPAND3(__VA_ARGS__))))
#define EXPAND3(...) EXPAND2(EXPAND2(EXPAND2(EXPAND2(__VA_ARGS__))))
#define EXPAND2(...) EXPAND1(EXPAND1(EXPAND1(EXPAND1(__VA_ARGS__))))
#define EXPAND1(...) __VA_ARGS__

#define FOR_EACH(macro, ...)  \
    __VA_OPT__(EXPAND(FOR_EACH_HELPER(macro, __VA_ARGS__)))
#define FOR_EACH_HELPER(macro, a1, ...)  macro(a1)  \
    __VA_OPT__(FOR_EACH_AGAIN PARENS (macro, __VA_ARGS__))
#define FOR_EACH_AGAIN() FOR_EACH_HELPER

void parse();

#define ENUM_CASE(name) case name:          \
                        lcd_print(#name);   \
                        parse##name();      \
                        lcd_print("\n");    \
                        break;

#define MAKE_ENUM(type, ...)                    \
    enum type { __VA_ARGS__ };                  \
    namespace                                   \
    {                                           \
        const initializer_list<type> Type##List { __VA_ARGS__ }; \
    };                                          \
    constexpr auto parse_instr(type _e)         \
    {                                           \
        switch (_e)                             \
        {                                       \
            FOR_EACH(ENUM_CASE, __VA_ARGS__)    \
            default: wait_button(ENTER); break; \
        }                                       \
    }

MAKE_ENUM
(
    instruction_t, _dummy,
    _and, _or, _not/*, _xor,
    _add, _sub, _mul, _div,
    _inc, _dec, _neg, _mod,
    _psh, _pop, _shl, _shr,
    _mov, _lbl, _nop, _ret,
    _cmp, _jmp, _je,  _jne,
    _jl,  _jle, _jg,  _jge,
    _jc,  _jo,  _js,  _jz
);
*/

// =============================================================================