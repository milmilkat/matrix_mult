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

Matrix_t matrix_mult_t(Matrix_t a, Matrix_t b)
{
  Matrix_t result = matrix_create(a.rows, b.rows);

  for (int i=0; i<a.rows; i++) {
    for (int j=0; j<b.rows; j++) {
      double sum = 0;
      for (int k=0; k<b.cols; k++) {
        sum += a.items[i][k] * b.items[j][k];
      }
      result.items[i][j] = sum;
    }
  }
  return result;
}

Matrix_t matrix_add(Matrix_t a, Matrix_t b)
{
  Matrix_t result = matrix_create(a.rows, b.rows);
  int N = a.rows;

  for(int i = 0; i < N; i++) 
    for(int j = 0; j < N; j++)
       result.items[i][j] = a.items[i][j] + b.items[i][j];

  return result;
}

Matrix_t matrix_subtract(Matrix_t a, Matrix_t b)
{
  Matrix_t result = matrix_create(a.rows, b.rows);
  int N = a.rows;

  for(int i = 0; i < N; i++) 
    for(int j = 0; j < N; j++)
       result.items[i][j] = a.items[i][j] - b.items[i][j];

  return result;
}

Matrix_t strassen(Matrix_t a, Matrix_t b) {
  Matrix_t result = matrix_create(a.rows, b.rows);
  long N = a.rows;

  Matrix_t temp1 = matrix_create(a.rows/2, b.rows/2);
  Matrix_t temp2 = matrix_create(a.rows/2, b.rows/2);

  Matrix_t A, B, C, D, E, F, G, H;
  Matrix_t P1, P2, P3, P4, P5, P6, P7;
  Matrix_t Q1, Q2, Q3, Q4;

  if(N <= 2)
	return matrix_mult(a , b);

  A = matrix_create(a.rows/2, b.rows/2);
  B = matrix_create(a.rows/2, b.rows/2);
  C = matrix_create(a.rows/2, b.rows/2);
  D = matrix_create(a.rows/2, b.rows/2);
  E = matrix_create(a.rows/2, b.rows/2);
  F = matrix_create(a.rows/2, b.rows/2);
  G = matrix_create(a.rows/2, b.rows/2);
  H = matrix_create(a.rows/2, b.rows/2);

  P1 = matrix_create(a.rows/2, b.rows/2);
  P2 = matrix_create(a.rows/2, b.rows/2);
  P3 = matrix_create(a.rows/2, b.rows/2);
  P4 = matrix_create(a.rows/2, b.rows/2);
  P5 = matrix_create(a.rows/2, b.rows/2);
  P6 = matrix_create(a.rows/2, b.rows/2);
  P7 = matrix_create(a.rows/2, b.rows/2);

  Q1 = matrix_create(a.rows/2, b.rows/2);
  Q2 = matrix_create(a.rows/2, b.rows/2);
  Q3 = matrix_create(a.rows/2, b.rows/2);
  Q4 = matrix_create(a.rows/2, b.rows/2);

  for(long i = 0; i < N/2; i++)
    for(long j = 0; j < N/2; j++)
    {
      A.items[i][j] = a.items[i][j];
	  B.items[i][j] = a.items[i][j+(N/2)];
	  C.items[i][j] = a.items[i+(N/2)][j];
	  D.items[i][j] = a.items[i+(N/2)][j+(N/2)];

	  E.items[i][j] = b.items[i][j];
	  F.items[i][j] = b.items[i][j+(N/2)];
	  G.items[i][j] = b.items[i+(N/2)][j];
	  H.items[i][j] = b.items[i+(N/2)][j+(N/2)];
    }

  temp1 = matrix_subtract(F , H);
  P1 = matrix_mult(A , temp1);
  
  temp1 = matrix_add(A , B);
  P2 = matrix_mult(temp1 , H);

  temp1 = matrix_add(C , D);
  P3 = matrix_mult(temp1 , E);
    
  temp1 = matrix_subtract(G , E);
  P4 = matrix_mult(D , temp1);

  temp1 = matrix_add(A , D);
  temp2 = matrix_add(E , H);
  P5 = matrix_mult(temp1 , temp2);

  temp1 = matrix_subtract(B , D);
  temp2 = matrix_add(G , H);
  P6 = matrix_mult(temp1 , temp2);

  temp1 = matrix_subtract(A , C);
  temp2 = matrix_add(E , F);
  P7 = matrix_mult(temp1 , temp2);

  temp1 = matrix_add(P5 , P4);
  temp2 = matrix_subtract(temp1 , P2);
  Q1 = matrix_add(temp2 , P6);

  Q2 = matrix_add(P1 , P2);

  Q3 = matrix_add(P3 , P4);

  temp1 = matrix_add(P1 , P5);
  temp2 = matrix_subtract(temp1 , P3);
  Q4 = matrix_add(temp2 , P7);

  for(int i = 0; i < N/2; i++)
    for(int j = 0; j < N/2; j++)
    {
	  result.items[i][j] = Q1.items[i][j];
	  result.items[i][j+(N/2)] = Q2.items[i][j];
	  result.items[i+(N/2)][j] = Q3.items[i][j];
	  result.items[i+(N/2)][j+(N/2)] = Q4.items[i][j];
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
