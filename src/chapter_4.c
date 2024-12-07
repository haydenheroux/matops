#include <stddef.h>
#include <stdio.h>

#include "matrix.h"
#include "test.h"

/*
 * Problem 4.1
 *
 * Determine whether G is the inverse of any of the following matrices, where:
 *
 * A = [ 4 -8
 *       4  0 ]
 *
 * B = [ 1 2 3
 *       4 5 6 ]
 *
 * C = [ 2 -4
 *       2  0 ]
 *
 * D = [ 2 -4 0
 *       2  0 0
 *       0  0 1 ]
 *
 * G = [     0  0.5
 *       -0.25 0.25 ]
 */
void problem_4_1() {
  Matrix *A = matrix_create(2, 2);
  matrix_set(A, 0, 0, 4);
  matrix_set(A, 0, 1, -8);
  matrix_set(A, 1, 0, 4);
  matrix_set(A, 1, 1, 0);

  Matrix *B = matrix_create(2, 3);
  matrix_set(B, 0, 0, 1);
  matrix_set(B, 0, 1, 2);
  matrix_set(B, 0, 2, 3);
  matrix_set(B, 1, 0, 4);
  matrix_set(B, 1, 1, 5);
  matrix_set(B, 1, 2, 6);

  Matrix *C = matrix_create(2, 2);
  matrix_set(C, 0, 0, 2);
  matrix_set(C, 0, 1, -4);
  matrix_set(C, 1, 0, 2);
  matrix_set(C, 1, 1, 0);

  Matrix *D = matrix_create(3, 3);
  matrix_set(D, 0, 0, 2);
  matrix_set(D, 0, 1, -4);
  matrix_set(D, 0, 2, 0);
  matrix_set(D, 1, 0, 2);
  matrix_set(D, 1, 1, 0);
  matrix_set(D, 1, 2, 0);
  matrix_set(D, 2, 0, 0);
  matrix_set(D, 2, 1, 0);
  matrix_set(D, 2, 2, 1);

  Matrix *G = matrix_create(2, 2);
  matrix_set(G, 0, 0, 0);
  matrix_set(G, 0, 1, 0.5);
  matrix_set(G, 1, 0, -0.25);
  matrix_set(G, 1, 1, 0.25);

  test("G ≠ A⁻¹", "G = A⁻¹", !matrix_are_inverses(A, G));
  test("G ≠ B⁻¹", "G = B⁻¹", !matrix_are_inverses(B, G));
  test("G = C⁻¹", "G ≠ C⁻¹", matrix_are_inverses(C, G));
  test("G ≠ D⁻¹", "G = D⁻¹", !matrix_are_inverses(D, G));
}

/*
 * Problem 4.3
 *
 * Determine the inverse of A, where:
 *
 * A = [ 2 1 3
 *       0 1 2
 *       0 0 3 ]
 *
 * A⁻¹ = [ 1/2 -1/2 -1/6
 *          0     1 -2/3
 *          0     0  1/3 ]
 */
void problem_4_3() {
  Matrix *A = matrix_create(3, 3);
  matrix_set(A, 0, 0, 2);
  matrix_set(A, 0, 1, 1);
  matrix_set(A, 0, 2, 3);
  matrix_set(A, 1, 0, 0);
  matrix_set(A, 1, 1, 1);
  matrix_set(A, 1, 2, 2);
  matrix_set(A, 2, 0, 0);
  matrix_set(A, 2, 1, 0);
  matrix_set(A, 2, 2, 3);

  Matrix *A_inv = matrix_inverse(A);

  Matrix *R = matrix_create(3, 3);
  matrix_set(R, 0, 0, 1.0 / 2.0);
  matrix_set(R, 0, 1, -1.0 / 2.0);
  matrix_set(R, 0, 2, -1.0 / 6.0);
  matrix_set(R, 1, 0, 0);
  matrix_set(R, 1, 1, 1);
  matrix_set(R, 1, 2, -2.0 / 3.0);
  matrix_set(R, 2, 0, 0);
  matrix_set(R, 2, 1, 0);
  matrix_set(R, 2, 2, 1.0 / 3.0);

  test("A is nonsingular", "A is singular", A_inv != NULL);
  test("A⁻¹ = R", "A⁻¹ ≠ R", matrix_are_equal(A_inv, R));
}

/*
 * Problem 4.4
 *
 * Determine the inverses of the following matrices:
 *
 * A = [ 3  0  0 0
 *       1 -2  0 0
 *       2  4  1 0
 *       1  3 -1 0 ]
 *
 * B = [ -1  0  0 0
 *        2 -2  0 0
 *        3  1 -2 0
 *        1 -1  3 3 ]
 *
 * A does not have an inverse.
 *
 * B⁻¹ = [ -1    0    0   0
 *         -1 -1/2    0   0
 *         -2 -1/4 -1/2   0
 *          2 1/12  1/2 1/3 ]
 */
