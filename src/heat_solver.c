/**
 * @file heat_solver.c
 * @brief High-performance computational core for the 1D Heat Equation.
 *
 * This file implements the finite difference solver in pure C, designed
 * to be compiled as a shared library and linked with Python via ctypes.
 */

#include <stddef.h>
#include "heat_solver.h" // Include own header to verify signature consistency

/**
 * @brief Computes a single time step for the 1D heat equation.
 *
 * Uses an explicit finite difference scheme (Forward Euler in time,
 * central differences in space).
 *
 * @param u      Current temperature state array (size N).
 * @param u_next Output array for the next time step (size N).
 * @param N      Number of spatial grid points.
 * @param r      Dimensionless diffusion coefficient (alpha * dt / dx^2).
 *               Must be <= 0.5 to satisfy the CFL stability condition.
 */
void step_heat_1d(const double *u, double *u_next, size_t N, double r) {
    // Guard clause: prevent out-of-bounds access on invalid grid sizes
    if (N < 2) {
        return;
    }

    // Dirichlet boundary conditions: fixed temperature at both ends
    u_next[0] = u[0];
    u_next[N - 1] = u[N - 1];

    // Interior points: explicit finite difference update
    // The compiler can optimize this loop (e.g., via SIMD vectorization with -O3)
    for (size_t i = 1; i < N - 1; i++) {
        u_next[i] = u[i] + r * (u[i + 1] - 2.0 * u[i] + u[i - 1]);
    }
}