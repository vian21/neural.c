#include "debug.h"
#include "matrix.h"
#include "neural.h"

int debug_level = -1;

int
main() {

    LOG_START();

    INFO("Init!");
    Matrix* inputs = matrix_create(1, 2);
    matrix_randomize(inputs);
    matrix_print(inputs);

    Layer* hidden = layer_create(3, inputs->cols);
    matrix_print(hidden->weights);
    matrix_print(hidden->biases);
    matrix_print(hidden->outputs);

    Layer* output = layer_create(2, hidden->n_neurons);
    matrix_print(output->outputs);

    // Clean up
    TRACE("Clean up: Freeing up memory!");
    matrix_free(inputs);
    layer_free(hidden);
    layer_free(output);

    return 0;
}
