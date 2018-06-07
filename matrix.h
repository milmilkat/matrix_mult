#ifndef MATRIX_H
#define MATRIX_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

// types
struct Matrix {
  size_t rows; // lines
  size_t cols; // columns
  double** items;
};

typedef struct Matrix Matrix_t;

// prototypes
Matrix_t matrix_load_from_file(FILE *file);
Matrix_t matrix_create(size_t rows, size_t cols);
Matrix_t matrix_transpose(Matrix_t a);
void matrix_set(Matrix_t a, size_t row, size_t col, double value);
Matrix_t matrix_mult(Matrix_t a, Matrix_t b);
Matrix_t matrix_mult_t(Matrix_t a, Matrix_t b);
bool matrix_mult_valid(Matrix_t a, Matrix_t b);
void matrix_print(Matrix_t a);
void matrix_print_to_file(FILE *output, Matrix_t a);
Matrix_t matrix_mult_openmp();
size_t* non_sparsing_matrix(Matrix_t a);
size_t size_of_non_sparsed(size_t *sp, size_t rows);
#endif
