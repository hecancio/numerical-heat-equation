/**
 * @file heat_solver.h
 * @brief Header file for the 1D Heat Equation solver.
 */

#ifndef HEAT_SOLVER_H
#define HEAT_SOLVER_H

#include <stddef.h>

/**
 * @brief Computes a single time step for the 1D heat equation.
 */
void step_heat_1d(const double *u, double *u_next, size_t N, double r);

#endif // HEAT_SOLVER_H