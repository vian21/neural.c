#include <stddef.h>
#include <stdint.h>

#include "debug.h"
#include "idx.h"
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

    INFO("Loading training dataset");
    Matrix* training_img =
        idx_parse("./datasets/MNIST/train-images.idx3-ubyte");
    Matrix* training_labels =
        idx_parse("./datasets/MNIST/train-labels.idx1-ubyte");

    assert(training_img != NULL, "Couldn't parse training images dataset!");
    assert(training_labels != NULL, "Couldn't parse training labels dataset!");

    for (int i = 0; i < 3; i++) {
        printf("Label: %d\n", ((uint8_t*)training_labels->data[0])[i]);
        display_img(training_img->data[i]);
    }

    matrix_free(training_img);
    matrix_free(training_labels);

    return 0;
}
