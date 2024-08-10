#include <stdlib.h>
// #include <time.h>
#include <assert.h>
#include "matrix.h"
#include "debug.h"

Matrix *
matrix_new(int rows, int cols){
    Matrix *matrix = (Matrix*) malloc(sizeof(Matrix));
    matrix->rows = rows;
    matrix->cols = cols;
    double **data =  (double **)malloc(rows * sizeof(double **));
    for(int i = 0; i < rows; i++){
        data[i] = (double *)malloc(cols * sizeof(double));
    }
    matrix->data = data;

    return matrix;
}

void
matrix_randomize(Matrix *matrix){
    if(!valid_matrix(matrix)){
        return;
    }
    // srand(time(NULL));
    srand(SEED);
    for(int i = 0; i < matrix->rows; i++){
        for(int j = 0; j < matrix->cols; j++){
            matrix->data[i][j] = (double)rand() / (double)RAND_MAX;
        }
    }
}

void
matrix_print(Matrix *matrix){
    if(!valid_matrix(matrix)){
        return;
    }
    TRACE("Shape: %dx%d", matrix->rows, matrix->cols);
    for(int i = 0; i < matrix->rows; i++){
        printf("[ ");
        for(int j = 0; j < matrix->cols; j++){
            printf("%.2f ", matrix->data[i][j]);
        }
        printf("]\n");
    }
}

int
valid_matrix(Matrix *matrix){
    if (matrix == NULL){
        ERROR("Matrix ptr is NULL");
        return 0;
    }
    if (matrix->data == NULL){
        ERROR("Matrix data is NULL");
        return 0;
    }
    if (matrix->rows <= 0){
        ERROR("Matrix rows is invalid");
        return 0;
    }
    if (matrix->cols <= 0){
        ERROR("Matrix cols is invalid");
        return 0;
    }
    return 1;
}

void
matrix_free(Matrix *matrix){
    if(!valid_matrix(matrix)){
        return;
    }
    for(int i = 0; i < matrix->rows; i++){
        free(matrix->data[i]);
    }
    free(matrix->data);
    free(matrix);
}

// https://en.wikipedia.org/wiki/Matrix_addition
void
matrix_add(Matrix *a, Matrix *b, Matrix *out){
    if(!valid_matrix(a) || !valid_matrix(b) || !valid_matrix(out)){
        ERROR("Cannot add invalid matrices!");
        return;
    }
    if(a->rows != b->rows || a->cols != b->cols){
        ERROR("Cannot add shape (%dx%d) with (%dx%d)!", a->rows, a->cols, b->rows, b->cols);
        return;
    }
    if(out->rows != a->rows || out->cols != a->cols){
        ERROR("Output matrix (%dx%d) has to be of shape (%dx%d)!", out->rows, out->cols,
        a->rows, a->cols);
        return;
    }
    for(int i = 0; i < a->rows; i++){
        for(int j = 0; j < a->cols; j++){
            out->data[i][j] = a->data[i][j] + b->data[i][j];
        }
    }
}