void problem_4_4() {
  Matrix *A = matrix_create(4, 4);
  matrix_set(A, 0, 0, 3);
  matrix_set(A, 0, 1, 0);
  matrix_set(A, 0, 2, 0);
  matrix_set(A, 0, 3, 0);
  matrix_set(A, 1, 0, 1);
  matrix_set(A, 1, 1, -2);
  matrix_set(A, 1, 2, 0);
  matrix_set(A, 1, 3, 0);
  matrix_set(A, 2, 0, 3);
  matrix_set(A, 2, 1, 1);
  matrix_set(A, 2, 2, -2);
  matrix_set(A, 2, 3, 0);
  matrix_set(A, 3, 0, 1);
  matrix_set(A, 3, 1, 3);
  matrix_set(A, 3, 2, -1);
  matrix_set(A, 3, 3, 0);

  Matrix *B = matrix_create(4, 4);
  matrix_set(B, 0, 0, -1);
  matrix_set(B, 0, 1, 0);
  matrix_set(B, 0, 2, 0);
  matrix_set(B, 0, 3, 0);
  matrix_set(B, 1, 0, 2);
  matrix_set(B, 1, 1, -2);
  matrix_set(B, 1, 2, 0);
  matrix_set(B, 1, 3, 0);
  matrix_set(B, 2, 0, 3);
  matrix_set(B, 2, 1, 1);
  matrix_set(B, 2, 2, -2);
  matrix_set(B, 2, 3, 0);
  matrix_set(B, 3, 0, 1);
  matrix_set(B, 3, 1, -1);
  matrix_set(B, 3, 2, 3);
  matrix_set(B, 3, 3, 3);

  Matrix *A_inv = matrix_inverse(A);
  Matrix *B_inv = matrix_inverse(B);

  Matrix *R = matrix_create(4, 4);
  matrix_set(R, 0, 0, -1);
  matrix_set(R, 0, 1, 0);
  matrix_set(R, 0, 2, 0);
  matrix_set(R, 0, 3, 0);
  matrix_set(R, 1, 0, -1);
  matrix_set(R, 1, 1, -1.0 / 2.0);
  matrix_set(R, 1, 2, 0);
  matrix_set(R, 1, 3, 0);
  matrix_set(R, 2, 0, -2);
  matrix_set(R, 2, 1, -1.0 / 4.0);
  matrix_set(R, 2, 2, -1.0 / 2.0);
  matrix_set(R, 2, 3, 0);
  matrix_set(R, 3, 0, 2);
  matrix_set(R, 3, 1, 1.0 / 12.0);
  matrix_set(R, 3, 2, 1.0 / 2.0);
  matrix_set(R, 3, 3, 1.0 / 3.0);

  test("A is singular", "A is nonsingular", A_inv == NULL);
  test("B is nonsingular", "B is singular", B_inv != NULL);
  test("B⁻¹ = R", "B⁻¹ ≠ R", matrix_are_equal(B_inv, R));
}

/*
 * Problem 4.5
 *
 * Determine the inverse of A, where:
 *
 * A = [ 5 3
 *       2 1 ]
 *
 * A⁻¹ = [ -1  3
 *          2 -5 ]
 */
void problem_4_5() {
  Matrix *A = matrix_create(2, 2);
  matrix_set(A, 0, 0, 5);
  matrix_set(A, 0, 1, 3);
  matrix_set(A, 1, 0, 2);
  matrix_set(A, 1, 1, 1);

  Matrix *A_inv = matrix_inverse(A);

  Matrix *R = matrix_create(2, 2);
  matrix_set(R, 0, 0, -1);
  matrix_set(R, 0, 1, 3);
  matrix_set(R, 1, 0, 2);
  matrix_set(R, 1, 1, -5);

  test("A is nonsingular", "A is singular", A_inv != NULL);
  test("A⁻¹ = R", "A⁻¹ ≠ R", matrix_are_equal(A_inv, R));
}

/*
 * Problem 4.6
 *
 * Determine the inverse of A, where:
 *
 * A = [ 1 2 3
 *       4 5 6
 *       7 8 9 ]
 *
 * A does not have an inverse.
 */
