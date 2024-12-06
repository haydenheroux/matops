#include <stdio.h>

#include "partition.h"

/*
 * PM = [ 1 2
 *        3 4 ]
 *
 * 1×1 partitions
 */
void test_1_1() {
  PartitionedMatrix *PM = partitioned_matrix_create(2, 2, 2, 2);

  matrix_set(PM->M, 0, 0, 1);
  matrix_set(PM->M, 0, 1, 2);
  matrix_set(PM->M, 1, 0, 3);
  matrix_set(PM->M, 1, 1, 4);

  partitioned_matrix_set_partition(PM, 0, 0, 1, 1);
  partitioned_matrix_set_partition(PM, 0, 1, 1, 1);
  partitioned_matrix_set_partition(PM, 1, 0, 1, 1);
  partitioned_matrix_set_partition(PM, 1, 1, 1, 1);

  puts("1×1 partitions");
  matrix_print(partitioned_matrix_get_matrix(PM, 0, 0));
  puts("");
  matrix_print(partitioned_matrix_get_matrix(PM, 0, 1));
  puts("");
  matrix_print(partitioned_matrix_get_matrix(PM, 1, 0));
  puts("");
  matrix_print(partitioned_matrix_get_matrix(PM, 1, 1));
}

/*
 * PM = [ 1 2
 *        3 4 ]
 *
 * 1×2 partitions
 */
void test_1_2() {
  PartitionedMatrix *PM = partitioned_matrix_create(2, 2, 1, 2);

  matrix_set(PM->M, 0, 0, 1);
  matrix_set(PM->M, 0, 1, 2);
  matrix_set(PM->M, 1, 0, 3);
  matrix_set(PM->M, 1, 1, 4);

  partitioned_matrix_set_partition(PM, 0, 0, 1, 2);
  partitioned_matrix_set_partition(PM, 0, 1, 1, 2);

  puts("1×2 partitions");
  matrix_print(partitioned_matrix_get_matrix(PM, 0, 0));
  puts("");
  matrix_print(partitioned_matrix_get_matrix(PM, 0, 1));
}

/*
 * PM = [ 1 2
 *        3 4 ]
 *
 * 2×1 partitions
 */
void test_2_1() {
  PartitionedMatrix *PM = partitioned_matrix_create(2, 2, 2, 1);

  matrix_set(PM->M, 0, 0, 1);
  matrix_set(PM->M, 0, 1, 2);
  matrix_set(PM->M, 1, 0, 3);
  matrix_set(PM->M, 1, 1, 4);

  partitioned_matrix_set_partition(PM, 0, 0, 2, 1);
  partitioned_matrix_set_partition(PM, 1, 0, 2, 1);

  puts("2×1 partitions");
  matrix_print(partitioned_matrix_get_matrix(PM, 0, 0));
  puts("");
  matrix_print(partitioned_matrix_get_matrix(PM, 1, 0));
}

int main() {
  test_1_1();
  puts("");
  test_1_2();
  puts("");
  test_2_1();
}
