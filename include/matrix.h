#ifndef MATRIX_H
#define MATRIX_H

#include <stddef.h>

#define SEED 0xDEADBEEF
typedef struct Matrix {
    int rows;
    int cols;
    size_t dtype;
    void** data;
} Matrix;

#define MATRIX_GET(matrix, i, j, type) (((type**)matrix->data)[i][j])
#define MATRIX_SET(matrix, i, j, type, value)                                  \
    (((type**)matrix->data)[i][j] = value)

/* Create a Zeroed matrix with shape (rowsxcols) */
Matrix* matrix_create(int rows, int cols, size_t dtype);

/* Fill matrix with random values */
void matrix_fill_random(Matrix* matrix);

/* Free matrix memory i.e struct + data */
void matrix_free(Matrix* matrix);

/*
 * Checks is matrix pointer, rows, cols and data pointer are valid,
 * @returns 1 if matrix is valid, 0 otherwise
 */
int valid_matrix(Matrix* matrix);

/* Print matrix to stdout */
void matrix_print(Matrix* matrix);

void matrix_add(Matrix* a, Matrix* b, Matrix* out);
void matrix_sub(Matrix* a, Matrix* b, Matrix* out);
void matrix_scalar_multiply(double lambda, Matrix* matrix, Matrix* out);
void matrix_multiply(Matrix* a, Matrix* b, Matrix* out);
void matrix_transpose(Matrix* matrix, Matrix* out);

#endif
