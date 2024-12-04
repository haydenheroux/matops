#pragma once

#include "matrix.h"

/*
 * A view into a constant matrix with `size` elements. Intended to be used
 * for immutable matrix operations.
 */
typedef struct {
  double **elements;
  unsigned int size;
} MatrixView;

/*
 * Creates a zero-valued constant matrix view with `size` elements.
 */
MatrixView *matrix_view_create(unsigned int size);

/*
 * Deletes the matrix view `MV`.
 */
void matrix_view_delete(MatrixView *MV);

/*
 * Gets the element of the matrix view `MV` at `index`.
 */
double matrix_view_get(const MatrixView *MV, unsigned int index);

/*
 * Prints the elements in the matrix view `MV`.
 */
void matrix_view_print(const MatrixView *MV);

/*
 * Views the `row` row of the matrix `M`.
 */
void matrix_view_row(MatrixView *MV, const Matrix *M, unsigned int row);

/*
 * Views the `column` column of the matrix `M`.
 */
void matrix_view_column(MatrixView *MV, const Matrix *M, unsigned int column);

/*
 * Calculates the vector dot product of two matrix views.
 */
double matrix_view_dot(const MatrixView *A, const MatrixView *B);
