#include <matrix.h>
#include <stdio.h>
#include <test.h>
#include <vector.h>

/*
 * 1.1 Find A·B and B·Cᵀ for
 * A = [2 3 4], B = [5 6 -7], C = [7 -8 -8]
 * A·B = 0
 * B·Cᵀ = 50
 */
void chapter_1_1() {
  Vector *A = vector_create(3);
  vector_set(A, 0, 2);
  vector_set(A, 1, 3);
  vector_set(A, 2, 4);

  Vector *B = vector_create(3);
  vector_set(B, 0, 5);
  vector_set(B, 1, 6);
  vector_set(B, 2, -7);

  Vector *C = vector_create(3);
  vector_set(C, 0, 7);
  vector_set(C, 1, -8);
  vector_set(C, 2, -9);

  test("A·B = 0", "A·B ≠ 0", vector_dot(A, B) == 0);
  test("B·Cᵀ = 50", "B·Cᵀ ≠ 50", vector_dot(B, C) == 50);
}

/*
 * 1.2 Show that A+B = B+A for
 * A = [ 0 1
 *       2 3 ]
 * B = [ 4 5
 *       6 -7 ]
 */
void chapter_1_2() {
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
 * 1.3 Find 3A - 0.5B for the matrices of Problem 1.2
 * 3A - 0.5B = [ -2  0.5
 *                3 12.5 ]
 */
void chapter_1_3() {
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

int main() {
  chapter_1_1();
  chapter_1_2();
  chapter_1_3();
  return 0;
}
