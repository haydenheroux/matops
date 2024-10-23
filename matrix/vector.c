#include <assert.h>
#include <stdlib.h>
#include <vector.h>

Vector *vector_create(unsigned int dimension) {
  Vector *V = malloc(sizeof(Vector));

  double *elements = calloc(dimension, sizeof(double));

  V->elements = elements;
  V->dimension = dimension;

  return V;
}

void vector_delete(Vector *V) {
  free(V->elements);
  free(V);
}

void vector_set(Vector *V, unsigned int index, double value) {
  assert(0 <= index && index < V->dimension);

  V->elements[index] = value;
}

double vector_dot(Vector *A, Vector *B) {
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
