#include "matrix.h"

Matrix_t matrix_load_from_file(FILE *file)
{
  long i, j;
  double rows, cols, value;
  fscanf(file, "%lf %lf", &rows, &cols);
  Matrix_t matrix = matrix_create(rows, cols);

  while (fscanf(file, "%ld %ld %lf", &i, &j, &value) != EOF)
    matrix_set(matrix, i-1, j-1, value);

  return matrix;
}

Matrix_t matrix_create(long rows, long cols)
{
  Matrix_t A;
  A.rows = rows;
  A.cols = cols;
  A.items = malloc(cols * rows * sizeof(double));

  for (long i = 0; i < rows; i++)
  {
    *(A.items+i) = malloc(cols * sizeof(double));
    for (long j = 0; j < cols; j++)
      A.items[i][j] = 0.0;
  }

  return A;
}

Matrix_t matrix_transpose(Matrix_t a)
{
  Matrix_t b = matrix_create(a.cols, a.rows);
  for (long j = 0; j < a.cols; j++)
    for (long i = 0; i < a.rows; i++)
      matrix_set(b, j, i, a.items[i][j]);
  return b;
}

void matrix_set(Matrix_t a, long row, long col, double value)
{
  a.items[row][col] = value;
}

Matrix_t matrix_mult(Matrix_t a, Matrix_t b)
{
  Matrix_t result = matrix_create(a.rows, b.cols);

  for (int i=0; i<a.rows; i++) {
    for (int j=0; j<b.cols; j++) {
      double sum = 0;
      for (int k=0; k<b.rows; k++) {
        sum += a.items[i][k] * b.items[k][j];
      }
      result.items[i][j] = sum;
    }
  }
  return result;
}

bool matrix_mult_valid(Matrix_t a, Matrix_t b)
{
  return a.cols == b.rows;
}

void matrix_print(Matrix_t a)
{
  for (int i=0; i<a.rows; i++) {
    for (int j=0; j<a.cols; j++) {
      printf("%03lf ", a.items[i][j]);
    }
    printf("\n");
  }
}

void matrix_print_to_file(FILE *output, Matrix_t a)
{
  fprintf(output, "%ld %ld\n", a.rows, a.cols);
  for (long i = 0; i < a.rows; i++)
    for (long j = 0; j < a.rows; j++)
      fprintf(output, "%ld %ld %lf\n", i, j, a.items[i][j]);
}
