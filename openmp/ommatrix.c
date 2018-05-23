#include "ommatrix.h"
#include "../matrix.h"

Matrix_t matrix_mult_openmp(Matrix_t a, Matrix_t b, int number_threads, int chunk_size)
{
  int tid, nthreads, chunk;
  Matrix_t result = matrix_create(a.rows, b.cols);

  // set loop iteration chunk size
  chunk = chunk_size;

  size_t sparse_threads = 0;
  for(size_t i = 0; i < a.rows; i++)
	if(*(matrix_sparsity(a)+i) != -1)
	  sparse_threads++;

  nthreads = number_threads - sparse_threads;

  omp_set_dynamic(0);
  omp_set_num_threads(nthreads);
  
  // Spawn a parallel region explicitly scoping all variables
  #pragma omp parallel shared(a,b,result,nthreads,chunk) private(tid)
  {
    tid = omp_get_thread_num();
    if (tid == 0)
      nthreads = number_threads - sparse_threads;

    // Do matrix multiply sharing iterations on outer loop
    // Display who does which iterations for demonstration purposes
    //printf("Thread %d starting matrix multiply...\n",tid);
    #pragma omp for schedule (static, chunk)
    for (size_t i = 0; i < nthreads+1; i++)
    {
	  for(size_t m = 0; m < sparse_threads; m++)
	    if(*(matrix_sparsity(a)+m) == i && *(matrix_sparsity(a)) > -1)
		  i++;
		
      //printf("Thread=%d did row=%ld\n",tid,i);
      for(size_t j = 0; j < b.cols; j++)
        for (size_t k = 0; k < a.cols; k++)
          result.items[i][j] += a.items[i][k] * b.items[k][j];
    }
  }   //End of parallel region

  return result;
}
