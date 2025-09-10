#ifndef IDX_H
#define IDX_H

#include "matrix.h"

/*
 * Returns an array of Matrices where each matrix->data[0] is a (1 x 784)
 * uint8_t image.
 *
 * For labels, it will have only one matrix with all the labels
 * as uint8_t
 */
Matrix** idx_parse(char* filepath);

#endif
