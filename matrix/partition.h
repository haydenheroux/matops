#pragma once

#include "matrix.h"

/*
 * A partition with `rows` rows and `columns` columns.
 */
typedef struct {
  unsigned int rows;
  unsigned int columns;
} Partition;

/*
 * A set of partitions, with `horizontal` horizontal partitions and `vertical`
 * vertical partitions.
 */
typedef struct {
  unsigned int horizontal;
  unsigned int vertical;
  Partition *partitions;
  Matrix *M;
} PartitionedMatrix;

/*
 * Creates a partitioned matrix with `rows` rows, `columns` columns,
 * `horizontal` horizontal partitions, and `vertical` vertical partitions.
 */
PartitionedMatrix *partitioned_matrix_create(unsigned int rows,
                                             unsigned int columns,
                                             unsigned int horizontal,
                                             unsigned int vertical);

/*
 * Deletes the partitioned matrix `PM`.
 */
void partitioned_matrix_delete(PartitionedMatrix *PM);

/*
 * Gets the partition of the partitioned matrix `PM` at `horizontal`
 * and `vertical`.
 */
Partition *partitioned_matrix_get_partition(const PartitionedMatrix *PM,
                                            unsigned int horizontal,
                                            unsigned int vertical);

/*
 * Sets the size of the partition of the partitioned matrix `PM` at `horizontal`
 * and `vertical` to `rows` rows and `columns` columns.
 */
void partitioned_matrix_set_partition(PartitionedMatrix *PM,
                                      unsigned int horizontal,
                                      unsigned int vertical, unsigned int rows,
                                      unsigned int columns);

// TODO Use with `MatrixView` or similar
/*
 * Gets the matrix of the partitioned matrix `PM` at `horizontal` and
 * `vertical`.
 */
Matrix *partitioned_matrix_get_matrix(const PartitionedMatrix *PM,
                                      unsigned int horizontal,
                                      unsigned int vertical);
