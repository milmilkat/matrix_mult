#ifndef ommatrix_h
#define ommatrix_h

#include <omp.h>
#include "../matrix.h"

Matrix_t matrix_mult_openmp(Matrix_t a, Matrix_t b, size_t *non_sparse_rows, size_t non_sparse_size);

#endif
