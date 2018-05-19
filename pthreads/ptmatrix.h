#ifndef ptmatrix_h
#define ptmatrix_h

#include <pthread.h>
#include "../matrix.h"

typedef struct Thread
{
    size_t id;
    size_t start_range;
    size_t end_range;
    Matrix_t *m1;
    Matrix_t *m2;
} Thread_t;

Matrix_t matrix_mult_pthread(Matrix_t a, Matrix_t b, int number_threads);

#endif
