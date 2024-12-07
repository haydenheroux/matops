#pragma once

#include "matrix.h"
#include <stdbool.h>

/*
 * Prints a message depending on if the test passes or fails.
 */
void test(const char *pass_message, const char *fail_message, bool passes);

/*
 * Prints a message depending on if the matrices `A` and `B` are equal. Equality
 * is considered a passing test.
 */
void test_matrix_are_equal(const char *A_name, const char *B_name,
                           const Matrix *A, const Matrix *B);

/*
 * Prints a message depending on if the matrices `A` and `B` are not equal.
 * Inequality is considered a passing test.
 */
void test_matrix_are_not_equal(const char *A_name, const char *B_name,
                               const Matrix *A, const Matrix *B);
