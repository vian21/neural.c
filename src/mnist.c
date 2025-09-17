/**
 * [1] Neural networks from scratch:
 * https://developer.ibm.com/articles/neural-networks-from-scratch/
 *
 * [2] CS231n: Deep Learning for Computer Vision: https://cs231n.github.io/
 *
 */
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "debug.h"
#include "idx.h"
#include "lib.h"
#include "matrix.h"
#include "neural.h"

int debug_level = -1;

typedef enum { TRAINING, INFERENCE } Mode;

typedef struct {
    Mode mode;
    int n_samples;
    char* checkpoint;
} CLIOptions;

void
print_usage() {
    printf("mnist - Hand written digit classifier\n");
    printf("Usage: mnist -c [CHECKPOINT] -i | -t\n");
    printf("-h                       - Display this message\n");
    printf("-t checkpoint_filepath   - Train neural network and save "
           "progress "
           "to checkpoint\n");
    printf("-i n_samples             - Run in inference mode. -c has to be "
           "added\n");
    printf("-c checkpoint_file       - Checkpoint file to load\n");
}

CLIOptions
parse_args(int argc, char** argv) {
    if (argc < 2) {
        print_usage();
        exit(EXIT_FAILURE);
    }

    CLIOptions opts = {.checkpoint = NULL};

    for (int i = 1; i < argc; i++) {
        if (strncmp(argv[i], "-h", 2) == 0) {
            print_usage();
            exit(EXIT_SUCCESS);
        }

        if (strncmp(argv[i], "-i", 2) == 0) {
            if (argc > i + 1) {
                ERROR("n_samples not provided!");
                exit(EXIT_FAILURE);
            }

            int n_samples = atoi(argv[++i]);
            if (n_samples != 0) {
                ERROR("Invalid n_samples values provided!");
                exit(EXIT_FAILURE);
            }

            opts.mode = INFERENCE;
            opts.n_samples = n_samples;
        }

        if (strncmp(argv[i], "-t", 2) == 0) {
            if (argc > i + 1) {
                ERROR("Filepath not provided!");
                exit(EXIT_FAILURE);
            }

            opts.mode = TRAINING;
            opts.checkpoint = argv[++i];
        }

        if (strncmp(argv[i], "-c", 2) == 0) {
            if (argc > i + 1) {
                ERROR("Checkpoint filepath not provided!");
                exit(EXIT_FAILURE);
            }

            opts.checkpoint = argv[++i];
        }
    }

    assert(opts.checkpoint != NULL,
           "Checkpoint filename has to be provided for both inference and "
           "training mode!");

    return opts;
}

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
main(int argc, char** argv) {
    LOG_START();

    CLIOptions opts = parse_args(argc, argv);

    if (opts.mode == INFERENCE) {
        // 1. Load checkpoint
        // 2. Load test dataset
        INFO("1. Loading testing dataset");
        Matrix** test_images =
            idx_parse("./datasets/MNIST/t10k-images.idx3-ubyte");
        Matrix** test_labels =
            idx_parse("./datasets/MNIST/t10k-labels.idx1-ubyte");

        assert(test_images != NULL, "Couldn't parse test images dataset!");
        assert(test_labels != NULL, "Couldn't parse test labels dataset!");

        uint8_t* input_labels = test_labels[0]->data[0];
        for (int i = 0; i < opts.n_samples; i++) {
            Matrix* input = test_images[i];
            TRACE("Input Matrix shape (%d x %d)", input->rows, input->cols);

            display_img(input->data[0]);
            printf("Label: %d\n", input_labels[i]);
        }

        TRACE("Clean up: Deallocating matrices!");
        for (int i = 0; i < 3; i++) {
            matrix_free(test_images[i]);
        }

        matrix_free(test_labels[0]);

        free(test_images);
        free(test_labels);

        return EXIT_SUCCESS;
    }

    // opts.mode == TRAINING
    INFO("1. Loading training dataset");
    Matrix** training_images =
        idx_parse("./datasets/MNIST/train-images.idx3-ubyte");
    Matrix** training_labels =
        idx_parse("./datasets/MNIST/train-labels.idx1-ubyte");

    assert(training_images != NULL, "Couldn't parse training images dataset!");
    assert(training_labels != NULL, "Couldn't parse training labels dataset!");

    INFO("2. Initializing neural network weights");
    Matrix* input = training_images[0];
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
        matrix_free(training_images[i]);
    }

    matrix_free(training_labels[0]);

    free(training_images);
    free(training_labels);

    return EXIT_SUCCESS;
}
