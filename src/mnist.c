#include <stddef.h>

#include "idx_parser.c"
#include "debug.h"
#include "matrix.h"
#include "neural.h"

int debug_level = -1;

int
main() {

    LOG_START();

    INFO("Loading training dataset");
    Matrix* training_img =
        idx_parse("../datasets/MNIST/train-images.idx3-ubyte");
    Matrix* training_labels =
        idx_parse("../datasets/MNIST/train-labels.idx1-ubyte");

    assert(training_img != NULL, "Couldn't parse training images dataset!");
    assert(training_labels != NULL, "Couldn't parse training images dataset!");

    return 0;
}
