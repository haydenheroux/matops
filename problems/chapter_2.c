#include <matrix.h>
#include <partition.h>
#include <test.h>

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
  matrix_set(B, 0, 1, 1);
  matrix_set(B, 0, 2, 8);

  PartitionedMatrix *AX_B = partitioned_matrix_create(3, 4, 2, 1);
  partitioned_matrix_set_partition(AX_B, 0, 0, 3, 3);
  partitioned_matrix_set_partition(AX_B, 0, 1, 3, 1);

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

int main() {
  // TODO
  problem_2_2();
}
