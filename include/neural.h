#ifndef NEURAL_H
#define NEURAL_H
#include "matrix.h"

typedef struct Layer {
    int n_neurons;
    int n_inputs;

    Matrix* weights;
    Matrix* biases;
    Matrix* outputs;
} Layer;

typedef struct Network {
    int depth;
    int capacity;

    Layer** layers;
    double (*act_func)(double);
} Network;

/*
 * Initialize a MLP layer.

 * Output of layer = n_neurons
 * Biases = n_neurons
 * Weigths = input x n_neurons
 */
Layer* layer_create(int n_neurons, int n_inputs);

/*
 * Initialize Feed forward Network
 *
 * n_layers = # hidden layers + output_layer.
 * NOTE: Does not include input layer
 */
Network* network_init(int n_layers, double (*activation_function)(double));

/* Append layer to network
 *
 * Returns 0: error | 1: success
 */
int network_append(Network* net, Layer* layer);

/* Run forward pass on all layers with input*/
void forward_pass(Network* net, Matrix* input);
#endif
