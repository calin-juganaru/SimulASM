#pragma once

#include "pins.h"
#include "constants.h"
#include "parsing.h"
#include "execution.h"

// ============================================================================

template <typename F>
static inline void call(F&& f, byte N)
{
    for (auto i = 0; i < N; ++i) f(i);
}

// ============================================================================
