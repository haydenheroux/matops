#pragma once

#include <stdbool.h>

#include "partition.h"

/*
 * A system of simultaneous linear equations with the coefficient matrix `A` and
 * the right-hand side matrix `B`.
 */
typedef struct {
  Matrix *A;
  Matrix *B;
  PartitionedMatrix *AX_B;
} System;

/*
 * Creates a system of simultaneous linear equations with the coefficient matrix
 * `A` and the right-hand side matrix `B`.
 */
System *system_create(const Matrix *A, const Matrix *B);

/*
 * Deletes the system of simultaneous linear equations `S`.
 */
void system_delete(System *S);

/*
 * Tests if the system of simultaneous linear equations `S` is consistent.
 */
bool system_is_consistent(const System *S);

/*
 * Tests if the system of simultaneous linear equations `S` has a unique
 * solution (i.e. the solution has no arbitrary scalars).
 */
bool system_has_unique_solution(const System *S);

/*
 * Solves the system of simultaneous linear equations `S`.
 */
PartitionedMatrix *system_solve(const System *S);
