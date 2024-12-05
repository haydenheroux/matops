#include <stdbool.h>
#include <stdio.h>

#include "decomposition.h"
#include "matrix.h"
#include "test.h"

/*
 * Problem 3.4
 *
 * Factor the following matrix into an upper triangular matrix and a lower
 * triangular matrix.
 *
 * A = [ 1 2 -2 3
 *       -1 1 0 2
 *       3 -3 4 1
 *       2 1 1 -2 ]
 *
 * L = [  1  0 0     0
 *       -1  3 0     0
 *        3 -9 4     0
 *        2 -3 3 -33/4 ]
 *
 * U = [ 1 2   -2   3
 *       0 1 -2/3 5/3
 *       0 0    1 7/4
 *       0 0    0   1 ]
 */
void problem_3_4() {
  Matrix *A = matrix_create(4, 4);
  matrix_set(A, 0, 0, 1);
  matrix_set(A, 0, 1, 2);
  matrix_set(A, 0, 2, -2);
  matrix_set(A, 0, 3, 3);
  matrix_set(A, 1, 0, -1);
  matrix_set(A, 1, 1, 1);
  matrix_set(A, 1, 2, 0);
  matrix_set(A, 1, 3, 2);
  matrix_set(A, 2, 0, 3);
  matrix_set(A, 2, 1, -3);
  matrix_set(A, 2, 2, 4);
  matrix_set(A, 2, 3, 1);
  matrix_set(A, 3, 0, 2);
  matrix_set(A, 3, 1, 1);
  matrix_set(A, 3, 2, 1);
  matrix_set(A, 3, 3, -2);

  Matrix *R_L = matrix_create(4, 4);
  matrix_set(R_L, 0, 0, 1);
  matrix_set(R_L, 0, 1, 0);
  matrix_set(R_L, 0, 2, 0);
  matrix_set(R_L, 0, 3, 0);
  matrix_set(R_L, 1, 0, -1);
  matrix_set(R_L, 1, 1, 3);
  matrix_set(R_L, 1, 2, 0);
  matrix_set(R_L, 1, 3, 0);
  matrix_set(R_L, 2, 0, 3);
  matrix_set(R_L, 2, 1, -9);
  matrix_set(R_L, 2, 2, 4);
  matrix_set(R_L, 2, 3, 0);
  matrix_set(R_L, 3, 0, 2);
  matrix_set(R_L, 3, 1, -3);
  matrix_set(R_L, 3, 2, 3);
  matrix_set(R_L, 3, 3, -33.0 / 4.0);

  Matrix *R_U = matrix_create(4, 4);
  matrix_set(R_U, 0, 0, 1);
  matrix_set(R_U, 0, 1, 2);
  matrix_set(R_U, 0, 2, -2);
  matrix_set(R_U, 0, 3, 3);
  matrix_set(R_U, 1, 0, 0);
  matrix_set(R_U, 1, 1, 1);
  matrix_set(R_U, 1, 2, -2.0 / 3.0);
  matrix_set(R_U, 1, 3, 5.0 / 3.0);
  matrix_set(R_U, 2, 0, 0);
  matrix_set(R_U, 2, 1, 0);
  matrix_set(R_U, 2, 2, 1);
  matrix_set(R_U, 2, 3, 7.0 / 4.0);
  matrix_set(R_U, 3, 0, 0);
  matrix_set(R_U, 3, 1, 0);
  matrix_set(R_U, 3, 2, 0);
  matrix_set(R_U, 3, 3, 1);

  MatrixLUDecompositionResult *LU = matrix_lu_decomposition(A);

  test("L = R_L", "L ≠ R_L", matrix_are_equal(LU->L, R_L));
  test("U = R_U", "U ≠ R_U", matrix_are_equal(LU->U, R_U));
}

