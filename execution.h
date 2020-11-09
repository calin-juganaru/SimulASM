#pragma once

#include "functions.h"

// ============================================================================

void error();

byte push_mem(byte value);
byte pop_mem();
byte pop_stack();

void print_segment();
void clear_segment();

byte get_key();
byte get_button();

byte wait_button(cref button);
byte read_value(byte base = 10);

byte get_reg();
byte get_mem();

String get_instruction(const char& c);

void set_memory_bit(int row, byte col, boolean value = true);
void set_memory_byte(int index);

void set_register_bit(int row, byte col, boolean value = true);
void display_register(byte index);

void run_code();

// ============================================================================
