#include "ommatrix.h"

Matrix_t matrix_mult_openmp(Matrix_t a, Matrix_t b, size_t *non_sparse_rows, size_t non_sparse_size)
{
  int tid, chunk;
  size_t nthreads;
  Matrix_t result = matrix_create(a.rows, b.cols);

  // set loop iteration chunk size
  chunk = 1;
  size_t *nsrows = non_sparse_rows;
  nthreads = non_sparse_size ;

  omp_set_dynamic(0);
  omp_set_num_threads(nthreads);
  
  // Spawn a parallel region explicitly scoping all variables
  #pragma omp parallel shared(a,b,result,nthreads,chunk) private(tid)
  {
    tid = omp_get_thread_num();
    if (tid == 0)
      nthreads = non_sparse_size;

    // Do matrix multiply sharing iterations on outer loop
    // Display who does which iterations for demonstration purposes
    //printf("Thread %d starting matrix multiply...\n",tid);
    #pragma omp for schedule (static, chunk)
    for (size_t i = 0; i < nthreads; i++)
    {		
      //printf("Thread=%d did row=%ld\n",tid,i);
      for(size_t j = 0; j < b.cols; j++)
        for (size_t k = 0; k < a.cols; k++)
          result.items[*(nsrows+i)][j] += a.items[*(nsrows+i)][k] * b.items[k][j];
    }
  }   //End of parallel region

  return result;
}