void problem_4_6() {
  Matrix *A = matrix_create(3, 3);
  matrix_set(A, 0, 0, 1);
  matrix_set(A, 0, 1, 2);
  matrix_set(A, 0, 2, 3);
  matrix_set(A, 1, 0, 4);
  matrix_set(A, 1, 1, 5);
  matrix_set(A, 1, 2, 6);
  matrix_set(A, 2, 0, 7);
  matrix_set(A, 2, 1, 8);
  matrix_set(A, 2, 2, 9);

  Matrix *A_inv = matrix_inverse(A);

  test("A is singular", "A is nonsingular", A_inv == NULL);
}

/*
 * Problem 4.7
 *
 * Determine the inverse of A, where:
 *
 * A = [ 0  1  1
 *       5  1 -1
 *       2 -3 -3 ]

 * A⁻¹ = 0.25·[   6  0  2
 *              -13  2 -5
 *               17 -2  5 ]
 */
void problem_4_7() {
  Matrix *A = matrix_create(3, 3);
  matrix_set(A, 0, 0, 0);
  matrix_set(A, 0, 1, 1);
  matrix_set(A, 0, 2, 1);
  matrix_set(A, 1, 0, 5);
  matrix_set(A, 1, 1, 1);
  matrix_set(A, 1, 2, -1);
  matrix_set(A, 2, 0, 2);
  matrix_set(A, 2, 1, -3);
  matrix_set(A, 2, 2, -3);

  Matrix *A_inv = matrix_inverse(A);

  Matrix *R = matrix_create(3, 3);
  matrix_set(R, 0, 0, 6);
  matrix_set(R, 0, 1, 0);
  matrix_set(R, 0, 2, 2);
  matrix_set(R, 1, 0, -13);
  matrix_set(R, 1, 1, 2);
  matrix_set(R, 1, 2, -5);
  matrix_set(R, 2, 0, 17);
  matrix_set(R, 2, 1, -2);
  matrix_set(R, 2, 2, 5);
  matrix_scalar_multiply(R, 0.25);

  test("A is nonsingular", "A is singular", A_inv != NULL);
  test("A⁻¹ = R", "A⁻¹ ≠ R", matrix_are_equal(A_inv, R));
}

/*
 * Problem 4.8
 *
 * Solve the system of equations.
 *
 * 5x₁ + 3x₂ =  8
 * 2x₁ +  x₂ = -1
 *
 * x₁ = -11
 * x₂ =  21
 */
void problem_4_8() {
  Matrix *A = matrix_create(2, 2);
  matrix_set(A, 0, 0, 5);
  matrix_set(A, 0, 1, 3);
  matrix_set(A, 1, 0, 2);
  matrix_set(A, 1, 1, 1);

  Matrix *A_inv = matrix_inverse(A);

  Matrix *B = matrix_create(2, 1);
  matrix_set(B, 0, 0, 8);
  matrix_set(B, 1, 0, -1);

  Matrix *X = matrix_matrix_multiply(A_inv, B);

  Matrix *R = matrix_create(2, 1);
  matrix_set(R, 0, 0, -11);
  matrix_set(R, 1, 0, 21);

  test("X = R", "X ≠ R", matrix_are_equal(X, R));
}

/*
 * Problem 4.9
 *
 * Solve the system of equations.
 *
 *        x₂ +  x₃ =  2
 * 5x₁ +  x₂ -  x₃ =  3
 * 2x₁ - 3x₂ - 3x₃ = -6
 *
 * x₁ =    0
 * x₂ =  5/2
 * x₃ = -1/2
 */
void problem_4_9() {
  Matrix *A = matrix_create(3, 3);
  matrix_set(A, 0, 0, 0);
  matrix_set(A, 0, 1, 1);
  matrix_set(A, 0, 2, 1);
  matrix_set(A, 1, 0, 5);
  matrix_set(A, 1, 1, 1);
  matrix_set(A, 1, 2, -1);
  matrix_set(A, 2, 0, 2);
  matrix_set(A, 2, 1, -3);
  matrix_set(A, 2, 2, -3);

  Matrix *A_inv = matrix_inverse(A);

  Matrix *B = matrix_create(3, 1);
  matrix_set(B, 0, 0, 2);
  matrix_set(B, 1, 0, 3);
  matrix_set(B, 2, 0, -6);

  Matrix *X = matrix_matrix_multiply(A_inv, B);

  Matrix *R = matrix_create(3, 1);
  matrix_set(R, 0, 0, 0);
  matrix_set(R, 1, 0, 5.0 / 2.0);
  matrix_set(R, 2, 0, -1.0 / 2.0);

  test("X = R", "X ≠ R", matrix_are_equal(X, R));
}

int main() {
  problem_4_1();
  problem_4_3();
  problem_4_4();
  problem_4_5();
  problem_4_6();
  problem_4_7();
  problem_4_8();
  problem_4_9();
}
