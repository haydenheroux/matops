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

  test("A+B = B+A", "A+B ≠ B+A", matrix_are_equal(A_B, B_A));
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

  test("3A - 0.5B = R", "3A - 0.5B ≠ R", matrix_are_equal(A_B_, R));
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

  test("AB = R_AB", "AB ≠ R_AB", matrix_are_equal(AB, R_AB));
  test("BA = R_BA", "BA ≠ R_BA", matrix_are_equal(BA, R_BA));
  // "Note that, for these matrices, AB ≠ BA."
  test("AB ≠ BA", "AB = BA", !matrix_are_equal(AB, BA));
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
  test("BA = R_BA", "BA ≠ R_BA", matrix_are_equal(BA, R_BA));
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
  matrix_set(B, 1, 1, -9);

  Matrix *A_T = matrix_transpose(A);
  Matrix *B_T = matrix_transpose(B);
  Matrix *A_T_B_T = matrix_matrix_multiply(A_T, B_T);

  Matrix *BA = matrix_matrix_multiply(B, A);
  Matrix *BA_T = matrix_transpose(BA);

  test("(BA)ᵀ = AᵀBᵀ", "(BA)ᵀ ≠ AᵀBᵀ", matrix_are_equal(BA_T, A_T_B_T));
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
  matrix_set(A, 1, 0, 2);
  matrix_set(A, 1, 1, 1);
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
  matrix_set(R_AB, 1, 0, 6);
  matrix_set(R_AB, 1, 1, 4);
  matrix_set(R_AB, 2, 0, -7);
  matrix_set(R_AB, 2, 1, -2);
  matrix_set(R_AB, 2, 2, 1);

  Matrix *R_AC = matrix_create(3, 3);
  matrix_set(R_AC, 0, 0, 12);
  matrix_set(R_AC, 0, 1, 8);
  matrix_set(R_AC, 1, 0, 6);
  matrix_set(R_AC, 1, 1, 4);
  matrix_set(R_AC, 2, 0, -7);
  matrix_set(R_AC, 2, 1, -2);
  matrix_set(R_AC, 2, 2, 1);

  test("AB = R_AB", "AB ≠ R_AB", matrix_are_equal(AB, R_AB));
  test("AC = R_AC", "AC ≠ R_AC", matrix_are_equal(AC, R_AC));
  // "Note that, for these matrices, AB = AC and yet B ≠ C."
  test("AB = AC", "AB ≠ AC", matrix_are_equal(AB, AC));
  test("B ≠ C", "B = C", !matrix_are_equal(B, C));
}

/*
 * Problem 1.11
 *
 * Determine which of the following matrices are in row-echelon form:
 *
 * A = [ 1 2 -1 0
 *       0 0  1 4
 *       0 0  0 0 ]
 *
 * B = [ 0 1 4
 *       1 2 3 ]
 *
 * C = [ 0 2 4
 *       0 0 1 ]
 *
 * D = [ 0 1 0 4
 *       0 0 1 3
 *       0 0 0 1 ]
 *
 * E = [ 1 2 3
 *       4 9 7 ]
 */
void problem_1_11() {
  Matrix *A = matrix_create(3, 4);
  matrix_set(A, 0, 0, 1);
  matrix_set(A, 0, 1, 2);
  matrix_set(A, 0, 2, -1);
  matrix_set(A, 1, 2, 1);
  matrix_set(A, 1, 3, 4);

  Matrix *B = matrix_create(2, 3);
  matrix_set(B, 0, 1, 1);
  matrix_set(B, 0, 2, 4);
  matrix_set(B, 1, 0, 1);
  matrix_set(B, 1, 1, 2);
  matrix_set(B, 1, 2, 3);

  Matrix *C = matrix_create(2, 3);
  matrix_set(C, 0, 1, 2);
  matrix_set(C, 0, 2, 4);
  matrix_set(C, 1, 2, 1);

  Matrix *D = matrix_create(3, 4);
  matrix_set(D, 0, 1, 1);
  matrix_set(D, 0, 3, 4);
  matrix_set(D, 1, 2, 1);
  matrix_set(D, 1, 3, 3);
  matrix_set(D, 2, 3, 1);

  Matrix *E = matrix_create(2, 3);
  matrix_set(E, 0, 0, 1);
  matrix_set(E, 0, 1, 2);
  matrix_set(E, 0, 2, 3);
  matrix_set(E, 1, 0, 4);
  matrix_set(E, 1, 1, 9);
  matrix_set(E, 1, 2, 7);

  // "Only A and D are in row-echelon form"
  test("A is in row-echelon form", "A is not in row-echelon form",
       matrix_is_row_echelon(A));
  test("D is in row-echelon form", "D is not in row-echelon form",
       matrix_is_row_echelon(D));
  // "B is not, because the first nonzero element in the second row is further
  // left than the first nonzero element in the top row, violating R4"
  test("B is not in row-echelon form", "B is in row-echelon form",
       !matrix_is_row_echelon(B));
  // "Condition R2 is violated in the first row of C
  test("C is not in row-echelon form", "C is in row-echelon form",
       !matrix_is_row_echelon(C));
  // "Matrix E violates condition R3, because the first nonzero element in the
  // lower row appears in the same column as the first nonzero element in the
  // upper row"
  test("E is not in row-echelon form", "E is in row-echelon form",
       !matrix_is_row_echelon(E));
}

