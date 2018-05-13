#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define RANDOM_DECIMAL 0.009923409809809809

int main(int argc, char* argv[])
{
  if (argc < 3)
  {
    printf("Usage: genmatrix <number_of_rows> <number_of_cols>\n");
    exit(-1);
  }

  long rows, cols;

  rows = strtol(argv[1], NULL, 10);
  cols = strtol(argv[2], NULL, 10);

  srand(time(0));

  printf("%ld %ld\n", rows, cols);
  for (long i = 1; i <= rows; i++)
    for (long j = 1; j <= cols; j++) {
      double val = (rand() % 1000000) / RANDOM_DECIMAL;
      printf("%ld %ld %lf\n", i, j, val);
    }

  printf("\n");
}
