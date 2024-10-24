#include <matrix.h>
#include <stddef.h>
#include <stdio.h>
#include <test.h>
#include <vector.h>

/*
 * Problem 1.1
 *
 * Find A·B and B·Cᵀ, where:
 *
 * A = [2 3 4]
 *
 * B = [5 6 -7]
 *
 * C = [7 -8 -8]
 *
 * A·B = 0
 *
 * B·Cᵀ = 50
 */
void problem_1_1() {
  Vector *A = vector_create(3);
  vector_set(A, 0, 2);
  vector_set(A, 1, 3);
  vector_set(A, 2, 4);

  Vector *B = vector_create(3);
  vector_set(B, 0, 5);
  vector_set(B, 1, 6);
  vector_set(B, 2, -7);

  // NOTE C = Cᵀ with these vectors
  Vector *C = vector_create(3);
  vector_set(C, 0, 7);
  vector_set(C, 1, -8);
  vector_set(C, 2, -9);

  test("A·B = 0", "A·B ≠ 0", vector_dot(A, B) == 0);
  test("B·Cᵀ = 50", "B·Cᵀ ≠ 50", vector_dot(B, C) == 50);
}

/*
 * Problem 1.2
 *
 * Show that A+B = B+A, where:
 *
 * A = [ 0 1
 *       2 3 ]
 *
 * B = [ 4  5
 *       6 -7 ]
 */
void problem_1_2() {
  Matrix *A = matrix_create(2, 2);
  matrix_set(A, 0, 0, 0);
  matrix_set(A, 0, 1, 1);
  matrix_set(A, 1, 0, 2);
  matrix_set(A, 1, 1, 3);

  Matrix *B = matrix_create(2, 2);
  matrix_set(B, 0, 0, 4);
  matrix_set(B, 0, 1, 5);
  matrix_set(B, 1, 0, 6);
  matrix_set(B, 1, 1, -7);

  Matrix *A_B = matrix_add(A, B);
  Matrix *B_A = matrix_add(B, A);

  test("A+B = B+A", "A+B ≠ B+A", matrix_equal(A_B, B_A));
}

/*
 * Problem 1.3
 *
 * Find 3A - 0.5B for the matrices of Problem 1.2.
 *
 * 3A - 0.5B = [ -2  0.5
 *                3 12.5 ]
 */
void problem_1_3() {
  Matrix *A = matrix_create(2, 2);
  matrix_set(A, 0, 0, 0);
  matrix_set(A, 0, 1, 1);
  matrix_set(A, 1, 0, 2);
  matrix_set(A, 1, 1, 3);

  Matrix *B = matrix_create(2, 2);
  matrix_set(B, 0, 0, 4);
  matrix_set(B, 0, 1, 5);
  matrix_set(B, 1, 0, 6);
  matrix_set(B, 1, 1, -7);

  Matrix *A_ = matrix_scalar_multiply(A, 3);

  Matrix *B_ = matrix_scalar_multiply(B, -0.5);

  Matrix *A_B_ = matrix_add(A_, B_);

  Matrix *R = matrix_create(2, 2);
  matrix_set(R, 0, 0, -2);
  matrix_set(R, 0, 1, 0.5);
  matrix_set(R, 1, 0, 3);
  matrix_set(R, 1, 1, 12.5);

  test("3A - 0.5B = R", "3A - 0.5B ≠ R", matrix_equal(A_B_, R));
}

/*
 * Problem 1.4
 *
 * Find AB and BA for the matrices of Problem 1.2.
 *
 * AB = [  6  -7
 *        26 -11 ]
 *
 * BA = [  10  19
 *        -14 -15 ]
 */
