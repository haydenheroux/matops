#pragma once

/*
 * A constant vector with dimension `dimension`.
 *
 * This implementation does not define whether this vector is a row vector or
 * column vector.
 */
typedef struct {
  double *elements;
  unsigned int dimension;
} Vector;

/*
 * Creates a zero-valued constant vector with dimension `dimension`.
 */
Vector *vector_create(unsigned int dimension);

/*
 * Deletes a vector.
 */
void vector_delete(Vector *V);

/*
 * Sets the element of `vec` at `index` to `value`.
 */
void vector_set(Vector *V, unsigned int index, double value);

/*
 * Calculates the scalar dot product of two constant vectors.
 */
double vector_dot(Vector *A, Vector *B);
