#ifndef ptmatrix_h
#define ptmatrix_h

#include <pthread.h>
#include "../matrix.h"

typedef struct Thread
{
    size_t id;
    size_t row_to_compute;
    Matrix_t *m1;
    Matrix_t *m2;
} Thread_t;

Matrix_t matrix_mult_pthread(Matrix_t a, Matrix_t b, size_t *sparsity);

#endif