/*
 * Problem 3.5
 *
 * Factor the following matrix into an upper triangular matrix and a lower
 * triangular matrix.
 *
 * A = [  1  2 -2  3
 *       -1 -2  0  2
 *        3 -3  0  1
 *        2  1  1 -2 ]
 *
 * The original matrix cannot be factored as an LU product.
 */
void problem_3_5() {
  Matrix *A = matrix_create(4, 4);
  matrix_set(A, 0, 0, 1);
  matrix_set(A, 0, 1, 2);
  matrix_set(A, 0, 2, -2);
  matrix_set(A, 0, 3, 3);
  matrix_set(A, 1, 0, -1);
  matrix_set(A, 1, 1, -2);
  matrix_set(A, 1, 2, 0);
  matrix_set(A, 1, 3, 2);
  matrix_set(A, 2, 0, 3);
  matrix_set(A, 2, 1, -3);
  matrix_set(A, 2, 2, 0);
  matrix_set(A, 2, 3, 1);
  matrix_set(A, 3, 0, 2);
  matrix_set(A, 3, 1, 1);
  matrix_set(A, 3, 2, 1);
  matrix_set(A, 3, 3, -2);

  test("A is not decomposable", "A s decomposable",
       matrix_lu_decomposition(A) == NULL);
}

/*
 * Problem 3.6
 *
 * Factor the following matrix into an upper triangular matrix and a lower
 * triangular matrix.
 *
 * A = [  2 2  1 0
 *        3 0 -1 1
 *        0 1  0 5
 *       -1 1  0 0 ]
 *
 * L = [  2  0    0     0
 *        3 -3    0     0
 *        0  1 -5/6     0
 *       -1  2 -7/6 -34/5 ]
 *
 * U = [ 1 1 1/2    0
 *       0 1 5/6 -1/3
 *       0 0  1 -32/5
 *       0 0  0     1 ]
 */
void problem_3_6() {
  Matrix *A = matrix_create(4, 4);
  matrix_set(A, 0, 0, 2);
  matrix_set(A, 0, 1, 2);
  matrix_set(A, 0, 2, 1);
  matrix_set(A, 0, 3, 0);
  matrix_set(A, 1, 0, 3);
  matrix_set(A, 1, 1, 0);
  matrix_set(A, 1, 2, -1);
  matrix_set(A, 1, 3, 1);
  matrix_set(A, 2, 0, 0);
  matrix_set(A, 2, 1, 1);
  matrix_set(A, 2, 2, 0);
  matrix_set(A, 2, 3, 5);
  matrix_set(A, 3, 0, -1);
  matrix_set(A, 3, 1, 1);
  matrix_set(A, 3, 2, 0);
  matrix_set(A, 3, 3, 0);

  Matrix *R_L = matrix_create(4, 4);
  matrix_set(R_L, 0, 0, 2);
  matrix_set(R_L, 0, 1, 0);
  matrix_set(R_L, 0, 2, 0);
  matrix_set(R_L, 0, 3, 0);
  matrix_set(R_L, 1, 0, 3);
  matrix_set(R_L, 1, 1, -3);
  matrix_set(R_L, 1, 2, 0);
  matrix_set(R_L, 1, 3, 0);
  matrix_set(R_L, 2, 0, 0);
  matrix_set(R_L, 2, 1, 1);
  matrix_set(R_L, 2, 2, -5.0 / 6.0);
  matrix_set(R_L, 2, 3, 0);
  matrix_set(R_L, 3, 0, -1);
  matrix_set(R_L, 3, 1, 2);
  matrix_set(R_L, 3, 2, -7.0 / 6.0);
  matrix_set(R_L, 3, 3, -34.0 / 5.0);

  Matrix *R_U = matrix_create(4, 4);
  matrix_set(R_U, 0, 0, 1);
  matrix_set(R_U, 0, 1, 1);
  matrix_set(R_U, 0, 2, 1.0 / 2.0);
  matrix_set(R_U, 0, 3, 0);
  matrix_set(R_U, 1, 0, 0);
  matrix_set(R_U, 1, 1, 1);
  matrix_set(R_U, 1, 2, 5.0 / 6.0);
  matrix_set(R_U, 1, 3, -1.0 / 3.0);
  matrix_set(R_U, 2, 0, 0);
  matrix_set(R_U, 2, 1, 0);
  matrix_set(R_U, 2, 2, 1);
  matrix_set(R_U, 2, 3, -32.0 / 5.0);
  matrix_set(R_U, 3, 0, 0);
  matrix_set(R_U, 3, 1, 0);
  matrix_set(R_U, 3, 2, 0);
  matrix_set(R_U, 3, 3, 1);

  MatrixLUDecompositionResult *LU = matrix_lu_decomposition(A);

  test("L = R_L", "L ≠ R_L", matrix_are_equal(LU->L, R_L));
  test("U = R_U", "U ≠ R_U", matrix_are_equal(LU->U, R_U));
}

