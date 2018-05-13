#ifndef MATRIX_H
#define MATRIX_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

// types
struct Matrix {
  long rows; // lines
  long cols; // columns
  double** items;
};

typedef struct Matrix Matrix_t;

// prototypes
Matrix_t matrix_load_from_file(FILE *file);
Matrix_t matrix_create(long rows, long cols);
Matrix_t matrix_transpose(Matrix_t a);
void matrix_set(Matrix_t a, long row, long col, double value);
Matrix_t matrix_mult(Matrix_t a, Matrix_t b);
Matrix_t matrix_mult_t(Matrix_t a, Matrix_t b);
bool matrix_mult_valid(Matrix_t a, Matrix_t b);
void matrix_print(Matrix_t a);
void matrix_print_to_file(FILE *output, Matrix_t a);
Matrix_t matrix_add(Matrix_t a, Matrix_t b);
Matrix_t matrix_subtract(Matrix_t a, Matrix_t b);
Matrix_t strassen(Matrix_t a, Matrix_t b);

#endif
