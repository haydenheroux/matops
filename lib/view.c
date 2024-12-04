#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "view.h"

MatrixView *matrix_view_create(unsigned int size) {
  MatrixView *MV = malloc(sizeof(MatrixView));

  double **elements = calloc(size, sizeof(double *));

  MV->elements = elements;
  MV->size = size;

  return MV;
}

void matrix_view_delete(MatrixView *MV) {
  free(MV->elements);
  free(MV);
}

double matrix_view_get(const MatrixView *MV, unsigned int index) {
  assert(0 <= index && index < MV->size);

  return *MV->elements[index];
}

void matrix_view_print(const MatrixView *MV) {
  for (unsigned int element = 0; element < MV->size; ++element) {
    printf("%f%c", matrix_view_get(MV, element),
           element < MV->size - 1 ? ' ' : '\n');
  }
}

void matrix_view_row(MatrixView *MV, const Matrix *M, unsigned int row) {
  assert(MV->size == M->columns);

  for (unsigned int column = 0; column < M->columns; ++column) {
    MV->elements[column] = &M->elements[matrix_index(M, row, column)];
  }
}

void matrix_view_column(MatrixView *MV, const Matrix *M, unsigned int column) {
  assert(MV->size == M->rows);

  for (unsigned int row = 0; row < M->rows; ++row) {
    MV->elements[row] = &M->elements[matrix_index(M, row, column)];
  }
}

double matrix_view_dot(const MatrixView *A, const MatrixView *B) {
  // "The dot product A·B of two vectors of the same order..."
  assert(A->size == B->size);

  double sum = 0.0;

  // "...is obtained by multiplying together corresponding elements of A and B
  // and then summing the results"
  for (unsigned int element = 0; element < A->size; ++element) {
    sum += *A->elements[element] * *B->elements[element];
  }

  return sum;
}
