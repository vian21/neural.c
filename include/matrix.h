#ifndef MATRIX_H
#define MATRIX_H

#define SEED 0xDEADBEEF
typedef struct Matrix{
    int rows;
    int cols;
    double **data;
} Matrix;

/* Create a Zeroed matrix with shape (rowsxcols) */
Matrix *matrix_new(int rows, int cols);

/* Fill matrix with random values */
void matrix_randomize(Matrix *matrix);

/* Free matrix memory */
void matrix_free(Matrix *matrix);

/*
 * Checks is matrix pointer, rows, cols and data pointer are valid, 
 * @returns 1 if matrix is valid, 0 otherwise
 */
int valid_matrix(Matrix *matrix);

/* Print matrix to stdout */
void matrix_print(Matrix *matrix);

void matrix_add(Matrix *a, Matrix *b, Matrix *out);
void matrix_sub(Matrix *a, Matrix *b, Matrix *out);
void matrix_scalar_multiply(double lambda, Matrix *matrix, Matrix *out);
void matrix_multiply(Matrix *a, Matrix *b, Matrix *out);
void matrix_transpose(Matrix *matrix, Matrix *out);

#endif