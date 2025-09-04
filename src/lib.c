#include "lib.h"
#include <math.h>

double
sigmoid(double x) {
    return 1 / (1 + exp(-x));
}

double
ReLU(double x) {
    return x > 0 ? x : 0;
}