void problem_1_4() {
  Matrix *A = matrix_create(2, 2);
  matrix_set(A, 0, 0, 0);
  matrix_set(A, 0, 1, 1);
  matrix_set(A, 1, 0, 2);
  matrix_set(A, 1, 1, 3);

  Matrix *B = matrix_create(2, 2);
  matrix_set(B, 0, 0, 4);
  matrix_set(B, 0, 1, 5);
  matrix_set(B, 1, 0, 6);
  matrix_set(B, 1, 1, -7);

  Matrix *AB = matrix_matrix_multiply(A, B);
  Matrix *BA = matrix_matrix_multiply(B, A);

  Matrix *R_AB = matrix_create(2, 2);
  matrix_set(R_AB, 0, 0, 6);
  matrix_set(R_AB, 0, 1, -7);
  matrix_set(R_AB, 1, 0, 26);
  matrix_set(R_AB, 1, 1, -11);

  Matrix *R_BA = matrix_create(2, 2);
  matrix_set(R_BA, 0, 0, 10);
  matrix_set(R_BA, 0, 1, 19);
  matrix_set(R_BA, 1, 0, -14);
  matrix_set(R_BA, 1, 1, -15);

  test("AB = R_AB", "AB ≠ R_AB", matrix_equal(AB, R_AB));
  test("BA = R_BA", "BA ≠ R_BA", matrix_equal(BA, R_BA));
  // "Note that, for these matrices, AB ≠ BA."
  test("AB ≠ BA", "AB = BA", !matrix_equal(AB, BA));
}

/*
 * Problem 1.5
 *
 * Find AB and BA, where:
 *
 * A = [ 1  2 3
 *       4 -5 6 ]
 *
 * B = [ 7  8
 *       0 -9 ]
 *
 * AB is not defined
 *
 * BA = [  39 -26  69
 *        -36  45 -54 ]
 */
void problem_1_5() {
  Matrix *A = matrix_create(2, 3);
  matrix_set(A, 0, 0, 1);
  matrix_set(A, 0, 1, 2);
  matrix_set(A, 0, 2, 3);
  matrix_set(A, 1, 0, 4);
  matrix_set(A, 1, 1, -5);
  matrix_set(A, 1, 2, 6);

  Matrix *B = matrix_create(2, 2);
  matrix_set(B, 0, 0, 7);
  matrix_set(B, 0, 1, 8);
  matrix_set(B, 1, 0, 0);
  matrix_set(B, 1, 1, -9);

  Matrix *AB = matrix_matrix_multiply(A, B);
  Matrix *BA = matrix_matrix_multiply(B, A);

  Matrix *R_BA = matrix_create(2, 3);
  matrix_set(R_BA, 0, 0, 39);
  matrix_set(R_BA, 0, 1, -26);
  matrix_set(R_BA, 0, 2, 69);
  matrix_set(R_BA, 1, 0, -36);
  matrix_set(R_BA, 1, 1, 45);
  matrix_set(R_BA, 1, 2, -54);

  test("AB = NULL", "AB ≠ NULL", AB == NULL);
  test("BA = R_BA", "BA ≠ R_BA", matrix_equal(BA, R_BA));
}

/*
 * Problem 1.6
 *
 * Verify that (BA)ᵀ = AᵀBᵀ for the matrices of Problem 1.5.
 */
void problem_1_6() {
  Matrix *A = matrix_create(2, 3);
  matrix_set(A, 0, 0, 1);
  matrix_set(A, 0, 1, 2);
  matrix_set(A, 0, 2, 3);
  matrix_set(A, 1, 0, 4);
  matrix_set(A, 1, 1, -5);
  matrix_set(A, 1, 2, 6);

  Matrix *B = matrix_create(2, 2);
  matrix_set(B, 0, 0, 7);
  matrix_set(B, 0, 1, 8);
  matrix_set(B, 1, 0, 0);
  matrix_set(B, 1, 1, -9);

  Matrix *A_T = matrix_transpose(A);
  Matrix *B_T = matrix_transpose(B);
  Matrix *A_T_B_T = matrix_matrix_multiply(A_T, B_T);

  Matrix *BA = matrix_matrix_multiply(B, A);
  Matrix *BA_T = matrix_transpose(BA);

  test("(BA)ᵀ = AᵀBᵀ", "(BA)ᵀ ≠ AᵀBᵀ", matrix_equal(BA_T, A_T_B_T));
}

