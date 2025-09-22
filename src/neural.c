#include <stdlib.h>

#include "debug.h"
#include "matrix.h"
#include "neural.h"

int valid_layer(Layer* layer);
void layer_free(Layer* layer);

///////////////////////
/// Layer ops
///////////////////////
Layer*
layer_create(int n_neurons, int n_inputs) {
    // Ref: https://cs231n.github.io/neural-networks-1/
    Layer* layer = (Layer*)malloc(sizeof(Layer));

    layer->n_neurons = n_neurons;
    layer->n_inputs = n_inputs;
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

Network*
network_init(int n_layers, double (*activation_function)(double)) {
    assert(activation_function, "Invalid activation function!");
    assert(n_layers > 0, "Invalid network depth");

    Network* net = malloc(sizeof(Network));

    net->depth = n_layers;
    net->capacity = 0;

    net->layers = malloc(n_layers * sizeof(Layer*));
    net->act_func = activation_function;

    return net;
}

int
network_append(Network* net, Layer* layer) {
    if (!net || !layer)
        return 0;

    if (net->capacity == net->depth) {
        ERROR("Network already at maximum capacity!");
        return 0;
    }

    net->layers[net->capacity] = layer;
    net->capacity++;

    return 1;
}

void
forward_pass(Network* net, Matrix* input) {
    Layer *curr_layer, *prev_layer = NULL;
    assert(net);
    assert(input);

    // First layer pass
    curr_layer = net->layers[0];
    Matrix* tmp =
        matrix_create(input->rows, curr_layer->weights->cols, sizeof(double));

    TRACE("Multiplying input layer x layer[0]");
    matrix_multiply(input, curr_layer->weights, tmp);
    matrix_add(tmp, curr_layer->biases, curr_layer->outputs);
    matrix_free(tmp);

    for (int i = 1; i < net->capacity; i++) {
        prev_layer = net->layers[i - 1];
        curr_layer = net->layers[i];

        assert(prev_layer);
        assert(curr_layer);

        Matrix* tmp = matrix_create(prev_layer->outputs->rows,
                                    curr_layer->weights->cols,
                                    sizeof(double));

        TRACE("Multiplying layer[%d] x layer[%d]", i - 1, i);
        matrix_multiply(prev_layer->outputs, curr_layer->weights, tmp);
        matrix_add(tmp, curr_layer->biases, curr_layer->outputs);

        matrix_free(tmp);
    }
}
