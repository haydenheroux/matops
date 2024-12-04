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
 * Gets the index into the elements of the matrix `M` for row `row` and column
 * `column`.
 */
unsigned int matrix_index(const Matrix *M, unsigned int row,
                          unsigned int column);

/*
 * Gets the element of the matrix `M` at row `row` and column `column`.
 */
double matrix_get(const Matrix *M, unsigned int row, unsigned int column);

/*
 * Sets the element of the matrix `M` at row `row` and column `column` to
 * `value`.
 */
void matrix_set(Matrix *M, unsigned int row, unsigned int column, double value);

/*
 * Prints the matrix `M`.
 */
void matrix_print(const Matrix *M);

/*
 * Creates a copy of the matrix `M`.
 */
Matrix *matrix_copy(const Matrix *M);

/*
 * Creates a matrix containing the transpose of the matrix `M`.
 */
Matrix *matrix_transpose(const Matrix *M);

/*
 * Compares the order of two matrices.
 */
bool matrix_are_same_order(const Matrix *A, const Matrix *B);

/*
 * Tests the equality of two matrices.
 */
bool matrix_are_equal(const Matrix *A, const Matrix *B);

/*
 * Adds the corresponding elements of the matrix `B` to the matrix `A`.
 */
void matrix_add(Matrix *A, const Matrix *B);

/*
 * Multiplies elements of the matrix `M` by the scalar `scalar`.
 */
void matrix_scalar_multiply(Matrix *M, double scalar);

/*
 * Creates a matrix containing the result of multiplying the matrices `A` and
 * `B`.
 */
Matrix *matrix_matrix_multiply(const Matrix *A, const Matrix *B);

/*
 * Tests whether a matrix is in row-echelon form.
 */
bool matrix_is_row_echelon(const Matrix *M);

/*
 * Transforms the matrix `M` to row-echelon form.
 */
void matrix_row_echelon(Matrix *M);

/*
 * Calculates the row rank of a matrix.
 */
unsigned int matrix_row_rank(const Matrix *M);

/*
 * Performs Gauss-Jordan elimination on the matrix `M`.
 */
void matrix_gauss_jordan(Matrix *M);

/*
 * Transforms the matrix `M` to reduced row-echelon form.
 */
void matrix_reduced_row_echelon(Matrix *M);
