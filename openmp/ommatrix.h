#ifndef ommatrix_h
#define ommatrix_h

#include <omp.h>
#include "../matrix.h"

Matrix_t matrix_mult_openmp(Matrix_t a, Matrix_t b, int number_threads, int chunk_size);

#endif
