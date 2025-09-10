/**
 * [1] Neural networks from scratch:
 * https://developer.ibm.com/articles/neural-networks-from-scratch/
 *
 * [2] CS231n: Deep Learning for Computer Vision: https://cs231n.github.io/
 *
 */
#include <stddef.h>
#include <stdint.h>

#include "debug.h"
#include "idx.h"
#include "lib.h"
#include "matrix.h"
#include "neural.h"

int debug_level = -1;

void
display_img(uint8_t* img) {
    for (int i = 0; i < 28 * 28; i++) {
        if (i != 0 && i % 28 == 0)
            printf("\n");

        printf("%c", img[i] == 0 ? '.' : '#');
    }
    printf("\n");
}

int
main() {
    LOG_START();

    INFO("1. Loading training dataset");
    Matrix** training_img =
        idx_parse("./datasets/MNIST/train-images.idx3-ubyte");
    Matrix** training_labels =
        idx_parse("./datasets/MNIST/train-labels.idx1-ubyte");

    assert(training_img != NULL, "Couldn't parse training images dataset!");
    assert(training_labels != NULL, "Couldn't parse training labels dataset!");

    // Print a few images for testing
    // for (int i = 0; i < 3; i++) {
    //     printf("Label: %d\n", ((uint8_t*)training_labels[0]->data[0])[i]);
    //     display_img(training_img[i]->data[0]);
    // }

    INFO("2. Initializing neural network weights");
    Matrix* input = training_img[0];
    TRACE("Input Matrix shape (%d x %d)", input->rows, input->cols);

    Layer* hidden_1 = layer_create(128, input->rows * input->cols);
    Layer* hidden_2 = layer_create(64, hidden_1->n_neurons);
    Layer* output = layer_create(10, hidden_2->n_neurons);

    Network* network = network_init(3, sigmoid);
    network_append(network, hidden_1);
    network_append(network, hidden_2);
    network_append(network, output);

    INFO("Start training ...");
    TRACE("Running Forward pass");
    forward_pass(network, input);

    TRACE("Calculating cost");
    TRACE("Running Backpropagation");

    matrix_print(output->outputs);

    TRACE("Clean up: Deallocating matrices!");
    for (int i = 0; i < 3; i++) {
        matrix_free(training_img[i]);
    }
    matrix_free(training_labels[0]);

    return 0;
}
