#include "includes/common.h"

float gaussianKernel(int i, int j) {
  // Define discrete Gaussian kernel (example)
  static float gaussianKernel[KERNEL_SIZE][KERNEL_SIZE] = {
    {0.075, 0.125, 0.075},
    {0.125, 0.200, 0.125},
    {0.075, 0.125, 0.075}
  };

  return gaussianKernel[i][j];
}

float vonNeumannKernel(int i, int j) {
  // Define discrete Von Neumann kernel
  static float vonNeumannKernel[KERNEL_SIZE][KERNEL_SIZE] = {
    {0, 1, 0},
    {1, 1, 1},
    {0, 1, 0}
  };

  return vonNeumannKernel[i][j];
}

float mooreKernel(int i, int j) {
  // Define discrete Moore kernel
  static float mooreKernel[KERNEL_SIZE][KERNEL_SIZE] = {
    {1, 1, 1},
    {1, 1, 1},
    {1, 1, 1}
  };

  return mooreKernel[i][j];
}

float conwayKernel(int i, int j) {
  // Define discrete Moore kernel
  static float conwayKernel[KERNEL_SIZE][KERNEL_SIZE] = {
    {1, 1, 1},
    {1, 0, 1},
    {1, 1, 1}
  };

  return conwayKernel[i][j];
}

float random_float(float lower_bound, float upper_bound) {
    // Generate a random integer between 0 and RAND_MAX
    int random_int = rand();

    // Scale and shift the random integer to the range [0, 1]
    float scaled_random = (float)random_int / RAND_MAX;

    // Scale and shift the random float to the specified range [lower_bound, upper_bound]
    float random_float = (upper_bound - lower_bound) * scaled_random + lower_bound;

    return random_float;
}