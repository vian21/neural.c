#include <stdint.h>
#include <stdio.h>

#include "checkpoints.h"
#include "debug.h"
#include "matrix.h"

static void
matrix_dump(FILE* file, Matrix* matrix) {
    assert(file);
    assert(matrix);

    for (int i = 0; i < matrix->rows; i++) {
        fwrite(matrix->data[i], matrix->dtype, matrix->cols, file);
    }
}

int
checkpoint_save(Network* net, const char* filepath) {
    INFO("Saving network checkpoint to %s", filepath);
    assert(net);
    assert(filepath);

    FILE* file = fopen(filepath, "w");
    // 4 bytes - signature
    fwrite(&CHECKPOINT_SIGNATURE, sizeof(int), 1, file);

    // 4 bytes - network depth (number of layers)
    fwrite(&net->capacity, sizeof(int), 1, file);

    /*
     * Layer Blocks. Each matrix is flattened
     *   - int n_neurons;
     *   - int n_inputs;
     *   - uint8_t dtype;
     *   - weights[n_inputs x n_neurons]
     *   - biases[n_neurons]
     *   - outputs[n_neurons]
     */
    for (int i = 0; i < net->capacity; i++) {
        Layer* layer = net->layers[i];
        fwrite(&layer->n_neurons, sizeof(int), 1, file);
        fwrite(&layer->n_inputs, sizeof(int), 1, file);
        fwrite(&layer->weights->dtype, sizeof(uint8_t), 1, file);

        matrix_dump(file, layer->weights);
        matrix_dump(file, layer->biases);
        matrix_dump(file, layer->outputs);
    }
    return 0;
}

Network*
checkpoint_load(const char* filepath) {
    assert(filepath);
    return NULL;
}
