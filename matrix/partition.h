#pragma once

#include "matrix.h"

/*
 * A partition spanning `row_span` rows and `column_span` columns.
 */
typedef struct {
  unsigned int row_span;
  unsigned int column_span;
} Partition;

/*
 * A set of partitions, with `vertical_partitions` vertical partitions and
 * `horizontal_partitions` horizontal partitions.
 */
typedef struct {
  unsigned int vertical_partitions;
  unsigned int horizontal_partitions;
  Partition *partitions;
  Matrix *M;
} PartitionedMatrix;

/*
 * Creates a partitioned matrix with `rows` rows, `columns` columns,
 * `vertical_partitions` vertical partitions and `horizontal_partitions`
 * horizontal partitions.
 */
PartitionedMatrix *
partitioned_matrix_create(unsigned int rows, unsigned int columns,
                          unsigned int vertical_partitions,
                          unsigned int horizontal_partitions);

/*
 * Deletes the partitioned matrix `PM`.
 */
void partitioned_matrix_delete(PartitionedMatrix *PM);

/*
 * Gets the partition of the partitioned matrix `PM` at the
 * `vertical_partition` vertical partition and the `horizontal_partition`
 * horizontal partition.
 */
Partition *partitioned_matrix_get_partition(const PartitionedMatrix *PM,
                                            unsigned int vertical_partition,
                                            unsigned int horizontal_partition);

/*
 * Calculates the number of rows of the partitioned matrix `PM` spanned by
 * the partitions in the `vertical_partition` vertical partition.
 */
unsigned int
partitioned_matrix_vertical_partition_row_span(const PartitionedMatrix *PM,
                                               unsigned int vertical_partition);

/*
 * Calculates the number of columns of the partitioned matrix `PM` spanned by
 * the partitions in the `horizontal_partition` horizontal partition.
 */
unsigned int partitioned_matrix_horizontal_partition_column_span(
    const PartitionedMatrix *PM, unsigned int horizontal_partition);

/*
 * Sets the partition of the partitioned matrix `PM` at the
 * `vertical_partition` vertical partition and the `horizontal_partition`
 * horizontal partition to span `row_span` rows and `column_span` columns.
 */
void partitioned_matrix_set_partition(PartitionedMatrix *PM,
                                      unsigned int vertical_partition,
                                      unsigned int horizontal_partition,
                                      unsigned int row_span,
                                      unsigned int column_span);

/*
 * Calculates the row offset into the partitioned matrix `PM` of the partition
 * at the `vertical_partition` vertical partition and the `horizontal_partition`
 * horizontal partition.
 */
unsigned int
partitioned_matrix_offset_row_index(const PartitionedMatrix *PM,
                                    unsigned int vertical_partition,
                                    unsigned int horizontal_partition);

/*
 * Calculates the column offset into the partitioned matrix `PM` of the
 * partition at the `vertical_partition` vertical partition and the
 * `horizontal_partition` horizontal partition.
 */
unsigned int
partitioned_matrix_offset_column_index(const PartitionedMatrix *PM,
                                       unsigned int vertical_partition,
                                       unsigned int horizontal_partition);

// TODO Use with `MatrixView` or similar
/*
 * Gets the matrix of the partitioned matrix `PM` at the `vertical_partition`
 * vertical partition and the `horizontal_partition` horizontal partition.
 */
Matrix *partitioned_matrix_get_matrix(const PartitionedMatrix *PM,
                                      unsigned int vertical_partition,
                                      unsigned int horizontal_partition);

/*
 * Sets the partition of the partitioned matrix `PM` at the
 * `vertical_partition` vertical partition and the `horizontal_partition`
 * horizontal partition to the matrix `M`.
 */
void partitioned_matrix_set_matrix(const PartitionedMatrix *PM,
                                   unsigned int vertical_partition,
                                   unsigned int horizontal_partition,
                                   const Matrix *M);
