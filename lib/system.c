#include <assert.h>
#include <stdlib.h>

#include "system.h"

System *system_create(const Matrix *A, const Matrix *B) {
  assert(A->rows == B->rows);
  assert(B->columns == 1);

  System *S = malloc(sizeof(System));

  S->A = matrix_copy(A);
  S->B = matrix_copy(B);
  S->AX_B = partitioned_matrix_create(A->rows, A->columns + B->columns, 2, 1);
  partitioned_matrix_set_matrix(S->AX_B, 0, 0, S->A);
  partitioned_matrix_set_matrix(S->AX_B, 0, 1, S->B);

  return S;
}

void system_delete(System *S) {
  matrix_delete(S->A);
  matrix_delete(S->B);
  partitioned_matrix_delete(S->AX_B);
  free(S);
}

bool system_is_consistent(const System *S) {
  // "Theorem 2.1: The system AX = B is consistent if and only if the rank of A
  // equals the rank of [ A | B ]"
  return matrix_row_rank(S->A) == matrix_row_rank(S->AX_B->M);
}

bool system_has_unique_solution(const System *S) {
  // "Theorem 2.2: Denote the rank of A as k, and the number of unknowns as n.
  // If the system AX = B is consistent, then the solution contains n - k
  // arbitrary scalars."
  unsigned int k = matrix_row_rank(S->A);
  unsigned int n = S->A->columns;
  // NOTE n == k is equivalent to n - k == 0
  return system_is_consistent(S) && n == k;
}

PartitionedMatrix *system_solve(const System *S) {
  // TODO Implement `partitioned_matrix_copy` to avoid remaking `AX_B` from
  // scratch without disrupting `S->AX_B`
  PartitionedMatrix *AX_B = partitioned_matrix_create(
      S->A->rows, S->A->columns + S->B->columns, 2, 1);
  partitioned_matrix_set_matrix(AX_B, 0, 0, S->A);
  partitioned_matrix_set_matrix(AX_B, 0, 1, S->B);

  // NOTE Use Gauss-Jordan elimination to avoid back-substitution
  matrix_reduced_row_echelon(AX_B->M);

  return AX_B;
}
