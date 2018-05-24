#include "ptmatrix.h"

static pthread_t *pthreads;

/*
 result for matrix multiplication using pthreads
*/
static Matrix_t _result;

/*
 private function to be carried out by threads
*/
static void* _mult_pthread(void *params)
{
  Thread_t *tparam = (Thread_t*) params;
  Matrix_t *a = tparam->m1;
  Matrix_t *b = tparam->m2;

  // running matrix multiplication on given range of rows of matrix a
  size_t row_to_compute = tparam->row_to_compute;

  for (size_t j = 0; j < b->cols; j++) // columns of matrix b
  {
    _result.items[row_to_compute][j] = 0.0;
    for (size_t k = 0; k < b->rows; k++) // rows of matrix b
      _result.items[row_to_compute][j] += a->items[row_to_compute][k] * b->items[k][j];
  }

  return NULL;
}

Matrix_t matrix_mult_pthread(Matrix_t a, Matrix_t b, size_t *sparsity)
{
  size_t number_threads = a.rows;
  pthreads = malloc(sizeof(pthread_t) * number_threads);
  if (pthreads == NULL)
  {
    printf("Cannot allocate memory for %d threads\n", number_threads);
    exit(-1);
  }

  long range;
  long N = a.rows;

  if (N < number_threads)
  {
    range = 1;
    number_threads = N;
  }
  else
    range = N / number_threads;

  _result = matrix_create(a.rows, b.cols);

  for (int tid = 0; tid < number_threads; tid++)
  {
    if (sparsity[tid] > 0 && sparsity[tid] == tid) {
      Thread_t *tparam = malloc(sizeof(Thread_t));
      tparam->id = tid;
      tparam->row_to_compute = tid;
      tparam->m1 = &a;
      tparam->m2 = &b;

      pthread_create(&pthreads[tid], NULL, _mult_pthread, (void*) tparam);
    }
  }

  for (int tid = 0; tid < number_threads; tid++)
    pthread_join(pthreads[tid], NULL);

  return _result;
}