/*
 * Problem 1.12
 *
 * Use elementary row operations to transform matrices B, C, and E of
 * Problem 1.11 into row-echelon form.
 *
 * B = [ 1 2 3
 *       0 1 4 ]
 *
 * C = [ 0 1 2
 *       0 0 1 ]
 *
 * E = [ 1 2  3
 *       0 1 -5 ]
 */
void problem_1_12() {
  Matrix *B = matrix_create(2, 3);
  matrix_set(B, 0, 1, 1);
  matrix_set(B, 0, 2, 4);
  matrix_set(B, 1, 0, 1);
  matrix_set(B, 1, 1, 2);
  matrix_set(B, 1, 2, 3);

  Matrix *C = matrix_create(2, 3);
  matrix_set(C, 0, 1, 2);
  matrix_set(C, 0, 2, 4);
  matrix_set(C, 1, 2, 1);

  Matrix *E = matrix_create(2, 3);
  matrix_set(E, 0, 0, 1);
  matrix_set(E, 0, 1, 2);
  matrix_set(E, 0, 2, 3);
  matrix_set(E, 1, 0, 4);
  matrix_set(E, 1, 1, 9);
  matrix_set(E, 1, 2, 7);

  Matrix *B_ = matrix_row_echelon(B);
  Matrix *C_ = matrix_row_echelon(C);
  Matrix *E_ = matrix_row_echelon(E);

  Matrix *R_B = matrix_create(2, 3);
  matrix_set(R_B, 0, 0, 1);
  matrix_set(R_B, 0, 1, 2);
  matrix_set(R_B, 0, 2, 3);
  matrix_set(R_B, 1, 1, 1);
  matrix_set(R_B, 1, 2, 4);

  Matrix *R_C = matrix_create(2, 3);
  matrix_set(R_C, 0, 1, 1);
  matrix_set(R_C, 0, 2, 2);
  matrix_set(R_C, 1, 2, 1);

  Matrix *R_E = matrix_create(2, 3);
  matrix_set(R_E, 0, 0, 1);
  matrix_set(R_E, 0, 1, 2);
  matrix_set(R_E, 0, 2, 3);
  matrix_set(R_E, 1, 1, 1);
  matrix_set(R_E, 1, 2, -5);

  test("B = R_B", "B ≠ R_B", matrix_are_equal(B_, R_B));
  test("C = R_C", "C ≠ R_C", matrix_are_equal(C_, R_C));
  test("E = R_E", "E ≠ R_E", matrix_are_equal(E_, R_E));
}

/*
 * Problem 1.13
 *
 * Transform the following matrix into row-echelon form:
 *
 * A = [ 1  2 -1  6
 *       3  8  9 10
 *       2 -1  2 -2 ]
 *
 * R = [ 1 2 -1  6
 *       0 1  6 -4
 *       0 0  1 -1 ]
 */
void problem_1_13() {
  Matrix *A = matrix_create(3, 4);
  matrix_set(A, 0, 0, 1);
  matrix_set(A, 0, 1, 2);
  matrix_set(A, 0, 2, -1);
  matrix_set(A, 0, 3, 6);
  matrix_set(A, 1, 0, 3);
  matrix_set(A, 1, 1, 8);
  matrix_set(A, 1, 2, 9);
  matrix_set(A, 1, 3, 10);
  matrix_set(A, 2, 0, 2);
  matrix_set(A, 2, 1, -1);
  matrix_set(A, 2, 2, 2);
  matrix_set(A, 2, 3, -2);

  Matrix *R = matrix_create(3, 4);
  matrix_set(R, 0, 0, 1);
  matrix_set(R, 0, 1, 2);
  matrix_set(R, 0, 2, -1);
  matrix_set(R, 0, 3, 6);
  matrix_set(R, 1, 1, 1);
  matrix_set(R, 1, 2, 6);
  matrix_set(R, 1, 3, -4);
  matrix_set(R, 2, 2, 1);
  matrix_set(R, 2, 3, -1);

  Matrix *A_ = matrix_row_echelon(A);

  test("A = R", "A ≠ R", matrix_are_equal(A_, R));
}

/*
 * Problem 1.14
 *
 * Transform the following matrix into row-echelon form:
 *
 * A = [ 2 1 0 5
 *       3 6 1 1
 *       5 7 1 8 ]
 *
 * R = [ 1 1/2   0   5/2
 *       0   1 2/9 -13/9
 *       0   0   0     1 ]
 */
