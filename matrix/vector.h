#pragma once

#include <stdbool.h>

/*
 * A constant row vector if `row` is true (column vector otherwise) with
 * dimension `dimension`.
 */
typedef struct {
  double *elements;
  unsigned int dimension;
  bool row;
} Vector;

/*
 * Creates a zero-valued constant row vector with dimension `dimension`.
 */
Vector *vector_create_row(unsigned int dimension);

/*
 * Creates a zero-valued constant column vector with dimension `dimension`.
 */
Vector *vector_create_column(unsigned int dimension);

/*
 * Deletes the vector `V`.
 */
void vector_delete(Vector *V);

/*
 * Gets the element of the vector `V` at `index`.
 */
double vector_get(const Vector *V, unsigned int index);

/*
 * Sets the element of the vector `V` at `index` to `value`.
 */
void vector_set(Vector *V, unsigned int index, double value);

/*
 * Prints the vector `V`.
 */
void vector_print(const Vector *V);

/*
 * Creates a copy of the vector `V`.
 */
Vector *vector_copy(const Vector *V);

/*
 * Creates a vector with the transpose of the vector `V`.
 */
Vector *vector_transpose(const Vector *V);

/*
 * Calculates the scalar dot product of two constant vectors.
 */
double vector_dot(const Vector *A, const Vector *B);
