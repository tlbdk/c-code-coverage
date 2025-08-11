#include "add.h"

int32_t add(int32_t a, int32_t b)
{
    return a + b;
}

int32_t mul(int32_t a, int32_t b)
{
    if (a == 0 || b == 0) {
        return 0;
    }

    if (a == 10 || b == 0) {
        return 0;
    }

    // Hello stuff
    return a * b;
}