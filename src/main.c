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
    Matrix *inputs = matrix_create(1, 2);
    matrix_randomize(inputs);
    matrix_print(inputs);

    Layer *hidden = layer_create(3, inputs->cols);
    matrix_print(hidden->weights);
    matrix_print(hidden->biases);
    matrix_print(hidden->outputs);

    Layer *output = layer_create(2, hidden->n_neurons);
    matrix_print(output->outputs);

    // Clean up
    TRACE("Clean up: Freeing up memory!");
    matrix_free(inputs);
    layer_free(hidden);
    layer_free(output);

    return 0;
}