#include "ommatrix.h"

Matrix_t matrix_mult_openmp(Matrix_t a, Matrix_t b, int number_threads, int chunk_size)
{
  int tid, nthreads, chunk;
  Matrix_t result = matrix_create(a.rows, b.cols);
  omp_set_dynamic(0);
  omp_set_num_threads(number_threads);

  // set loop iteration chunk size
  chunk = chunk_size;

  // Spawn a parallel region explicitly scoping all variables
  #pragma omp parallel shared(a,b,result,nthreads,chunk) private(tid)
  {
    tid = omp_get_thread_num();
    if (tid == 0)
    {
      nthreads = number_threads;//omp_set_num_threads(number_threads); //omp_get_num_threads();
      omp_set_dynamic(0);
      omp_set_num_threads(number_threads);
      printf("Starting matrix multiple example with %d threads\n",nthreads);
    }

    // Do matrix multiply sharing iterations on outer loop
    // Display who does which iterations for demonstration purposes
    printf("Thread %d starting matrix multiply...\n",tid);
    #pragma omp for schedule (static, chunk)
    for (long i=0; i<a.rows; i++)
    {
      printf("Thread=%d did row=%ld\n",tid,i);
      for(long j=0; j<b.cols; j++)
        for (long k=0; k<a.cols; k++)
          result.items[i][j] += a.items[i][k] * b.items[k][j];
    }
  }   //End of parallel region

  return result;
}