/*
 * Problem 3.10
 *
 * Find A² and A when:
 *
 * A = [ 2 -1
 *       4  3 ]
 *
 * A² = [  0 -5
 *        20  5 ]
 *
 * A⁴ = [ -100 -25
 *         100 -75 ]
 */
void problem_3_10() {
  Matrix *A = matrix_create(2, 2);
  matrix_set(A, 0, 0, 2);
  matrix_set(A, 0, 1, -1);
  matrix_set(A, 1, 0, 4);
  matrix_set(A, 1, 1, 3);

  Matrix *A_2 = matrix_matrix_multiply(A, A);

  Matrix *A_4 = matrix_matrix_multiply(A_2, A_2);

  Matrix *R_A_2 = matrix_create(2, 2);
  matrix_set(R_A_2, 0, 0, 0);
  matrix_set(R_A_2, 0, 1, -5);
  matrix_set(R_A_2, 1, 0, 20);
  matrix_set(R_A_2, 1, 1, 5);

  Matrix *R_A_4 = matrix_create(2, 2);
  matrix_set(R_A_4, 0, 0, -100);
  matrix_set(R_A_4, 0, 1, -25);
  matrix_set(R_A_4, 1, 0, 100);
  matrix_set(R_A_4, 1, 1, -75);

  test("A² = R_A²", "A² ≠ R_A²", matrix_are_equal(A_2, R_A_2));
  test("A⁴ = R_A⁴", "A⁴ ≠ R_A⁴", matrix_are_equal(A_4, R_A_4));
}

/*
 * Problem 3.11
 *
 * Show that A³ - 9A + 10I = 0, where:
 *
 * A = [ 1 -2  2
 *       0  2  0
 *       1 -1 -3 ]
 */
void problem_3_11() {
  Matrix *A = matrix_create(3, 3);
  matrix_set(A, 0, 0, 1);
  matrix_set(A, 0, 1, -2);
  matrix_set(A, 0, 2, 2);
  matrix_set(A, 1, 0, 0);
  matrix_set(A, 1, 1, 2);
  matrix_set(A, 1, 2, 0);
  matrix_set(A, 2, 0, 1);
  matrix_set(A, 2, 1, -1);
  matrix_set(A, 2, 2, -3);

  Matrix *A_2 = matrix_matrix_multiply(A, A);
  Matrix *A_3 = matrix_matrix_multiply(A_2, A);

  Matrix *A9 = matrix_copy(A);
  matrix_scalar_multiply(A9, -9);

  Matrix *I10 = matrix_create_identity(3);
  matrix_scalar_multiply(I10, 10);

  Matrix *R = matrix_copy(A_3);
  matrix_add(R, A9);
  matrix_add(R, I10);

  // NOTE Zero row rank is equivalent to checking all elements for zero
  test("A³ - 9A + 10I = 0", "A³ - 9A + 10I ≠ 0", matrix_row_rank(R) == 0);
}

int main() {
  problem_3_4();
  problem_3_5();
  problem_3_6();
  problem_3_10();
  problem_3_11();
}
