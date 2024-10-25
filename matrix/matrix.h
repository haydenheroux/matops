#pragma once

#include <stdbool.h>

/*
 * A constant matrix with `rows` rows and `columns` columns.
 */
typedef struct {
  unsigned int rows;
  unsigned int columns;
  double *elements;
} Matrix;

/*
 * Creates a zero-value constant matrix with `rows` rows and `columns` columns.
 */
Matrix *matrix_create(unsigned int rows, unsigned int columns);

/*
 * Deletes the matrix `M`.
 */
void matrix_delete(Matrix *M);

/*
 * Gets the element of the matrix `M` at row `row` and column `column`.
 */
double matrix_get(Matrix *M, unsigned int row, unsigned int column);

/*
 * Sets the element of the matrix `M` at row `row` and column `column` to
 * `value`.
 */
void matrix_set(Matrix *M, unsigned int row, unsigned int column, double value);

/*
 * Prints the matrix `M`.
 */
void matrix_print(Matrix *M);

/*
 * Creates a copy of the matrix `M`.
 */
Matrix *matrix_copy(Matrix *M);

/*
 * Creates a matrix containing the transpose of the matrix `M`.
 */
Matrix *matrix_transpose(Matrix *M);

/*
 * Compares the order of two matrices.
 */
bool matrix_are_same_order(Matrix *A, Matrix *B);

/*
 * Tests the equality of two matrices.
 */
bool matrix_are_equal(Matrix *A, Matrix *B);

/*
 * Adds the corresponding elements of the matrix `B` to the matrix `M` if the
 * matrices have the same order.
 *
 * If the matrices have different order, returns NULL.
 * Otherwise, returns `M`, with the corresponding elements of `B` added.
 */
Matrix *matrix_add(Matrix *M, Matrix *B);

/*
 * Multiplies elements of the matrix `M` by the scalar `scalar`.
 *
 * Returns `M`, with elements multiplied by the scalar `scalar`.
 */
Matrix *matrix_scalar_multiply(Matrix *M, double scalar);

/*
 * Creates a matrix containing the result of multiplying the matrices `A` and
 * `B`.
 *
 * If the matrices have different order, returns NULL.
 * Otherwise, returns a created matrix `C`, which contains the result of `A``B`.
 */
Matrix *matrix_matrix_multiply(Matrix *A, Matrix *B);

/*
 * Tests whether a matrix is in row-echelon form.
 */
bool matrix_is_row_echelon(Matrix *M);

/*
 * Transforms the matrix `M` to row-echelon form.
 *
 * Returns the matrix `M` after transformation.
 */
Matrix *matrix_row_echelon(Matrix *M);

/*
 * Calculates the row rank of a matrix.
 */
unsigned int matrix_row_rank(Matrix *M);
