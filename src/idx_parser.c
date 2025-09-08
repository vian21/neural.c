/**
 * [1] Converting MNIST dataset for Handwritten digit recognition in IDX Format
 * to Python Numpy Array:
 * https://medium.com/the-owl/converting-mnist-data-in-idx-format-to-python-numpy-array-5cb9126f99f1
 *
 * [2] Read MNIST Dataset:
 * https://www.kaggle.com/code/hojjatk/read-mnist-dataset
 *
 */
#include <errno.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "debug.h"
#include "idx.h"
#include "matrix.h"

static uint32_t
read_be32(FILE* file) {
    unsigned char buf[4];
    fread(buf, 1, 4, file);
    return (buf[0] << 24) | (buf[1] << 16) | (buf[2] << 8) | buf[3];
}

Matrix*
idx_parse(char* filepath) {
    FILE* file = fopen(filepath, "rb");
    Matrix* m = NULL;

    assert(file != NULL, "%s - %s", strerror(errno), filepath);

    const uint32_t magic = read_be32(file);
    const uint32_t size = read_be32(file);
    uint32_t img_width = 0, img_height = 0;

    switch (magic) {
    case 2049: // Labels
        INFO("%s - Magic: %u, Size: %u", filepath, magic, size);

        // One row for all labels. Cols will be used for indexing
        m = matrix_create(1, size, sizeof(uint8_t));

        size_t labels_read = fread((m->data)[0], sizeof(uint8_t), size, file);
        assert(labels_read == size,
               "Failed to read labels. Expected: %d Got: %zu",
               size,
               labels_read);
        break;

    case 2051: // Images
        img_width = read_be32(file);
        img_height = read_be32(file);

        INFO("%s - Magic: %u, Size: %u, Rows: %u, Cols: %u",
             filepath,
             magic,
             size,
             img_width,
             img_height);

        // Each row will be an image of size width x height
        m = matrix_create(size, img_width * img_height, sizeof(uint8_t));

        for (uint32_t i = 0; i < size; i++) {
            size_t got = fread((m->data)[i], img_width * img_height, 1, file);
            assert(got == 1, "Failed to read image %u", i);
        }
        break;
    default:
        assert(0, "Invalid magic number: %u", magic);
    }

    fclose(file);
    return m;
}
