#include "../pthreads/ptmatrix.h"
#include "../openmp/ommatrix.h"
#include <stdint.h>
#include "../util.h"
#include <string.h>

// constants
#define RANDOM_DECIMAL 0.009923409809809809
#define NUM_EXEC 10
#define NUM_THREADS 4
#define CHUNKS 1

// prototypes
Matrix_t genmatrix(long, long);

int main(int argc, char *argv[])
{
  srand(time(0));

  uint64_t start, end;
  uint64_t time_pthreads, time_openmp, time_single_thread;

  // create matrix A and matrix B
  Matrix_t A = genmatrix(100, 100);
  Matrix_t B = genmatrix(100, 100);

  for (int sample = 0; sample < 10; sample++)
  {
    // run matrix multiplication without threads
    time_single_thread = 0;
    for (int i = 0; i < NUM_EXEC; i++)
    {
      start = get_time();
      matrix_mult(A, B);
      end = get_time();
      time_single_thread += (end - start);
    }

    // run matrix multiplication with pthreads
    time_pthreads = 0;
    for (int i = 0; i < NUM_EXEC; i++)
    {
      start = get_time();
      matrix_mult_pthread(A, B, NUM_THREADS);
      end = get_time();
      time_pthreads += (end - start);
    }

    // run matrix multiplication with openmp
    time_openmp = 0;
    for (int i = 0; i < NUM_EXEC; i++)
    {
      start = get_time();
      matrix_mult_openmp(A, B, NUM_THREADS, CHUNKS);
      end = get_time();
      time_openmp += (end - start);
    }

    printf("Avg single thread: %d\n", time_single_thread / NUM_EXEC);
    printf("Avg pthreads.....: %d\n", time_pthreads / NUM_EXEC);
    printf("Avg openmp.......: %d\n\n", time_openmp / NUM_EXEC);
  }
}

Matrix_t genmatrix(long rows, long cols)
{
  Matrix_t M = matrix_create(rows, cols);
  for (long i = 0; i < rows; i++)
    for (long j = 0; j < cols; j++) {
      double val = (rand() % 1000000) / RANDOM_DECIMAL;
      matrix_set(M, i, j, val);
    }
  return M;
}
