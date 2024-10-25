#include <assert.h>
#include <math.h>
#include <matrix.h>
#include <stdio.h>
#include <stdlib.h>

#define DEBUG false
#define EPSILON 1E-14
#define INDEX(M, r, c) r * M->columns + c
#define IS_ZERO(x) fabs(x) <= EPSILON
#define IS_NONZERO(x) fabs(x) > EPSILON

Matrix *matrix_create(unsigned int rows, unsigned int columns) {
  Matrix *M = malloc(sizeof(Matrix));

  unsigned int size = rows * columns;
  double *elements = calloc(size, sizeof(double));

  M->elements = elements;
  M->rows = rows;
  M->columns = columns;

  return M;
}

void matrix_delete(Matrix *M) {
  free(M->elements);
  free(M);
}

double matrix_get(Matrix *M, unsigned int row, unsigned int column) {
  if (DEBUG) {
    printf("matrix_get(%d, %d) of %d×%d\n", row, column, M->rows, M->columns);
  }

  return M->elements[INDEX(M, row, column)];
}

void matrix_set(Matrix *M, unsigned int row, unsigned int column,
                double value) {
  if (DEBUG) {
    printf("matrix_set(%d, %d, %f) of %d×%d\n", row, column, value, M->rows,
           M->columns);
  }

  M->elements[INDEX(M, row, column)] = value;
}

void matrix_print(Matrix *M) {
  int max_width = 0;

  for (unsigned int row = 0; row < M->rows; ++row) {
    for (unsigned int column = 0; column < M->columns; ++column) {
      int width = snprintf(NULL, 0, "%f", matrix_get(M, row, column));
      if (width > max_width)
        max_width = width;
    }
  }

  for (unsigned int row = 0; row < M->rows; ++row) {
    for (unsigned int column = 0; column < M->columns; ++column) {
      printf("%*f ", max_width, matrix_get(M, row, column));
    }
    printf("\n");
  }
}

Matrix *matrix_copy(Matrix *M) {
  Matrix *C = matrix_create(M->rows, M->columns);

  for (unsigned int row = 0; row < M->rows; ++row) {
    for (unsigned int column = 0; column < M->columns; ++column) {
      matrix_set(C, row, column, matrix_get(M, row, column));
    }
  }

  return C;
}

Matrix *matrix_transpose(Matrix *M) {
  // "If A has order m×n, then Aᵀ has order n×m"
  Matrix *M_T = matrix_create(M->columns, M->rows);

  for (unsigned int row = 0; row < M->rows; ++row) {
    for (unsigned int column = 0; column < M->columns; ++column) {
      matrix_set(M_T, column, row, matrix_get(M, row, column));
    }
  }

  return M_T;
}

bool matrix_are_same_order(Matrix *A, Matrix *B) {
  return A->rows == B->rows && A->columns == B->columns;
}

bool matrix_are_equal(Matrix *A, Matrix *B) {
  if (!matrix_are_same_order(A, B))
    return false;

  for (unsigned int row = 0; row < A->rows; ++row) {
    for (unsigned int column = 0; column < A->columns; ++column) {
      double difference =
          matrix_get(A, row, column) - matrix_get(B, row, column);
      if (IS_NONZERO(difference)) {
        return false;
      }
    }
  }

  return true;
}

Matrix *matrix_add(Matrix *M, Matrix *B) {
  // "The sum A+B of two matrices A and B having the same order..."
  if (!matrix_are_same_order(M, B)) {
    return NULL;
  }

  // "... is the matrix obtained by adding corresponding elements of A and B"
  for (unsigned int row = 0; row < M->rows; ++row) {
    for (unsigned int column = 0; column < M->columns; ++column) {
      double sum = matrix_get(M, row, column) + matrix_get(B, row, column);
      matrix_set(M, row, column, sum);
    }
  }

  return M;
}

Matrix *matrix_scalar_multiply(Matrix *M, double scalar) {
  // "The matrix kA is obtained by multiplying ever element of A by the scalar
  // k"
  for (unsigned int row = 0; row < M->rows; ++row) {
    for (unsigned int column = 0; column < M->columns; ++column) {
      matrix_set(M, row, column, scalar * matrix_get(M, row, column));
    }
  }

  return M;
}

Matrix *matrix_matrix_multiply(Matrix *A, Matrix *B) {
  // "Let A and B have orders r×p and p×c, respectively, so that the number of
  // columns of A equals the number of rows of B..."
  if (A->columns != B->rows) {
    return NULL;
  }

  double common_dimension = A->columns;

  // "Then the product AB is defined to be the matrix C of order r×c..."
  Matrix *C = matrix_create(A->rows, B->columns);

  // TODO Write using vectors, dot product
  for (unsigned int row = 0; row < A->rows; ++row) {
    for (unsigned int column = 0; column < B->columns; ++column) {
      double sum = 0.0;

      for (unsigned int index = 0; index < common_dimension; ++index) {
        sum += matrix_get(A, row, index) * matrix_get(B, index, column);
      }

      matrix_set(C, row, column, sum);
    }
  }

  return C;
}

