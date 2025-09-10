#include <stddef.h>
#include <stdlib.h>
#include <time.h>

#include "debug.h"
#include "matrix.h"

static int is_seed_set = 0;

void
set_seed() {
    if (!is_seed_set) {
        srand(time(NULL));
        // srand(SEED);
        is_seed_set = 1;
    }
}

Matrix*
matrix_create(int rows, int cols, size_t dtype) {
    Matrix* matrix = (Matrix*)malloc(sizeof(Matrix));
    matrix->rows = rows;
    matrix->cols = cols;
    matrix->dtype = dtype;

    void** data = malloc(rows * sizeof(void**));
    for (int i = 0; i < rows; i++) {
        data[i] = malloc(cols * dtype);
    }
    matrix->data = data;

    return matrix;
}

void
matrix_fill_random(Matrix* matrix) {
    if (!valid_matrix(matrix)) {
        return;
    }

    set_seed();

    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->cols; j++) {
            MATRIX_SET(matrix, i, j, double, (double)rand() / (double)RAND_MAX);
        }
    }
}

void
matrix_print(Matrix* matrix) {
    if (!valid_matrix(matrix)) {
        return;
    }

    TRACE("Shape: %dx%d", matrix->rows, matrix->cols);
    for (int i = 0; i < matrix->rows; i++) {
        printf("[ ");
        for (int j = 0; j < matrix->cols; j++) {
            printf("%.2f ", MATRIX_GET(matrix, i, j, double));
        }
        printf("]\n");
    }
}

int
valid_matrix(Matrix* matrix) {
    if (matrix == NULL) {
        ERROR("Matrix ptr is NULL");
        return 0;
    }
    if (matrix->data == NULL) {
        ERROR("Matrix data is NULL");
        return 0;
    }
    if (matrix->rows <= 0) {
        ERROR("Matrix rows is invalid");
        return 0;
    }
    if (matrix->cols <= 0) {
        ERROR("Matrix cols is invalid");
        return 0;
    }
    return 1;
}

void
matrix_free(Matrix* matrix) {
    if (!valid_matrix(matrix)) {
        return;
    }

    for (int i = 0; i < matrix->rows; i++) {
        free(matrix->data[i]);
    }

    free(matrix->data);
    free(matrix);
}

Matrix*
matrix_clone(Matrix* matrix) {
    if (!valid_matrix(matrix)) {
        ERROR("Cannot clone empty matrix!");
        return NULL;
    }

    Matrix* clone = matrix_create(matrix->rows, matrix->cols, matrix->dtype);
    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->cols; j++) {
            MATRIX_SET(clone, i, j, double, MATRIX_GET(matrix, i, j, double));
        }
    }

    return clone;
}

////////////////////////////
// Matrix Operations
// https://en.wikipedia.org/wiki/Matrix_(mathematics)#Basic_operations
////////////////////////////

void
matrix_add(Matrix* a, Matrix* b, Matrix* out) {
    if (!valid_matrix(a) || !valid_matrix(b) || !valid_matrix(out)) {
        ERROR("Cannot add invalid matrices!");
        return;
    }

    if (a->rows != b->rows || a->cols != b->cols) {
        ERROR("Cannot add shape (%dx%d) with (%dx%d)!",
              a->rows,
              a->cols,
              b->rows,
              b->cols);
        return;
    }

    if (out->rows != a->rows || out->cols != a->cols) {
        ERROR("Output matrix (%dx%d) has to be of shape (%dx%d)!",
              out->rows,
              out->cols,
              a->rows,
              a->cols);
        return;
    }

    for (int i = 0; i < a->rows; i++) {
        for (int j = 0; j < a->cols; j++) {
            MATRIX_SET(out,
                       i,
                       j,
                       double,
                       MATRIX_GET(a, i, j, double) +
                           MATRIX_GET(b, i, j, double));
        }
    }
}

void
matrix_sub(Matrix* a, Matrix* b, Matrix* out) {
    if (!valid_matrix(a) || !valid_matrix(b) || !valid_matrix(out)) {
        ERROR("Cannot subtract invalid matrices!");
        return;
    }

    if (a->rows != b->rows || a->cols != b->cols) {
        ERROR("Cannot subtract shape (%dx%d) with (%dx%d)!",
              a->rows,
              a->cols,
              b->rows,
              b->cols);
        return;
    }

    if (out->rows != a->rows || out->cols != a->cols) {
        ERROR("Output matrix (%dx%d) has to be of shape (%dx%d)!",
              out->rows,
              out->cols,
              a->rows,
              a->cols);
        return;
    }

    for (int i = 0; i < a->rows; i++) {
        for (int j = 0; j < a->cols; j++) {
            MATRIX_SET(out,
                       i,
                       j,
                       double,
                       MATRIX_GET(a, i, j, double) -
                           MATRIX_GET(b, i, j, double));
        }
    }
}

void
matrix_scalar_multiply(double lambda, Matrix* matrix, Matrix* out) {
    if (!valid_matrix(matrix) || !valid_matrix(out)) {
        ERROR("[SCALAR_MUL] Cannot multiply with invalid matrix!");
        return;
    }

    if (out->rows != matrix->rows || out->cols != matrix->cols) {
        ERROR("[SCALAR_MUL] Output matrix (%dx%d) has to be of shape (%dx%d)!",
              out->rows,
              out->cols,
              matrix->rows,
              matrix->cols);
        return;
    }

    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->cols; j++) {
            MATRIX_SET(
                out, i, j, double, MATRIX_GET(matrix, i, j, double) * lambda);
        }
    }
}

void
matrix_multiply(Matrix* a, Matrix* b, Matrix* out) {
    if (!valid_matrix(a) || !valid_matrix(b) || !valid_matrix(out)) {
        ERROR("Cannot multiply invalid matrices!");
        return;
    }

    if (a->cols != b->rows) {
        ERROR("[MULTIPLY] Cannot multiply shape (%dx%d) with (%dx%d)!",
              a->rows,
              a->cols,
              b->rows,
              b->cols);
        return;
    }

    if (out->rows != a->rows || out->cols != b->cols) {
        ERROR("[MULTIPLY] Output matrix (%dx%d) has to be of shape (%dx%d)!",
              out->rows,
              out->cols,
              a->rows,
              b->cols);
        return;
    }

    for (int i = 0; i < a->rows; i++) {
        for (int j = 0; j < b->cols; j++) {
            MATRIX_SET(out, i, j, double, 0);
            for (int k = 0; k < a->cols; k++) {
                MATRIX_SET(out,
                           i,
                           j,
                           double,
                           MATRIX_GET(a, i, k, double) *
                               MATRIX_GET(b, k, j, double));
            }
        }
    }
}

void
matrix_transpose(Matrix* matrix, Matrix* out) {
    if (!valid_matrix(matrix) || !valid_matrix(out)) {
        ERROR("Cannot transpose empty/invalid matrices!");
        return;
    }

    if (out->rows != matrix->cols || out->cols != matrix->rows) {
        ERROR("[TRANSPOSE] Output matrix (%dx%d) has to be of shape (%dx%d)!",
              out->rows,
              out->cols,
              matrix->cols,
              matrix->rows);
        return;
    }

    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->cols; j++) {
            MATRIX_SET(out, j, i, double, MATRIX_GET(matrix, i, j, double));
        }
    }
}
