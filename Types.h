//----------------------------------------------------------------------------------------------------------------------
// Variable type support, size and limits
// Copyright (c) 2023 Samuel Gomes
//----------------------------------------------------------------------------------------------------------------------

#pragma once

#include <cstdint>

// QB64 false is 0 and true is -1 (sad, but true XD)
enum qb_bool : int8_t
{
    QB_TRUE = -1,
    QB_FALSE = 0
};

#define TO_C_BOOL(_exp_) ((_exp_) != false)
#define TO_QB_BOOL(_exp_) ((qb_bool)(-TO_C_BOOL(_exp_)))
#define TO_L_NOT(_exp_) (-(not(_exp_)))
