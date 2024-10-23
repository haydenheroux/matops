// TODO Use libraries change vector path
#include <test.h>
#include <vector.h>

int main() {
  // 1.1 Find A·B and B·Cᵀ for
  // A = [2, 3, 4], B = [5, 6, -7], C = [7, -8, -8]
  Vector *A = vector_create(3);
  vector_set(A, 0, 2);
  vector_set(A, 1, 3);
  vector_set(A, 2, 4);

  Vector *B = vector_create(3);
  vector_set(B, 0, 5);
  vector_set(B, 1, 6);
  vector_set(B, 2, -7);

  Vector *C = vector_create(3);
  vector_set(C, 0, 7);
  vector_set(C, 1, -8);
  vector_set(C, 2, -9);

  // A·B = 0
  test("A·B = 0", "A·B ≠ 0", vector_dot(A, B) == 0);
  // B·Cᵀ = 50
  test("B·Cᵀ = 50", "B·Cᵀ ≠ 50", vector_dot(B, C) == 50);

  return 0;
}
