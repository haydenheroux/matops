#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "decomposition.h"

MatrixLUDecompositionResult *matrix_lu_decomposition(const Matrix *M) {
  // Only a square matrix can be decomposed into LU using Crout's reduction
  if (M->rows != M->columns) {
    return NULL;
  }

  unsigned int n = M->rows;

  // "If the first element of M is zero, stop; factorization is not possible"
  if (matrix_get(M, 0, 0) == 0) {
    return NULL;
  }

  MatrixLUDecompositionResult *LU = malloc(sizeof(MatrixLUDecompositionResult));
  Matrix *L = matrix_create(M->rows, M->columns);
  Matrix *U = matrix_create(M->rows, M->columns);

  // "Step 3.1: The first column of L is the first column of M..."
  for (unsigned int row = 0; row < M->rows; ++row) {
    matrix_set(L, row, 0, matrix_get(M, row, 0));
  }

  // "Step 3.1: The first row of U is the first row of M divided by the first
  // element of M"
  double m = matrix_get(M, 0, 0);
  for (unsigned int column = 0; column < M->columns; ++column) {
    matrix_set(U, 0, column, matrix_get(M, 0, column) / m);
  }

  // "Step 3.1: Set a counter at N = 2"
  unsigned int N = 2;

  while (true) {
    // "Step 3.2: For i = N ... n, set L'i equal to the computed portion of the
    // ith row of L. That is, L'i consists of the first N - 1 elements of the
    // ith row of L"
    for (unsigned int i = N; i <= n; ++i) {
      // "Step 3.4: For each element of the column on or below the main
      // diagonal, compute liN = aiN - L'i · U'N"
      double liN = matrix_get(M, i - 1, N - 1);

      for (unsigned int k = 0; k < N - 1; ++k) {
        liN -= matrix_get(L, i - 1, k) * matrix_get(U, k, N - 1);
      }

      // "Step 3.4: if any lNN when N ≠ n, stop; the factorization is not
      // possible."
      if (liN == 0 && N != n) {
        matrix_delete(L);
        matrix_delete(U);
        free(LU);
        return NULL;
      }

      matrix_set(L, i - 1, N - 1, liN);
    }

    // "Step 3.5: Set uNN to 1"
    matrix_set(U, N - 1, N - 1, 1);

    // "Step 3.5: If N = n, stop; the factorization is complete."
    if (N == n) {
      break;
    }

    // "Step 3.3: For j = N ...n, set U'j equal to the computed portion of the
    // jth column of U. That is, U'j consists of the first N - 1 elements of the
    // jth column of U."
    // NOTE j = N + 1 because uNN = 1
    for (unsigned int j = N + 1; j <= n; ++j) {
      // "Step 3.5: For each element of the row to the right of
      // the main diagonal, compute uNj = (aNj - L'N · ̇U'j) / lNN"
      double uNj = matrix_get(M, N - 1, j - 1);

      // NOTE Repeated subtraction of the products of of L'N and U'j is the dot
      // product
      for (unsigned int k = 0; k < N - 1; ++k) {
        uNj -= matrix_get(L, N - 1, k) * matrix_get(U, k, j - 1);
      }

      uNj /= matrix_get(L, N - 1, N - 1);

      matrix_set(U, N - 1, j - 1, uNj);
    }

    // "Step 3.6: Increase N by 1, and return to Step 3.2"
    N += 1;
  }

  LU->L = L;
  LU->U = U;
  return LU;
}
