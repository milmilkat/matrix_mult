#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"

// some utils unit testing functions
void assertEquals(double, double);

// functions for unit testing
void test_small_matrix_mult(void);
void test_matrix_transpose(void);

int main(int argc, char *argv[])
{
  printf(ANSI_COLOR_YELLOW "************************\n");
  printf(ANSI_COLOR_YELLOW "** Running Unit tests **\n");
  printf(ANSI_COLOR_YELLOW "************************\n");
  test_small_matrix_mult();
  test_matrix_transpose();
  printf("\nAll tests have passed.\n");
}

// all tests should be defined by new functions
void test_small_matrix_mult()
{
    printf(ANSI_COLOR_YELLOW "\nrunning test_small_matrix_mult\n");
    // prepare data
    Matrix_t A = matrix_create(2, 2);
    Matrix_t X = matrix_create(2, 3);

    matrix_set(A, 0, 0, 1.0); matrix_set(A, 0, 1, 2.0);
    matrix_set(A, 1, 0, 3.0); matrix_set(A, 1, 1, 4.0);
    matrix_set(X, 0, 0, 1.0); matrix_set(X, 0, 1, 2.0); matrix_set(X, 0, 2, 2.0);
    matrix_set(X, 1, 0, 3.0); matrix_set(X, 1, 1, 4.0); matrix_set(X, 1, 2, 2.0);

    // run test
    Matrix_t B = matrix_mult(A, X);

    // run assertions
    assertEquals(2, B.rows);
    assertEquals(3, B.cols);
    assertEquals(7.0,  B.items[0][0]);
    assertEquals(10.0, B.items[0][1]);
    assertEquals(6.0,  B.items[0][2]);
    assertEquals(15.0,  B.items[1][0]);
    assertEquals(22.0,  B.items[1][1]);
    assertEquals(14.0,  B.items[1][2]);
}

void test_matrix_transpose()
{
  printf(ANSI_COLOR_YELLOW "\nrunning test_matrix_transpose\n");
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
