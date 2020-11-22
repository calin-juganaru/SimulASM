#include "execution.h"

// ================================================================================================

inline void error()
{
    for (auto i = 0; i < 3; ++i)
    {
        module.setLEDs(255);
        delay(100);
        module.setLEDs(0);
        delay(100);
    }
}

// ============================================================================

inline byte push_mem(byte value)
{
    if (SR == 31) bitSet(FLAGS, SO);
    SR = (SR + 1) % 32;
    return memory[SR] = value;
}

// ============================================================================

inline byte pop_mem()
{
    auto value = memory[IP];
    if (IP == 31) bitSet(FLAGS, SO);
    IP = (IP + 1) % 32;
    return value;
}

// ============================================================================

inline byte pop_stack()
{
    auto value = memory[SR];
    if (SR == 0) bitSet(FLAGS, SO);
    SR = (SR - 1) % 32;
    return value;
}

// ============================================================================

inline void print_segment()
{
    module.setDisplayToString(segment_text.c_str());
}

// ============================================================================

inline void clear_segment()
{
    segment_text = "        ";
    print_segment();
}

// ============================================================================

inline byte get_key()
{
    auto aux = 0;
    while (!aux)
        aux = numpad.getKey();
    return aux - 1;
}

// ============================================================================

inline byte get_button()
{
    auto aux = byte();
    while (!aux)
        aux = module.getButtons();

    for (auto i = 0; i < 8; ++i)
        if (aux & (1 << i))
          return byte(1 << i);

    return ERROR;
}

// ============================================================================

inline byte wait_button(cref button)
{
    auto aux = module.getButtons();
    while (!(aux & button))
        aux = module.getButtons();
    return aux;
}

// ============================================================================

inline byte read_value(byte base)
{
    auto value = byte();

    while (get_button() != ENTER)
    {
        auto aux = get_key();
        value = value * base + aux;
        auto index = 4;
        for (auto i: String(value))
            segment_text[index++] = i;

        print_segment();
    }

    return value;
}

// ============================================================================

inline byte get_reg()
{
    auto index = read_value();
    while (index > 3)
    {
        error();
        index = read_value();
    }

    return index;
}

// ============================================================================

inline byte get_mem()
{
    auto index = read_value();
    while (index > 31)
    {
        error();
        index = read_value();
    }

    return index;
}

// ============================================================================

inline String get_instruction(const char& c)
{
    if (c < 0 || c > 'F')
        return String("Err0r");
    return instructions[c];
}

// ================================================================================================

inline void set_memory_bit(int row, byte col, boolean value)
{
    mem_display.setLed(row / 8, col, 7 + 8 * (row / 8) - row, value);
}

// ================================================================================================

inline void set_memory_byte(int index)
{
    auto value = memory[index];
    for (auto col = 0; col < 8; ++col, value >>= 1)
        set_memory_bit(index, col, value % 2);
}

// ================================================================================================

inline void set_register_bit(int row, byte col, boolean value)
{
    reg_display.setLed(0, 7 - row, col, value);
}

// ================================================================================================

inline void display_register(byte index)
{
    auto value = registers[index];
    for (auto i = 0; i < 8; ++i, value >>= 1)
        set_register_bit(index, i, value % 2);
}

// ================================================================================================

void run_code()
{
    error(); error();
    wait_button(ENTER);
    clear_segment();

    RA = RB = RC = RD = BP = IP = FLAGS = 0;

    for (auto i = 0; i < 8; ++i)
        display_register(i);

    while (true)
    {
        auto op_code = pop_mem();
        execute(op_code);

        for (auto i = 0; i < 32; ++i)
            set_memory_byte(i);

        for (auto i = 0; i < 8; ++i)
            display_register(i);

        wait_button(ENTER);
    }
}

// ================================================================================================
