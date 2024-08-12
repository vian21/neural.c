#ifndef NEURAL_H
#define NEURAL_H

#include "matrix.h"
typedef struct Layer{
    int n_neurons;
    Matrix *weights;
    Matrix *biases;
    Matrix *outputs;
} Layer;

/*
 * Initialize a MLP layer.

 * Output of layer = n_neurons
 * Biases = n_neurals
 * Weigths[input][n_neuron]
 */
Layer *layer_create(int n_neurons, int n_inputs);
void feed_forward(Layer *layer, Matrix *inputs);
int valid_layer(Layer *layer);
void layer_free(Layer *layer);

#endif