void problem_1_14() {
  Matrix *A = matrix_create(3, 4);
  matrix_set(A, 0, 0, 2);
  matrix_set(A, 0, 1, 1);
  matrix_set(A, 0, 3, 5);
  matrix_set(A, 1, 0, 3);
  matrix_set(A, 1, 1, 6);
  matrix_set(A, 1, 2, 1);
  matrix_set(A, 1, 3, 1);
  matrix_set(A, 2, 0, 5);
  matrix_set(A, 2, 1, 7);
  matrix_set(A, 2, 2, 1);
  matrix_set(A, 2, 3, 8);

  Matrix *R = matrix_create(3, 4);
  matrix_set(R, 0, 0, 1);
  matrix_set(R, 0, 1, 1.0 / 2.0);
  matrix_set(R, 0, 3, 5.0 / 2.0);
  matrix_set(R, 1, 1, 1);
  matrix_set(R, 1, 2, 2.0 / 9.0);
  matrix_set(R, 1, 3, -13.0 / 9.0);
  matrix_set(R, 2, 3, 1);

  Matrix *A_ = matrix_row_echelon(A);

  test("A = R", "A ≠ R", matrix_are_equal(A_, R));
}

/*
 * Problem 1.15
 *
 * Transform the following matrix into row-echelon form:
 *
 * A = [ 3  2 1 -4  1
 *       2  3 0 -1 -1
 *       1 -6 3 -8  7 ]
 *
 * R = [ 1 2/3  1/3 -4/3 1/3
 *       0   1 -2/5    1  -1
 *       0   0    0    0   0 ]
 */
void problem_1_15() {
  Matrix *A = matrix_create(3, 5);
  matrix_set(A, 0, 0, 3);
  matrix_set(A, 0, 1, 2);
  matrix_set(A, 0, 2, 1);
  matrix_set(A, 0, 3, -4);
  matrix_set(A, 0, 4, 1);
  matrix_set(A, 1, 0, 2);
  matrix_set(A, 1, 1, 3);
  matrix_set(A, 1, 3, -1);
  matrix_set(A, 1, 4, -1);
  matrix_set(A, 2, 0, 1);
  matrix_set(A, 2, 1, -6);
  matrix_set(A, 2, 2, 3);
  matrix_set(A, 2, 3, -8);
  matrix_set(A, 2, 4, 7);

  Matrix *R = matrix_create(3, 5);
  matrix_set(R, 0, 0, 1);
  matrix_set(R, 0, 1, 2.0 / 3.0);
  matrix_set(R, 0, 2, 1.0 / 3.0);
  matrix_set(R, 0, 3, -4.0 / 3.0);
  matrix_set(R, 0, 4, 1.0 / 3.0);
  matrix_set(R, 1, 1, 1);
  matrix_set(R, 1, 2, -2.0 / 5.0);
  matrix_set(R, 1, 3, 1);
  matrix_set(R, 1, 4, -1);

  Matrix *A_ = matrix_row_echelon(A);

  test("A = R", "A ≠ R", matrix_are_equal(A_, R));
}

/*
 * Problem 1.16
 *
 * Determine the rank of the matrix of Problem 1.14.
 *
 * rank(A) = 3
 */
void problem_1_16() {
  Matrix *A = matrix_create(3, 4);
  matrix_set(A, 0, 0, 2);
  matrix_set(A, 0, 1, 1);
  matrix_set(A, 0, 3, 5);
  matrix_set(A, 1, 0, 3);
  matrix_set(A, 1, 1, 6);
  matrix_set(A, 1, 2, 1);
  matrix_set(A, 1, 3, 1);
  matrix_set(A, 2, 0, 5);
  matrix_set(A, 2, 1, 7);
  matrix_set(A, 2, 2, 1);
  matrix_set(A, 2, 3, 8);

  test("rank(A) = 3", "rank(A) ≠ 3", matrix_row_rank(A) == 3);
}

/*
 * Problem 1.17
 *
 * Determine the rank of the matrix of Problem 1.15.
 *
 * rank(A) = 2
 */
void problem_1_17() {
  Matrix *A = matrix_create(3, 5);
  matrix_set(A, 0, 0, 3);
  matrix_set(A, 0, 1, 2);
  matrix_set(A, 0, 2, 1);
  matrix_set(A, 0, 3, -4);
  matrix_set(A, 0, 4, 1);
  matrix_set(A, 1, 0, 2);
  matrix_set(A, 1, 1, 3);
  matrix_set(A, 1, 3, -1);
  matrix_set(A, 1, 4, -1);
  matrix_set(A, 2, 0, 1);
  matrix_set(A, 2, 1, -6);
  matrix_set(A, 2, 2, 3);
  matrix_set(A, 2, 3, -8);
  matrix_set(A, 2, 4, 7);

  test("rank(A) = 2", "rank(A) ≠ 2", matrix_row_rank(A) == 2);
}

int main() {
  problem_1_1();
  problem_1_2();
  problem_1_3();
  problem_1_4();
  problem_1_5();
  problem_1_6();
  problem_1_7();
  problem_1_11();
  problem_1_12();
  problem_1_13();
  problem_1_14();
  problem_1_15();
  problem_1_16();
  problem_1_17();
}
