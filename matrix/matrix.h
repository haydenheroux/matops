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
 * Deletes a matrix.
 */
void matrix_delete(Matrix *M);

/*
 * Gets the element at `row``column`
 */
double matrix_get(Matrix *M, unsigned int row, unsigned int column);

/*
 * Sets the element at `row``column` to `value`.
 */
double matrix_set(Matrix *M, unsigned int row, unsigned int column,
                  double value);

/*
 * Prints the matrix.
 */
void matrix_print(Matrix *M);

/*
 * Creates a copy of the matrix `M`.
 */
Matrix *matrix_copy(Matrix *M);

/*
 * Calculates the transpose of a matrix.
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
 * Calculates the result of adding two constant matrices.
 *
 * If the matrices have different order, returns NULL.
 */
Matrix *matrix_add(Matrix *A, Matrix *B);

/*
 * Calculates the result of multiplying the matrix `M` by `scalar`.
 */
Matrix *matrix_scalar_multiply(Matrix *M, double scalar);

/*
 * Calculates the result of multiplying `A``B`.
 *
 * If the matrices have different order, returns NULL.
 */
Matrix *matrix_matrix_multiply(Matrix *A, Matrix *B);

/*
 * Tests whether a matrix is in row-echelon form.
 */
bool matrix_is_row_echelon(Matrix *M);

/*
 * Converts a matrix to row-echelon form.
 */
Matrix *matrix_row_echelon(Matrix *M);

/*
 * Calculates the row rank of a matrix.
 */
unsigned int matrix_row_rank(Matrix *M);
