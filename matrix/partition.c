#include "partition.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define DEBUG false
#define INDEX(PM, h, v) h * PM->vertical + v

PartitionedMatrix *partitioned_matrix_create(unsigned int rows,
                                             unsigned int columns,
                                             unsigned int horizontal,
                                             unsigned int vertical) {
  PartitionedMatrix *PM = malloc(sizeof(PartitionedMatrix));

  PM->horizontal = horizontal;
  PM->vertical = vertical;

  unsigned int size = horizontal * vertical;
  PM->partitions = calloc(size, sizeof(Partition));

  PM->M = matrix_create(rows, columns);

  return PM;
}

void partitioned_matrix_delete(PartitionedMatrix *PM) {
  matrix_delete(PM->M);
  free(PM->partitions);
  free(PM);
}

Partition *partitioned_matrix_get_partition(const PartitionedMatrix *PM,
                                            unsigned int horizontal,
                                            unsigned int vertical) {
  if (DEBUG) {
    printf("partitioned_matrix_get_partition(%d, %d) of %d×%d\n", horizontal,
           vertical, PM->horizontal, PM->vertical);
  }

  return &PM->partitions[INDEX(PM, horizontal, vertical)];
}

void partitioned_matrix_set_partition(PartitionedMatrix *PM,
                                      unsigned int horizontal,
                                      unsigned int vertical, unsigned int rows,
                                      unsigned int columns) {
  if (DEBUG) {
    printf("partitioned_matrix_set_partition(%d, %d) of %d×%d\n\n", horizontal,
           vertical, PM->horizontal, PM->vertical);
  }

  if (DEBUG)
    puts("testing same rows in set partition");
  // TODO All partitions sharing vertical must have same number of rows
  bool same_rows = true;
  for (unsigned int horiz = 0; horiz < PM->horizontal; ++horiz) {
    // Skip over self
    if (horiz == horizontal) {
      continue;
    }

    Partition *partition =
        partitioned_matrix_get_partition(PM, horiz, vertical);

    if (partition->rows != 0 && partition->rows != rows) {
      same_rows = false;
      break;
    }
  }
  assert(same_rows);
  if (DEBUG)
    puts("");

  if (DEBUG)
    puts("testing same columns in set partition");
  // TODO All partitions sharing horizontal must have same number of columns
  bool same_columns = true;
  for (unsigned int vert = 0; vert < PM->vertical; ++vert) {
    // Skip over self
    if (vert == vertical) {
      continue;
    }

    Partition *partition =
        partitioned_matrix_get_partition(PM, horizontal, vert);

    if (partition->columns != 0 && partition->columns != columns) {
      same_columns = false;
      break;
    }
  }
  assert(same_columns);
  if (DEBUG)
    puts("");

  if (DEBUG)
    puts("setting the partition");
  Partition *partition =
      partitioned_matrix_get_partition(PM, horizontal, vertical);
  partition->rows = rows;
  partition->columns = columns;
  if (DEBUG)
    puts("");
}

Matrix *partitioned_matrix_get_matrix(const PartitionedMatrix *PM,
                                      unsigned int horizontal,
                                      unsigned int vertical) {
  if (DEBUG) {
    printf("partitioned_matrix_get_matrix(%d, %d)\n", horizontal, vertical);
  }

  unsigned int offset_row = 0;
  for (unsigned int vert = 0; vert < vertical; ++vert) {
    offset_row += partitioned_matrix_get_partition(PM, horizontal, vert)->rows;
  }
  if (DEBUG)
    printf("offset_row: %d\n", offset_row);

  unsigned int offset_column = 0;
  for (unsigned int horiz = 0; horiz < horizontal; ++horiz) {
    offset_column +=
        partitioned_matrix_get_partition(PM, horiz, vertical)->columns;
  }
  if (DEBUG)
    printf("offset_column: %d\n", offset_column);

  if (DEBUG)
    puts("getting the partition");

  Partition *partition =
      partitioned_matrix_get_partition(PM, horizontal, vertical);

  if (DEBUG)
    printf("partition->rows = %d, partition->columns = %d\n", partition->rows,
           partition->columns);

  if (DEBUG)
    puts("");

  Matrix *C = matrix_create(partition->rows, partition->columns);

  if (DEBUG)
    puts("copying the matrix");

  for (unsigned int row = 0; row < partition->rows; ++row) {
    for (unsigned int column = 0; column < partition->columns; ++column) {
      unsigned int i = offset_row + row;
      unsigned int j = offset_column + column;
      matrix_set(C, row, column, matrix_get(PM->M, i, j));
    }
  }

  if (DEBUG)
    puts("");

  return C;
}
