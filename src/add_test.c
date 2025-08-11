#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include <string.h>

#include <cmocka.h>

#include "add.h"

static void test_add(void **state) {
    (void) state; /* unused */
    int val = add(1, 2);
    assert_int_equal(val, 3);
}

static void test_mul(void **state) {
    (void) state; /* unused */
    int val = mul(3, 4);
    assert_int_equal(val, 12);
}

static void test_mul_zero(void **state) {
    (void) state; /* unused */
    int val = mul(0, 0);
    assert_int_equal(val, 0);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_add),
        cmocka_unit_test(test_mul),
        cmocka_unit_test(test_mul_zero),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}