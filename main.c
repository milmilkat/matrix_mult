#include "pthreads/ptmatrix.h"
#include "openmp/ommatrix.h"
#include <stdint.h>
#include "util.h"
#include <string.h>

char *matrix_path_a, *matrix_path_b, *matrix_path_c;
FILE *matrix_file_a, *matrix_file_b, *matrix_file_c;

void release_resources(void);
void open_matrix_files(void);

int main(int argc, char *argv[]) {
  int param_offset = 0;
  if (argc < 3)
  {
    printf("usage main [opt] <matrix_a_file> <matrix_b_file> <matrix_c_output_file>\n");
    printf("available options:\n");
    printf("\tp if you want to run using pthreads\n");
    printf("\to if you want to run using openmp\n");
    printf("\tif no option is provided, it will run as a single threaded app\n");
    exit(-1);
  }

  char opt = 's'; // single threaded version
  if (argc == 5)
  {
    opt = argv[1][0];
    param_offset++;
  }

  matrix_path_a = malloc(sizeof(char) * strlen(argv[1 + param_offset]));
  matrix_path_b = malloc(sizeof(char) * strlen(argv[2 + param_offset]));
  matrix_path_c = malloc(sizeof(char) * strlen(argv[3 + param_offset]));

  strcpy(matrix_path_a, argv[1 + param_offset]);
  strcpy(matrix_path_b, argv[2 + param_offset]);
  strcpy(matrix_path_c, argv[3 + param_offset]);

  open_matrix_files();

  Matrix_t a = matrix_load_from_file(matrix_file_a);
  Matrix_t b = matrix_load_from_file(matrix_file_b);
  Matrix_t c;

  // retrieving sparsity
  size_t *nsmatrix = non_sparsing_matrix(a);
  size_t size_of_nsp = size_of_non_sparsed(nsmatrix, a.rows);

  // given a and b are valid matrix,
  // validates if a is able to be multiplied by b.
  if (matrix_mult_valid(a, b))
  {
    switch (opt)
    {
      case 'p':
        printf("using pthreads version\n");
        c = matrix_mult_pthread(a, b, nsmatrix, size_of_nsp);
        break;
      case 'o':
        printf("using openmp version\n");
        c = matrix_mult_openmp(a, b, nsmatrix, size_of_nsp);
        break;
      default:
        printf("using single threaded version\n");
        c = matrix_mult(a, b);
    }
    matrix_print_to_file(matrix_file_c, c);
    printf("Results written to %s\n", matrix_path_c);
    release_resources();
    return 0;
  }
  else
  {
    printf("The # of columns of A must be the same # of lines of B.");
    release_resources();
    exit(-3);
  }
}

void open_matrix_files(void)
{
  matrix_file_a = fopen(matrix_path_a, "r");
  matrix_file_b = fopen(matrix_path_b, "r");
  matrix_file_c = fopen(matrix_path_c, "w");

  if (!matrix_file_a)
  {
    printf("Could not open file with matrix a definitions\n");
    release_resources();
    exit(-2);
  }

  if (!matrix_file_b)
  {
    printf("Could not open file with matrix b definitions\n");
    release_resources();
    exit(-2);
  }

  if (!matrix_file_c)
  {
    printf("Could not open file for matrix c results\n");
    release_resources();
    exit(-2);
  }

}

void release_resources(void)
{
  free(matrix_path_a);
  free(matrix_path_b);
  free(matrix_path_c);
  fclose(matrix_file_a);
  fclose(matrix_file_b);
  fclose(matrix_file_c);
}
