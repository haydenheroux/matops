#include <stdio.h>

#include "test.h"

void test(const char *pass_message, const char *fail_message, bool passes) {
  if (passes) {
    printf("PASS %s\n", pass_message);
  } else {
    printf("FAIL %s\n", fail_message);
  }
}

void test_matrix_are_equal(const char *A_name, const char *B_name,
                           const Matrix *A, const Matrix *B) {
  if (matrix_are_equal(A, B)) {
    printf("PASS %s = %s\n", A_name, B_name);
  } else {
    printf("FAIL %s ≠ %s\n", A_name, B_name);
  }
}

void test_matrix_are_not_equal(const char *A_name, const char *B_name,
                               const Matrix *A, const Matrix *B) {
  if (!matrix_are_equal(A, B)) {
    printf("PASS %s ≠ %s\n", A_name, B_name);
  } else {
    printf("FAIL %s = %s\n", A_name, B_name);
  }
}
