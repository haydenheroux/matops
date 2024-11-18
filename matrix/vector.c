#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector.h>

Vector *vector_create(unsigned int dimension, bool row) {
  Vector *V = malloc(sizeof(Vector));

  double *elements = calloc(dimension, sizeof(double));

  V->elements = elements;
  V->dimension = dimension;
  V->row = row;

  return V;
}

Vector *vector_create_row(unsigned int dimension) {
  return vector_create(dimension, true);
}

Vector *vector_create_column(unsigned int dimension) {
  return vector_create(dimension, false);
}

void vector_delete(Vector *V) {
  free(V->elements);
  free(V);
}

double vector_get(const Vector *V, unsigned int index) {
  assert(0 <= index && index < V->dimension);

  return V->elements[index];
}

void vector_set(Vector *V, unsigned int index, double value) {
  assert(0 <= index && index < V->dimension);

  V->elements[index] = value;
}

void vector_print(const Vector *V) {
  const char c = V->row ? ' ' : '\n';

  for (unsigned int element = 0; element < V->dimension; ++element) {
    printf("%f%c", vector_get(V, element),
           element < V->dimension - 1 ? c : '\n');
  }
}

Vector *vector_copy(const Vector *V) {
  Vector *C = vector_create(V->dimension, V->row);

  for (unsigned int element = 0; element < V->dimension; ++element) {
    vector_set(C, element, vector_get(V, element));
  }

  return C;
}

Vector *vector_transpose(const Vector *V) {
  Vector *C = vector_copy(V);

  // Toggle the row-ness of the vector to transpose the vector
  C->row = !V->row;

  return C;
}

double vector_dot(const Vector *A, const Vector *B) {
  // "The dot product A·B of two vectors of the same order..."
  assert(A->dimension == B->dimension);

  double sum = 0.0;

  // "...is obtained by multiplying together corresponding elements of A and B
  // and then summing the results"
  for (unsigned int element = 0; element < A->dimension; ++element) {
    sum += A->elements[element] * B->elements[element];
  }

  return sum;
}
