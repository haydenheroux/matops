#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "partition.h"

#define DEBUG false
#define INDEX(PM, h, v) h * PM->vertical_partitions + v

PartitionedMatrix *partitioned_matrix_create(unsigned int rows,
                                             unsigned int columns,
                                             unsigned int horizontal_partitions,
                                             unsigned int vertical_partitions) {
  PartitionedMatrix *PM = malloc(sizeof(PartitionedMatrix));

  PM->M = matrix_create(rows, columns);

  PM->horizontal_partitions = horizontal_partitions;
  PM->vertical_partitions = vertical_partitions;

  PM->partitions =
      calloc(horizontal_partitions * vertical_partitions, sizeof(Partition));

  return PM;
}

void partitioned_matrix_delete(PartitionedMatrix *PM) {
  matrix_delete(PM->M);
  free(PM->partitions);
  free(PM);
}

Partition *partitioned_matrix_get_partition(const PartitionedMatrix *PM,
                                            unsigned int horizontal_partition,
                                            unsigned int vertical_partition) {
  if (DEBUG) {
    printf("partitioned_matrix_get_partition(%d, %d) of %d×%d\n",
           horizontal_partition, horizontal_partition,
           PM->horizontal_partitions, PM->vertical_partitions);
  }

  assert(0 <= horizontal_partition &&
         horizontal_partition < PM->horizontal_partitions);
  assert(0 <= vertical_partition &&
         vertical_partition < PM->vertical_partitions);

  return &PM->partitions[INDEX(PM, horizontal_partition, vertical_partition)];
}

unsigned int partitioned_matrix_row_span(const PartitionedMatrix *PM,
                                         unsigned int horizontal_partition) {
  if (DEBUG) {
    printf("partitioned_matrix_row_span(%d)\n", horizontal_partition);
  }

  unsigned int row_span = 0;

  for (unsigned int vertical_partition = 0;
       vertical_partition < PM->vertical_partitions; ++vertical_partition) {
    Partition *partition = partitioned_matrix_get_partition(
        PM, horizontal_partition, vertical_partition);

    if (partition->row_span != 0) {
      assert(row_span == partition->row_span || row_span == 0);
      row_span = partition->row_span;
    }
  }

  return row_span;
}

unsigned int partitioned_matrix_column_span(const PartitionedMatrix *PM,
                                            unsigned int vertical_partition) {
  if (DEBUG) {
    printf("partitioned_matrix_column_span(%d)\n", vertical_partition);
  }

  unsigned int column_span = 0;

  for (unsigned int horizontal_partition = 0;
       horizontal_partition < PM->horizontal_partitions;
       ++horizontal_partition) {
    Partition *partition = partitioned_matrix_get_partition(
        PM, horizontal_partition, vertical_partition);

    if (partition->column_span != 0) {
      assert(column_span == partition->column_span || column_span == 0);
      column_span = partition->column_span;
    }
  }

  return column_span;
}

void partitioned_matrix_set_partition(PartitionedMatrix *PM,
                                      unsigned int horizontal_partition,
                                      unsigned int vertical_partition,
                                      unsigned int row_span,
                                      unsigned int column_span) {
  if (DEBUG) {
    printf("partitioned_matrix_set_partition(%d, %d) of %d×%d\n",
           horizontal_partition, vertical_partition, PM->horizontal_partitions,
           PM->vertical_partitions);
  }

  assert(0 <= horizontal_partition &&
         horizontal_partition < PM->horizontal_partitions);
  assert(0 <= vertical_partition &&
         vertical_partition < PM->vertical_partitions);

  unsigned int existing_row_span =
      partitioned_matrix_row_span(PM, horizontal_partition);
  unsigned int existing_column_span =
      partitioned_matrix_column_span(PM, vertical_partition);

  if (DEBUG) {
    printf("existing_row_span: %d, existing_column_span: %d\n",
           existing_row_span, existing_column_span);
    printf("desired_row_span: %d, desired_column_span: %d\n", row_span,
           column_span);
  }

  assert(existing_row_span == row_span || existing_row_span == 0);
  assert(existing_column_span == column_span || existing_column_span == 0);

  Partition *partition = partitioned_matrix_get_partition(
      PM, horizontal_partition, vertical_partition);
  partition->row_span = row_span;
  partition->column_span = column_span;
}

unsigned int
partitioned_matrix_offset_row_index(const PartitionedMatrix *PM,
                                    unsigned int horizontal_partition,
                                    unsigned int vertical_partition) {
  unsigned int offset_row = 0;

  for (unsigned int horiz = 0; horiz < horizontal_partition; ++horiz) {
    offset_row +=
        partitioned_matrix_get_partition(PM, horiz, vertical_partition)
            ->row_span;
  }

  return offset_row;
}

unsigned int
partitioned_matrix_offset_column_index(const PartitionedMatrix *PM,
                                       unsigned int horizontal_partition,
                                       unsigned int vertical_partition) {
  unsigned int offset_column = 0;

  for (unsigned int vert = 0; vert < vertical_partition; ++vert) {
    offset_column +=
        partitioned_matrix_get_partition(PM, horizontal_partition, vert)
            ->column_span;
  }

  return offset_column;
}

Matrix *partitioned_matrix_get_matrix(const PartitionedMatrix *PM,
                                      unsigned int horizontal_partition,
                                      unsigned int vertical_partition) {
  if (DEBUG) {
    printf("partitioned_matrix_get_matrix(%d, %d)\n", horizontal_partition,
           vertical_partition);
  }

  assert(0 <= horizontal_partition &&
         horizontal_partition < PM->horizontal_partitions);
  assert(0 <= vertical_partition &&
         vertical_partition < PM->vertical_partitions);

  unsigned int offset_row = partitioned_matrix_offset_row_index(
      PM, horizontal_partition, vertical_partition);

  unsigned int offset_column = partitioned_matrix_offset_column_index(
      PM, horizontal_partition, vertical_partition);

  Partition *partition = partitioned_matrix_get_partition(
      PM, horizontal_partition, vertical_partition);

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

void partitioned_matrix_set_matrix(PartitionedMatrix *PM,
                                   unsigned int horizontal_partition,
                                   unsigned int vertical_partition,
                                   const Matrix *M) {
  assert(0 <= horizontal_partition &&
         horizontal_partition < PM->horizontal_partitions);
  assert(0 <= vertical_partition &&
         vertical_partition < PM->vertical_partitions);

  partitioned_matrix_set_partition(PM, horizontal_partition, vertical_partition,
                                   M->rows, M->columns);

  unsigned int offset_row = partitioned_matrix_offset_row_index(
      PM, horizontal_partition, vertical_partition);

  unsigned int offset_column = partitioned_matrix_offset_column_index(
      PM, horizontal_partition, vertical_partition);

  for (unsigned int matrix_row = 0; matrix_row < M->rows; ++matrix_row) {
    for (unsigned int matrix_column = 0; matrix_column < M->columns;
         ++matrix_column) {
      unsigned int partition_row = offset_row + matrix_row;
      unsigned int partition_column = offset_column + matrix_column;

      matrix_set(PM->M, partition_row, partition_column,
                 matrix_get(M, matrix_row, matrix_column));
    }
  }
}
