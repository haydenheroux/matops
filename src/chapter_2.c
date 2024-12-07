#include "solve.h"
#include "test.h"

/*
 * Problem 2.2
 *
 * Determine the associated augmented matrix of the system of equations.
 *
 * 2x₁ +  x₂      = 5
 * 3x₁ + 6x₂ + x₃ = 1
 * 5x₁ + 7x₂ + x₃ = 8
 *
 * A = [ 2 1 0
 *       3 6 1
 *       5 7 1 ]
 *
 * B = [ 5
 *       1
 *       8 ]
 *
 * [ A | B ] = [ 2 1 0 | 5
 *               3 6 1 | 1
 *               5 7 1 | 8 ]
 */
void problem_2_2() {
  Matrix *A = matrix_create(3, 3);
  matrix_set(A, 0, 0, 2);
  matrix_set(A, 0, 1, 1);
  matrix_set(A, 1, 0, 3);
  matrix_set(A, 1, 1, 6);
  matrix_set(A, 1, 2, 1);
  matrix_set(A, 2, 0, 5);
  matrix_set(A, 2, 1, 7);
  matrix_set(A, 2, 2, 1);

  Matrix *B = matrix_create(3, 1);
  matrix_set(B, 0, 0, 5);
  matrix_set(B, 1, 0, 1);
  matrix_set(B, 2, 0, 8);

  PartitionedMatrix *AX_B = partitioned_matrix_create(3, 4, 1, 2);
  partitioned_matrix_set_matrix(AX_B, 0, 0, A);
  partitioned_matrix_set_matrix(AX_B, 0, 1, B);

  Matrix *R = matrix_create(3, 4);
  matrix_set(R, 0, 0, 2);
  matrix_set(R, 0, 1, 1);
  matrix_set(R, 0, 3, 5);
  matrix_set(R, 1, 0, 3);
  matrix_set(R, 1, 1, 6);
  matrix_set(R, 1, 2, 1);
  matrix_set(R, 1, 3, 1);
  matrix_set(R, 2, 0, 5);
  matrix_set(R, 2, 1, 7);
  matrix_set(R, 2, 2, 1);
  matrix_set(R, 2, 3, 8);

  test("A|B = R", "A|B ≠ R", matrix_are_equal(AX_B->M, R));
}

/*
 * Problem 2.13
 *
 * Use Gauss-Jordan elimination to solve Problem 2.8.
 *
 *  x₁ + 2x₂ -  x₃ =  6
 * 3x₁ + 8x₂ + 9x₃ = 10
 * 2x₁ -  x₂ + 2x₃ = -2
 *
 * x₁ =  1
 * x₂ =  2
 * x₃ = -1
 */
void problem_2_13() {
  Matrix *A = matrix_create(3, 3);
  matrix_set(A, 0, 0, 1);
  matrix_set(A, 0, 1, 2);
  matrix_set(A, 0, 2, -1);
  matrix_set(A, 1, 0, 3);
  matrix_set(A, 1, 1, 8);
  matrix_set(A, 1, 2, 9);
  matrix_set(A, 2, 0, 2);
  matrix_set(A, 2, 1, -1);
  matrix_set(A, 2, 2, 2);

  Matrix *B = matrix_create(3, 1);
  matrix_set(B, 0, 0, 6);
  matrix_set(B, 1, 0, 10);
  matrix_set(B, 2, 0, -2);

  System *S = system_create(A, B);

  PartitionedMatrix *AX_B_ = system_solve(S);

  Matrix *B_ = partitioned_matrix_get_matrix(AX_B_, 0, 1);

  Matrix *R = matrix_create(3, 1);
  matrix_set(R, 0, 0, 1);
  matrix_set(R, 1, 0, 2);
  matrix_set(R, 2, 0, -1);

  test("consistent", "not consistent", system_is_consistent(S));
  test("unique solution", "no unique solution", system_has_unique_solution(S));
  test("B = R", "B ≠ R", matrix_are_equal(B_, R));
}

/*
 * Problem 2.14
 *
 * Use Gauss-Jordan elimination to solve the system of Problem 2.7.
 *
 *       7x₂ + 9x₃ = 0
 * 2x₁ +  x₂ -  x₃ = 0
 * 5x₁ + 6x₂ + 2x₃ = 0
 *
 * No unique solution.
 */
void problem_2_14() {
  Matrix *A = matrix_create(3, 3);
  matrix_set(A, 0, 1, 7);
  matrix_set(A, 0, 2, 9);
  matrix_set(A, 1, 0, 2);
  matrix_set(A, 1, 1, 1);
  matrix_set(A, 1, 2, -1);
  matrix_set(A, 2, 0, 5);
  matrix_set(A, 2, 1, 6);
  matrix_set(A, 2, 2, 2);

  Matrix *B = matrix_create(3, 1);

  System *S = system_create(A, B);

  test("consistent", "not consistent", system_is_consistent(S));
  test("no unique solution", "unique solution", !system_has_unique_solution(S));
}

int main() {
  problem_2_2();
  problem_2_13();
  problem_2_14();
}
