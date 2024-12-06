#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"

#define DEBUG false
#define EPSILON 1E-14
#define INDEX(M, r, c) r * M->columns + c
#define IS_ZERO(x) fabs(x) <= EPSILON
#define IS_NONZERO(x) fabs(x) > EPSILON

MatrixView *matrix_view_create(unsigned int size) {
  MatrixView *MV = malloc(sizeof(MatrixView));

  double **elements = calloc(size, sizeof(double *));

  MV->elements = elements;
  MV->size = size;

  return MV;
}

void matrix_view_delete(MatrixView *MV) {
  free(MV->elements);
  free(MV);
}

double matrix_view_get(const MatrixView *MV, unsigned int index) {
  assert(0 <= index && index < MV->size);

  return *MV->elements[index];
}

void matrix_view_print(const MatrixView *MV) {
  for (unsigned int element = 0; element < MV->size; ++element) {
    printf("%f%c", matrix_view_get(MV, element),
           element < MV->size - 1 ? ' ' : '\n');
  }
}

Matrix *matrix_create(unsigned int rows, unsigned int columns) {
  Matrix *M = malloc(sizeof(Matrix));

  M->rows = rows;
  M->columns = columns;
  M->elements = calloc(M->rows * M->columns, sizeof(double));

  M->row_views = calloc(M->rows, sizeof(MatrixView));
  for (unsigned int row = 0; row < M->rows; ++row) {
    M->row_views[row] = matrix_view_create(M->columns);

    for (unsigned int column = 0; column < M->columns; ++column) {
      M->row_views[row]->elements[column] = &M->elements[INDEX(M, row, column)];
    }
  }

  M->column_views = calloc(M->columns, sizeof(MatrixView));
  for (unsigned int column = 0; column < M->columns; ++column) {
    M->column_views[column] = matrix_view_create(M->rows);

    for (unsigned int row = 0; row < M->rows; ++row) {
      M->column_views[column]->elements[row] =
          &M->elements[INDEX(M, row, column)];
    }
  }

  return M;
}

Matrix *matrix_create_identity(unsigned int size) {
  Matrix *M = matrix_create(size, size);

  for (unsigned int i = 0; i < size; ++i) {
    matrix_set(M, i, i, 1);
  }

  return M;
}

void matrix_delete(Matrix *M) {
  free(M->elements);
  free(M);
}

double matrix_get(const Matrix *M, unsigned int row, unsigned int column) {
  if (DEBUG) {
    printf("matrix_get(%d, %d) of %d×%d\n", row, column, M->rows, M->columns);
  }

  assert(0 <= row && row < M->rows);
  assert(0 <= column && column < M->columns);

  return M->elements[INDEX(M, row, column)];
}

void matrix_set(Matrix *M, unsigned int row, unsigned int column,
                double value) {
  if (DEBUG) {
    printf("matrix_set(%d, %d, %f) of %d×%d\n", row, column, value, M->rows,
           M->columns);
  }

  assert(0 <= row && row < M->rows);
  assert(0 <= column && column < M->columns);

  M->elements[INDEX(M, row, column)] = value;
}

void matrix_print(const Matrix *M) {
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

Matrix *matrix_copy(const Matrix *M) {
  Matrix *C = matrix_create(M->rows, M->columns);

  for (unsigned int row = 0; row < M->rows; ++row) {
    for (unsigned int column = 0; column < M->columns; ++column) {
      matrix_set(C, row, column, matrix_get(M, row, column));
    }
  }

  return C;
}

Matrix *matrix_transpose(const Matrix *M) {
  // "If A has order m×n, then Aᵀ has order n×m"
  Matrix *M_T = matrix_create(M->columns, M->rows);

  for (unsigned int row = 0; row < M->rows; ++row) {
    for (unsigned int column = 0; column < M->columns; ++column) {
      matrix_set(M_T, column, row, matrix_get(M, row, column));
    }
  }

  return M_T;
}

bool matrix_are_same_order(const Matrix *A, const Matrix *B) {
  return A->rows == B->rows && A->columns == B->columns;
}

bool matrix_are_equal(const Matrix *A, const Matrix *B) {
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

void matrix_add(Matrix *A, const Matrix *B) {
  // "The sum A+B of two matrices A and B having the same order..."
  assert(matrix_are_same_order(A, B));

  // "... is the matrix obtained by adding corresponding elements of A and B"
  for (unsigned int row = 0; row < A->rows; ++row) {
    for (unsigned int column = 0; column < A->columns; ++column) {
      double sum = matrix_get(A, row, column) + matrix_get(B, row, column);
      matrix_set(A, row, column, sum);
    }
  }
}

void matrix_scalar_multiply(Matrix *M, double scalar) {
  // "The matrix kA is obtained by multiplying ever element of A by the scalar
  // k"
  for (unsigned int row = 0; row < M->rows; ++row) {
    for (unsigned int column = 0; column < M->columns; ++column) {
      matrix_set(M, row, column, scalar * matrix_get(M, row, column));
    }
  }
}

double matrix_view_dot(const MatrixView *A, const MatrixView *B) {
  // "The dot product A·B of two vectors of the same order..."
  assert(A->size == B->size);

  double sum = 0.0;

  // "...is obtained by multiplying together corresponding elements of A and B
  // and then summing the results"
  for (unsigned int element = 0; element < A->size; ++element) {
    sum += *A->elements[element] * *B->elements[element];
  }

  return sum;
}

Matrix *matrix_matrix_multiply(const Matrix *A, const Matrix *B) {
  // "Let A and B have orders r×p and p×c, respectively, so that the number of
  // columns of A equals the number of rows of B..."
  if (A->columns != B->rows) {
    return NULL;
  }

  // "Then the product AB is defined to be the matrix C of order r×c..."
  Matrix *C = matrix_create(A->rows, B->columns);

  // "Each element cij of AB is a dot product; it is obtained by forming the
  // transpose of the ith trow of A and then taking its dot product with the jth
  // column of B."
  for (unsigned int i = 0; i < A->rows; ++i) {
    for (unsigned int j = 0; j < B->columns; ++j) {
      double cij = matrix_view_dot(A->row_views[i], B->column_views[j]);
      matrix_set(C, i, j, cij);
    }
  }

  return C;
}

bool matrix_is_row_echelon(const Matrix *M) {
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

void matrix_row_echelon(Matrix *M) {
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
      return;
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
}

unsigned int matrix_row_rank(const Matrix *M) {
  Matrix *R = matrix_copy(M);
  matrix_row_echelon(R);

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

void matrix_gauss_jordan(Matrix *M) {
  // "Beginning with the last pivot element and continuing sequentially
  // backward"
  for (unsigned int work_row = M->rows - 1; work_row > 0; --work_row) {
    for (unsigned int work_column = 0; work_column < M->columns;
         ++work_column) {
      double p = matrix_get(M, work_row, work_column);
      if (IS_ZERO(p - 1)) {
        // "Each pivot element is used to transform all other elements in its
        // column to zero"
        for (unsigned int row = 0; row < work_row; ++row) {
          double v = matrix_get(M, row, work_column);
          for (unsigned int column = 0; column < M->columns; ++column) {
            double x = matrix_get(M, row, column);
            double y = matrix_get(M, work_row, column);
            x -= v * y;
            matrix_set(M, row, column, x);
          }
        }
      }
    }
  }
}

void matrix_reduced_row_echelon(Matrix *M) {
  // "Once the augmented matrix has been reduced to row-echelon form..."
  matrix_row_echelon(M);
  // "it is then reduced still further"
  matrix_gauss_jordan(M);
}
