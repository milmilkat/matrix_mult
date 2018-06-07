#include "../pthreads/ptmatrix.h"
#include "../openmp/ommatrix.h"
#include <stdint.h>
#include "../util.h"
#include <string.h>
#include <stdbool.h>

// constants
#define RANDOM_DECIMAL 0.009923409809809809
#define NUM_EXEC 10
#define CHUNKS 1

// prototypes
Matrix_t genmatrix(long);
Matrix_t gensparsematrix(long);

int main(int argc, char *argv[])
{
  char opt[7];
  size_t size;

  if (argc != 3)
  {
    printf("usage: bin/bench <opt> <size>\n");
    printf("\topt: [normal|sparse]\n");
    exit(-1);
  }

  size = atol(argv[2]);
  srand(time(0));

  uint64_t start, end;
  uint64_t time_pthreads, time_openmp, time_single_thread;

  // create squared matrix A and matrix B with size (size)
  Matrix_t A;
  if (strcmp("sparse", argv[1]) == 0)
    A = gensparsematrix(size);
  else
    A = genmatrix(size);
  Matrix_t B = genmatrix(size);

  size_t *nsmatrix = non_sparsing_matrix(A);
  size_t size_of_nsp = size_of_non_sparsed(nsmatrix, A.rows);

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
      matrix_mult_pthread(A, B, nsmatrix, size_of_nsp);
      end = get_time();
      time_pthreads += (end - start);
    }

    // run matrix multiplication with openmp
    time_openmp = 0;
    for (int i = 0; i < NUM_EXEC; i++)
    {
      start = get_time();
      matrix_mult_openmp(A, B, nsmatrix, size_of_nsp);
      end = get_time();
      time_openmp += (end - start);
    }

    printf("Avg single thread: %ld\n", time_single_thread / NUM_EXEC);
    printf("Avg pthreads.....: %ld\n", time_pthreads / NUM_EXEC);
    printf("Avg openmp.......: %ld\n\n", time_openmp / NUM_EXEC);
  }
}

Matrix_t genmatrix(long size)
{
  Matrix_t M = matrix_create(size, size);
  for (long i = 0; i < size; i++)
    for (long j = 0; j < size; j++) {
      double val = (rand() % 1000000) / RANDOM_DECIMAL;
      matrix_set(M, i, j, val);
    }
  return M;
}

Matrix_t gensparsematrix(long size)
{
  Matrix_t M = matrix_create(size, size);

  size_t number_of_non_sparsed_rows = size / 2;
  size_t non_sparsed_rows[number_of_non_sparsed_rows];
  for (int k = 0; k < number_of_non_sparsed_rows; k++)
    non_sparsed_rows[k] = rand() % size;

  for (long i = 0; i < number_of_non_sparsed_rows; i++)
    for (long j = 0; j < size; j++) {
      double val = (rand() % 1000000) / RANDOM_DECIMAL;
      matrix_set(M, non_sparsed_rows[i], j, val);
    }
  return M;
}
