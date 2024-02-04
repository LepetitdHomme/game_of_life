#include "includes/common.h"

float random_float(float lower_bound, float upper_bound) {
  // Generate a random integer between 0 and RAND_MAX
  int random_int = rand();

  // Scale and shift the random integer to the range [0, 1]
  float scaled_random = (float)random_int / RAND_MAX;

  // Scale and shift the random float to the specified range [lower_bound, upper_bound]
  float random_float = (upper_bound - lower_bound) * scaled_random + lower_bound;

  return random_float;
}