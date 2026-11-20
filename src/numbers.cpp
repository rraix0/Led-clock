#include "numbers.h"

const bool number_shapes[10][12] = {
    {// 0
        true, true,
        true, false, true,
        false, false,
        true, false, true,
        true, true
    },
    {// 1
        false, true,
        false, false, true,
        false, true,
        false, false, true,
        false, true
    },
    {// 2
        true, true,
        false, false, true,
        true, true,
        true, false, false,
        true, true
    },
    {// 3
        true, true,
        false, false, true,
        true, true,
        false, false, true,
        true, true
    },
    {// 4
        true, false,
        true, false, true,
        true, true,
        false, false, true,
        false, true
    },
    {// 5
        true, true,
        true, false, false,
        true, true,
        false, false, true,
        true, true
    },
    {// 6
        false, true,
        false, true, false,
        true, true,
        true, false, true,
        true, true
    },
    {// 7
        true, true,
        false, false, true,
        false, true,
        false, true, false,
        true, false
    },
    {// 8
        true, true,
        true, false, true,
        true, true,
        true, false, true,
        true, true
    },
    {// 9
        true, true,
        true, false, true,
        true, true,
        false, true, false,
        true, false
    }
};