bool matrix_is_row_echelon(Matrix *M) {
  // "R1: All nonzero rows precede (appear above) zero rows when both types
  // are contained in the matrix"
  // "R2: The first (leftmost) nonzero element of each nonzero row is unity (1)"
  // "R3: When the first nonzero element of a row appears in column c, then all
  // elements in column c in succeeding rows are zero"
  // "R4: The first nonzero element of any nonzero row appears in a later column
  // (further to the right) than the first nonzero element of any preceding row"

  bool leading_column_defined = false;
  // NOTE Comparison between signed and unsigned has weird behavior?
  // NOTE Setting the initial value to -1 breaks things...
  unsigned int leading_column = 0;

  for (unsigned int row = 0; row < M->rows; ++row) {
    unsigned int column = 0;

    while (column < M->columns && IS_ZERO(matrix_get(M, row, column))) {
      column++;
    }

    if (column == M->columns) {
      continue;
    }

    if (matrix_get(M, row, column) != 1) {
      return false;
    }

    if (leading_column_defined && column <= leading_column) {
      return false;
    }

    leading_column_defined = true;
    leading_column = column;
  }

  return true;
}

Matrix *matrix_row_echelon(Matrix *M) {
  // "Step 1.1: Let R denote the work row"
  unsigned int work_row = 0;

  while (work_row < M->rows) {
    unsigned int pivot_column = 0;
    bool found_pivot = false;

    // "Step 1.2: Find the first column containing a nonzero element in either
    // row R or any succeeding row"
    // "Step 1.2: Otherwise, let C denote this column"
    // "Step 1.3: Beginning with row R and continuing through successive rows,
    // locate the first row having a nonzero element in column C"
    for (; !found_pivot && pivot_column < M->columns; ++pivot_column) {
      for (unsigned int pivot_row = work_row;
           !found_pivot && pivot_row < M->rows; ++pivot_row) {
        if (IS_NONZERO(matrix_get(M, pivot_row, pivot_column))) {
          found_pivot = true;
          // "Step 1.3: If this element is not row R, interchange it with row R"
          for (unsigned int column = 0; column < M->columns; ++column) {
            double pivot_row_value = matrix_get(M, pivot_row, column);
            double work_row_value = matrix_get(M, work_row, column);

            matrix_set(M, pivot_row, column, work_row_value);
            matrix_set(M, work_row, column, pivot_row_value);
          }
        }
      }
    }

    // "Step 1.2: If no such column exists, stop; the transformation is
    // complete"
    if (!found_pivot) {
      return M;
    }

    // TODO The pivot column is incremented after exiting the loop, and
    // this is the easiest fix
    --pivot_column;

    // "Step 1.3: Row R will now have a nonzero element in column C... called
    // the pivot; let P denote its value"
    double pivot_value = matrix_get(M, work_row, pivot_column);

    // "Step 1.4: If P is not 1, multiply the elements of row R by 1/P"
    if (pivot_value != 1) {
      for (unsigned int column = 0; column < M->columns; ++column) {
        matrix_set(M, work_row, column,
                   matrix_get(M, work_row, column) / pivot_value);
      }
    }

    // "Step 1.5: Search all rows following R for one having a nonzero
    // element... designate that row as row N, and the value of the nonzero
    // element in row N and column C as V"
    for (unsigned int row = work_row + 1; row < M->rows; ++row) {
      double v = matrix_get(M, row, pivot_column);
      if (IS_NONZERO(v)) {
        // "Step 1.6: Add to the elements of row N the scalar -V times the
        // corresponding elements of row R"
        for (unsigned int column = 0; column < M->columns; ++column) {
          double x = matrix_get(M, row, column);
          double y = matrix_get(M, work_row, column);
          x -= v * y;
          matrix_set(M, row, column, x);
        }
      }

      // "Step 1.7: Return to Step 1.5."
    }

    // "Step 1.8: Increase R by 1. If this new value of R is larger than the
    // number of rows in the matrix, stop; the transformation is complete.
    // Otherwise, return to Step 1.2."
    work_row++;
  }

  return M;
}

unsigned int matrix_row_rank(Matrix *M) {
  Matrix *R = matrix_row_echelon(M);

  // "The rank (or row rank) of a matrix is the number of nonzero rows in the
  // matrix after it has been transformed to row-echelon form"
  unsigned int nonzero_rows = 0;

  for (unsigned int row = 0; row < R->rows; ++row) {
    bool is_zero_row = true;
    for (unsigned int column = 0; column < R->columns; ++column) {
      if (IS_NONZERO(matrix_get(R, row, column))) {
        nonzero_rows++;
        is_zero_row = false;
        break;
      }
    }
    if (is_zero_row) {
      break;
    }
  }

  return nonzero_rows;
}
