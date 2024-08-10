#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "math.h"
#include "neural.h"
#include "debug.h"

int
main()
{
    INFO("Init!");
    Matrix *a = matrix_new(2, 4);
    Matrix *aT = matrix_new(4, 2);
    Matrix *b = matrix_new(2, 4);
    Matrix *out = matrix_new(2, 4);

    matrix_randomize(a);
    matrix_randomize(b);

    matrix_print(a);

    matrix_transpose(a, aT);
    matrix_print(aT);
    matrix_scalar_multiply(2.0, aT, aT);
    matrix_print(aT);
    
    matrix_print(b);

    matrix_add(a, b, out);
    matrix_print(out);

    matrix_sub(a, b, out);
    matrix_print(out);

    Matrix *mult_out = matrix_new(2, 2);
    matrix_multiply(a, aT, mult_out);
    matrix_print(mult_out);

    // Clean up
    TRACE("Clean up: Freeing matrices...");
    matrix_free(a);
    matrix_free(aT);
    matrix_free(b);
    matrix_free(out);
    matrix_free(mult_out);

    return 0;
}