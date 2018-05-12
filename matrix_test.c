#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"

// some utils unit testing functions
void assertEquals(double, double);

// functions for unit testing
void test_matrix_transpose(void);

int main(int argc, char *argv[])
{
  printf("************************\n");
  printf("** Running Unit tests **\n");
  printf("************************\n\n");
  test_matrix_transpose();
  printf("\nAll tests have passed.\n");
}

// all tests should be defined by new functions

void test_matrix_transpose()
{
  Matrix_t M = matrix_create(3, 2);
  matrix_set(M, 0, 0, 1.0); matrix_set(M, 0, 1, 2.0);
  matrix_set(M, 1, 0, 3.0); matrix_set(M, 1, 1, 4.0);
  matrix_set(M, 2, 0, 5.0); matrix_set(M, 2, 1, 6.0);

  Matrix_t Mt = matrix_transpose(M);
  assertEquals(1.0, Mt.items[0][0]);
  assertEquals(3.0, Mt.items[0][1]);
  assertEquals(5.0, Mt.items[0][2]);
}

void assertEquals(double expected, double current)
{
  if (expected != current)
  {
    printf(ANSI_COLOR_RED "Should be %lf, but was %lf\n", expected, current);
    exit(0);
  } else
  {
    printf(ANSI_COLOR_GREEN "%lf equals to %lf\n", expected, current);
  }
}
