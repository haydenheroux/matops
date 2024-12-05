#pragma once

#include "matrix.h"

/*
 * A result of the decomposition of a square constant matrix into a lower
 * triangular matrix `L` and an upper triangular matrix `U`.
 */
typedef struct {
  Matrix *L;
  Matrix *U;
} MatrixLUDecompositionResult;

/*
 * Decomposes a square matrix `M` into a lower triangular matrix `L` and an
 * upper triangular matrix `U`.
 */
MatrixLUDecompositionResult *matrix_lu_decomposition(const Matrix *M);
