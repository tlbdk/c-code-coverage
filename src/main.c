#include <stdio.h>
#include <inttypes.h>
#include "add.h"

int main(void)
{
    printf("7 + 3 = %"PRIi32"\n", add(7, 3));
    printf("7 * 3 = %"PRIi32"\n", mul(7, 3));
    return 0;
}