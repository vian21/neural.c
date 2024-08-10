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
    Matrix *b = matrix_new(2, 4);
    matrix_randomize(a);
    matrix_randomize(b);
    matrix_print(a);
    matrix_print(b);
    Matrix *out = matrix_new(2, 4);
    matrix_add(a, b, out);
    matrix_print(out);

    // Clean up
    TRACE("Clean up: Freeing matrices...");
    matrix_free(a);
    matrix_free(b);
    matrix_free(out);

    return 0;
}