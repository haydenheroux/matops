#include <assert.h>
#include <matrix.h>
#include <stdio.h>
#include <stdlib.h>

#define INDEX(i, j, r) (r * i) + j

Matrix *matrix_create(unsigned int rows, unsigned int columns) {
  Matrix *M = malloc(sizeof(Matrix));

  unsigned int size = rows * columns;
  double *elements = calloc(size, sizeof(double));

  M->elements = elements;
  M->rows = rows;
  M->columns = columns;

  return M;
}

void matrix_delete(Matrix *M) {
  free(M->elements);
  free(M);
}

double matrix_get(Matrix *M, unsigned int row, unsigned int column) {
  unsigned int index = row * M->columns + column;

  return M->elements[index];
}

double matrix_set(Matrix *M, unsigned int row, unsigned int column,
                  double value) {
  unsigned int index = row * M->columns + column;

  return M->elements[index] = value;
}

void matrix_print(Matrix *M) {
  int max_width = 0;

  for (unsigned int row = 0; row < M->rows; ++row) {
    for (unsigned int column = 0; column < M->columns; ++column) {
      int width = snprintf(NULL, 0, "%f", matrix_get(M, row, column));
      if (width > max_width)
        max_width = width;
    }
  }

  for (unsigned int row = 0; row < M->rows; ++row) {
    for (unsigned int column = 0; column < M->columns; ++column) {
      double d = matrix_get(M, row, column);

      printf("%*f ", max_width, d);
    }
    printf("\n");
  }
}

Matrix *matrix_copy(Matrix *M) {
  Matrix *C = matrix_create(M->rows, M->columns);

  for (unsigned int row = 0; row < M->rows; ++row) {
    for (unsigned int column = 0; column < M->columns; ++column) {
      matrix_set(C, row, column, matrix_get(M, row, column));
    }
  }

  return C;
}

Matrix *matrix_transpose(Matrix *M) {
  // "If A has order m×n, then Aᵀ has order n×m"
  Matrix *M_T = matrix_create(M->columns, M->rows);

  for (unsigned int row = 0; row < M->rows; ++row) {
    for (unsigned int column = 0; column < M->columns; ++column) {
      matrix_set(M_T, column, row, matrix_get(M, row, column));
    }
  }

  return M_T;
}

bool matrix_same_order(Matrix *A, Matrix *B) {
  return A->rows == B->rows && A->columns == B->columns;
}

bool matrix_equal(Matrix *A, Matrix *B) {
  if (!matrix_same_order(A, B))
    return false;

  for (unsigned int row = 0; row < A->rows; ++row) {
    for (unsigned int column = 0; column < A->columns; ++column) {
      // TODO Replace with custom "fuzzy" equality checker
      if (matrix_get(A, row, column) != matrix_get(B, row, column)) {
        return false;
      }
    }
  }

  return true;
}

Matrix *matrix_add(Matrix *A, Matrix *B) {
  // "The sum A+B of two matrices A and B having the same order..."
  if (!matrix_same_order(A, B)) {
    return NULL;
  }

  // "... is the matrix obtained by adding corresponding elements of A and B"
  Matrix *C = matrix_create(A->rows, A->columns);

  for (unsigned int row = 0; row < A->rows; ++row) {
    for (unsigned int column = 0; column < A->columns; ++column) {
      double sum = matrix_get(A, row, column) + matrix_get(B, row, column);
      matrix_set(C, row, column, sum);
    }
  }

  return C;
}

Matrix *matrix_scalar_multiply(Matrix *M, double scalar) {
  Matrix *C = matrix_create(M->rows, M->columns);

  for (unsigned int row = 0; row < M->rows; ++row) {
    for (unsigned int column = 0; column < M->columns; ++column) {
      matrix_set(C, row, column, scalar * matrix_get(M, row, column));
    }
  }

  return C;
}

Matrix *matrix_matrix_multiply(Matrix *A, Matrix *B) {
  // "Let A and B have orders r×p and p×c, respectively, so that the number of
  // columns of A equals the number of rows of B..."
  if (A->columns != B->rows) {
    return NULL;
  }

  double common_dimension = A->columns;

  // "Then the product AB is defined to be the matrix C of order r×c..."
  Matrix *C = matrix_create(A->rows, B->columns);

  // TODO Write using vectors, dot product
  for (unsigned int row = 0; row < A->rows; ++row) {
    for (unsigned int column = 0; column < B->columns; ++column) {
      double sum = 0.0;

      for (unsigned int index = 0; index < common_dimension; ++index) {
        sum += matrix_get(A, row, index) * matrix_get(B, index, column);
      }

      matrix_set(C, row, column, sum);
    }
  }

  return C;
}
