#ifndef CHECKPOINTS_H
#define CHECKPOINTS_H

#include "neural.h"
static const int CHECKPOINT_SIGNATURE = 0x420;

/*
 * Save neural network state to file
 *
 * ## Format
 *
 * 4 bytes - signature
 *
 * 4 bytes - network depth (number of layers)
 *
 * Layer Blocks. Each matrix is flattened
 *   - int n_neurons;
 *   - int n_inputs;
 *   - uint8_t dtype;
 *   - weights[n_inputs x n_neurons]
 *   - biases[n_neurons]
 *   - outputs[n_neurons]
 *
 * Return
 *
 *  0: success
 * -1: error
 */
int checkpoint_save(Network* net, const char* filepath);

/*
 * Load neural network from checkpoint file.
 *
 */
Network* checkpoint_load(const char* filepath);

#endif // !CHECKPOINTS_H
