#include "partition.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define DEBUG false
#define INDEX(PM, v, h) v * PM->horizontal_partitions + h

PartitionedMatrix *
partitioned_matrix_create(unsigned int rows, unsigned int columns,
                          unsigned int vertical_partitions,
                          unsigned int horizontal_partitions) {
  PartitionedMatrix *PM = malloc(sizeof(PartitionedMatrix));

  PM->vertical_partitions = vertical_partitions;
  PM->horizontal_partitions = horizontal_partitions;

  unsigned int size = vertical_partitions * horizontal_partitions;
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
                                            unsigned int vertical_partition,
                                            unsigned int horizontal_partition) {
  if (DEBUG) {
    printf("partitioned_matrix_get_partition(%d, %d) of %d×%d\n",
           vertical_partition, horizontal_partition, PM->vertical_partitions,
           PM->horizontal_partitions);
  }

  return &PM->partitions[INDEX(PM, vertical_partition, horizontal_partition)];
}

unsigned int partitioned_matrix_vertical_partition_row_span(
    const PartitionedMatrix *PM, unsigned int vertical_partition) {
  if (DEBUG) {
    printf("partitioned_matrix_vertical_partition_row_span(%d)\n",
           vertical_partition);
  }

  unsigned int row_span = 0;

  for (unsigned int horizontal_partition = 0;
       horizontal_partition < PM->horizontal_partitions;
       ++horizontal_partition) {
    Partition *partition = partitioned_matrix_get_partition(
        PM, vertical_partition, horizontal_partition);

    if (partition->row_span != 0) {
      assert(row_span == partition->row_span || row_span == 0);
      row_span = partition->row_span;
    }
  }

  return row_span;
}

unsigned int partitioned_matrix_horizontal_partition_column_span(
    const PartitionedMatrix *PM, unsigned int horizontal_partition) {
  if (DEBUG) {
    printf("partitioned_matrix_horizontal_partition_column_span(%d)\n",
           horizontal_partition);
  }

  unsigned int column_span = 0;

  for (unsigned int vertical_partition = 0;
       vertical_partition < PM->vertical_partitions; ++vertical_partition) {
    Partition *partition = partitioned_matrix_get_partition(
        PM, vertical_partition, horizontal_partition);

    if (partition->column_span != 0) {
      assert(column_span == partition->column_span || column_span == 0);
      column_span = partition->column_span;
    }
  }

  return column_span;
}

void partitioned_matrix_set_partition(PartitionedMatrix *PM,
                                      unsigned int vertical_partition,
                                      unsigned int horizontal_partition,
                                      unsigned int row_span,
                                      unsigned int column_span) {
  if (DEBUG) {
    printf("partitioned_matrix_set_partition(%d, %d) of %d×%d\n",
           vertical_partition, horizontal_partition, PM->vertical_partitions,
           PM->horizontal_partitions);
  }

  unsigned int vertical_row_span =
      partitioned_matrix_vertical_partition_row_span(PM, vertical_partition);
  unsigned int horizontal_column_span =
      partitioned_matrix_horizontal_partition_column_span(PM,
                                                          horizontal_partition);

  if (DEBUG) {
    printf("vertical_row_span: %d, horizontal_column_span: %d\n",
           vertical_row_span, horizontal_column_span);
  }

  assert(vertical_row_span == row_span || vertical_row_span == 0);
  assert(horizontal_column_span == column_span || horizontal_column_span == 0);

  Partition *partition = partitioned_matrix_get_partition(
      PM, vertical_partition, horizontal_partition);
  partition->row_span = row_span;
  partition->column_span = column_span;
}

unsigned int
partitioned_matrix_offset_row_index(const PartitionedMatrix *PM,
                                    unsigned int vertical_partition,
                                    unsigned int horizontal_partition) {
  unsigned int offset_row = 0;

  for (unsigned int vert = 0; vert < vertical_partition; ++vert) {
    offset_row +=
        partitioned_matrix_get_partition(PM, vert, horizontal_partition)
            ->row_span;
  }

  return offset_row;
}

unsigned int
partitioned_matrix_offset_column_index(const PartitionedMatrix *PM,
                                       unsigned int vertical_partition,
                                       unsigned int horizontal_partition) {
  unsigned int offset_column = 0;

  for (unsigned int horiz = 0; horiz < horizontal_partition; ++horiz) {
    offset_column +=
        partitioned_matrix_get_partition(PM, vertical_partition, horiz)
            ->column_span;
  }

  return offset_column;
}

Matrix *partitioned_matrix_get_matrix(const PartitionedMatrix *PM,
                                      unsigned int vertical_partition,
                                      unsigned int horizontal_partition) {
  if (DEBUG) {
    printf("partitioned_matrix_get_matrix(%d, %d)\n", vertical_partition,
           horizontal_partition);
  }

  unsigned int offset_row = partitioned_matrix_offset_row_index(
      PM, vertical_partition, horizontal_partition);

  unsigned int offset_column = partitioned_matrix_offset_column_index(
      PM, vertical_partition, horizontal_partition);

  Partition *partition = partitioned_matrix_get_partition(
      PM, vertical_partition, horizontal_partition);

  Matrix *C = matrix_create(partition->row_span, partition->column_span);

  for (unsigned int partition_row = 0; partition_row < partition->row_span;
       ++partition_row) {
    for (unsigned int partition_column = 0;
         partition_column < partition->column_span; ++partition_column) {
      unsigned int matrix_row = offset_row + partition_row;
      unsigned int matrix_column = offset_column + partition_column;

      matrix_set(C, partition_row, partition_column,
                 matrix_get(PM->M, matrix_row, matrix_column));
    }
  }

  return C;
}

void partitioned_matrix_set_matrix(const PartitionedMatrix *PM,
                                   unsigned int vertical_partition,
                                   unsigned int horizontal_partition,
                                   const Matrix *M) {
  Partition *partition = partitioned_matrix_get_partition(
      PM, vertical_partition, horizontal_partition);

  assert(M->rows == partition->row_span &&
         M->columns == partition->column_span);

  unsigned int offset_row = partitioned_matrix_offset_row_index(
      PM, vertical_partition, horizontal_partition);

  unsigned int offset_column = partitioned_matrix_offset_column_index(
      PM, vertical_partition, horizontal_partition);

  for (unsigned int matrix_row = 0; matrix_row < M->rows; ++matrix_row) {
    for (unsigned int matrix_column = 0; matrix_column < M->columns;
         ++matrix_column) {
      unsigned int partition_row = offset_row + matrix_row;
      unsigned int partition_column = offset_column + matrix_column;

      matrix_set(PM->M, partition_row, partition_column,
                 matrix_get(M, matrix_row, matrix_column));
    }
  }

  return;
}