/*
 * Problem 1.7
 *
 * Find AB and AC, where:
 *
 * A = [  4  2 0
 *        2  1 0
 *       -2 -1 1 ]
 *
 * B = [  2  3  1
 *        2 -2 -2
 *       -1  2  1 ]
 *
 * C = [  3  1 -3
 *        0  2  6
 *       -1  2  1 ]
 *
 * AB = [ 12  8 0
 *         6  4 0
 *        -7 -2 1 ]
 *
 * AC = [ 12  8 0
 *         6  4 0
 *        -7 -2 1 ]
 */
void problem_1_7() {
  Matrix *A = matrix_create(3, 3);
  matrix_set(A, 0, 0, 4);
  matrix_set(A, 0, 1, 2);
  matrix_set(A, 0, 2, 0);
  matrix_set(A, 1, 0, 2);
  matrix_set(A, 1, 1, 1);
  matrix_set(A, 1, 2, 0);
  matrix_set(A, 2, 0, -2);
  matrix_set(A, 2, 1, -1);
  matrix_set(A, 2, 2, 1);

  Matrix *B = matrix_create(3, 3);
  matrix_set(B, 0, 0, 2);
  matrix_set(B, 0, 1, 3);
  matrix_set(B, 0, 2, 1);
  matrix_set(B, 1, 0, 2);
  matrix_set(B, 1, 1, -2);
  matrix_set(B, 1, 2, -2);
  matrix_set(B, 2, 0, -1);
  matrix_set(B, 2, 1, 2);
  matrix_set(B, 2, 2, 1);

  Matrix *C = matrix_create(3, 3);
  matrix_set(C, 0, 0, 3);
  matrix_set(C, 0, 1, 1);
  matrix_set(C, 0, 2, -3);
  matrix_set(C, 1, 0, 0);
  matrix_set(C, 1, 1, 2);
  matrix_set(C, 1, 2, 6);
  matrix_set(C, 2, 0, -1);
  matrix_set(C, 2, 1, 2);
  matrix_set(C, 2, 2, 1);

  Matrix *AB = matrix_matrix_multiply(A, B);
  Matrix *AC = matrix_matrix_multiply(A, C);

  Matrix *R_AB = matrix_create(3, 3);
  matrix_set(R_AB, 0, 0, 12);
  matrix_set(R_AB, 0, 1, 8);
  matrix_set(R_AB, 0, 2, 0);
  matrix_set(R_AB, 1, 0, 6);
  matrix_set(R_AB, 1, 1, 4);
  matrix_set(R_AB, 1, 2, 0);
  matrix_set(R_AB, 2, 0, -7);
  matrix_set(R_AB, 2, 1, -2);
  matrix_set(R_AB, 2, 2, 1);

  Matrix *R_AC = matrix_create(3, 3);
  matrix_set(R_AC, 0, 0, 12);
  matrix_set(R_AC, 0, 1, 8);
  matrix_set(R_AC, 0, 2, 0);
  matrix_set(R_AC, 1, 0, 6);
  matrix_set(R_AC, 1, 1, 4);
  matrix_set(R_AC, 1, 2, 0);
  matrix_set(R_AC, 2, 0, -7);
  matrix_set(R_AC, 2, 1, -2);
  matrix_set(R_AC, 2, 2, 1);

  test("AB = R_AB", "AB ≠ R_AB", matrix_equal(AB, R_AB));
  test("AC = R_AC", "AC ≠ R_AC", matrix_equal(AC, R_AC));
  // "Note that, for these matrices, AB = AC and yet B ≠ C."
  test("AB = AC", "AB ≠ AC", matrix_equal(AB, AC));
  test("B ≠ C", "B = C", !matrix_equal(B, C));
}

int main() {
  problem_1_1();
  problem_1_2();
  problem_1_3();
  problem_1_4();
  problem_1_5();
  problem_1_6();
  problem_1_7();
}
