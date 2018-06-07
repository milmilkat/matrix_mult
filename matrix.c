#include "matrix.h"

Matrix_t matrix_load_from_file(FILE *file)
{
  size_t i, j;
  double rows, cols, value;
  fscanf(file, "%lf %lf", &rows, &cols);
  Matrix_t matrix = matrix_create(rows, cols);

  while (fscanf(file, "%ld %ld %lf", &i, &j, &value) != EOF)
    matrix_set(matrix, i-1, j-1, value);

  return matrix;
}

Matrix_t matrix_create(size_t rows, size_t cols)
{
  Matrix_t A;
  A.rows = rows;
  A.cols = cols;
  A.items = malloc(cols * rows * sizeof(double));

  for (size_t i = 0; i < rows; i++)
  {
    *(A.items+i) = malloc(cols * sizeof(double));
    for (size_t j = 0; j < cols; j++)
      A.items[i][j] = 0.0;
  }

  return A;
}

Matrix_t matrix_transpose(Matrix_t a)
{
  Matrix_t b = matrix_create(a.cols, a.rows);
  for (size_t j = 0; j < a.cols; j++)
    for (size_t i = 0; i < a.rows; i++)
      matrix_set(b, j, i, a.items[i][j]);
  return b;
}

void matrix_set(Matrix_t a, size_t row, size_t col, double value)
{
  a.items[row][col] = value;
}

Matrix_t matrix_mult(Matrix_t a, Matrix_t b)
{
  Matrix_t result = matrix_create(a.rows, b.cols);

  for (size_t i=0; i<a.rows; i++) {
    for (size_t j=0; j<b.cols; j++) {
      double sum = 0;
      for (size_t k=0; k<b.rows; k++) {
        sum += a.items[i][k] * b.items[k][j];
      }
      result.items[i][j] = sum;
    }
  }
  return result;
}

Matrix_t matrix_mult_t(Matrix_t a, Matrix_t b)
{
  Matrix_t result = matrix_create(a.rows, b.rows);

  for (size_t i=0; i<a.rows; i++) {
    for (size_t j=0; j<b.rows; j++) {
      double sum = 0;
      for (size_t k=0; k<b.cols; k++) {
        sum += a.items[i][k] * b.items[j][k];
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
  for (size_t i=0; i<a.rows; i++) {
    for (size_t j=0; j<a.cols; j++) {
      printf("%03lf ", a.items[i][j]);
    }
    printf("\n");
  }
}

void matrix_print_to_file(FILE *output, Matrix_t a)
{
  fprintf(output, "%ld %ld\n", a.rows, a.cols);
  for (size_t i = 0; i < a.rows; i++)
    for (size_t j = 0; j < a.cols; j++)
      if (a.items[i][j] != 0.0)
        fprintf(output, "%ld %ld %lf\n", i+1, j+1, a.items[i][j]);
}

size_t* non_sparsing_matrix(Matrix_t a)
{
  size_t *result = malloc(a.rows * sizeof(size_t));
  size_t m = 0;
  for (size_t k = 0; k < a.rows; k++)
	  *(result+k) = -1;

  for (size_t i = 0; i < a.rows; i++)
    for (size_t j = 0; j < a.cols; j++)
    {
      if (a.items[i][j] != 0.0)
      {
        *(result + m) = i;
        m++;
        break;
      }
    }
  return result;
}

size_t size_of_non_sparsed(size_t *sp, size_t rows)
{
  size_t count = 0;
  for (; sp[count] != -1 && count < rows; count++);
  return count;
}
