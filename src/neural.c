#include <stdlib.h>

#include "debug.h"
#include "neural.h"

///////////////////////
/// Layer ops
///////////////////////
Layer*
layer_create(int n_neurons, int n_inputs) {
    Layer* layer = (Layer*)malloc(sizeof(Layer));

    layer->n_neurons = n_neurons;
    layer->weights = matrix_create(n_inputs, n_neurons, sizeof(double));
    layer->biases = matrix_create(1, n_neurons, sizeof(double));
    layer->outputs = matrix_create(1, n_neurons, sizeof(double));

    matrix_fill_random(layer->weights);
    matrix_fill_random(layer->biases);

    return layer;
}

int
valid_layer(Layer* layer) {
    if (!valid_matrix(layer->weights) || !valid_matrix(layer->biases) ||
        !valid_matrix(layer->outputs)) {
        ERROR("Invalid layer attributes!");
        return 0;
    }
    return 1;
}

void
layer_free(Layer* layer) {
    if (!valid_layer(layer)) {
        ERROR("Cannot free invalid layer ptr!");
        return;
    }

    free(layer->biases);
    free(layer->weights);
    free(layer->outputs);

    free(layer);
}

void
feed_forward(Layer* layer, Matrix* inputs) {
    assert(valid_layer(layer));
    assert(valid_matrix(inputs));
}
