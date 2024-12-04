#include <matrix.h>
#include <stdio.h>
#include <view.h>

/*
 * A = [ 2 -1
 *       4  3 ]
 */
int main() {
  Matrix *A = matrix_create(2, 2);

  matrix_set(A, 0, 0, 2);
  matrix_set(A, 0, 1, -1);
  matrix_set(A, 1, 0, 4);
  matrix_set(A, 1, 1, 3);

  MatrixView *row_view = matrix_view_create(A->columns);
  MatrixView *column_view = matrix_view_create(A->rows);

  puts("row 0:");
  matrix_view_row(row_view, A, 0);
  matrix_view_print(row_view);

  puts("row 1:");
  matrix_view_row(row_view, A, 1);
  matrix_view_print(row_view);

  puts("");

  puts("column 0:");
  matrix_view_column(column_view, A, 0);
  matrix_view_print(column_view);

  puts("column 1:");
  matrix_view_column(column_view, A, 1);
  matrix_view_print(column_view);

  puts("");

  puts("A = ");
  matrix_print(A);

  Matrix *A_2 = matrix_create(2, 2);

  for (unsigned int row = 0; row < A->rows; ++row) {
    for (unsigned int column = 0; column < A->rows; ++column) {
      matrix_view_row(row_view, A, row);
      matrix_view_column(column_view, A, column);
      matrix_set(A_2, row, column, matrix_view_dot(row_view, column_view));
    }
  }

  puts("A² = ");
  matrix_print(A_2);

  Matrix *A_4 = matrix_create(2, 2);

  for (unsigned int row = 0; row < A->rows; ++row) {
    for (unsigned int column = 0; column < A->rows; ++column) {
      matrix_view_row(row_view, A_2, row);
      matrix_view_column(column_view, A_2, column);
      matrix_set(A_4, row, column, matrix_view_dot(row_view, column_view));
    }
  }

  puts("A⁴ = ");
  matrix_print(A_4);
}
