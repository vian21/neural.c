#include "lib.h"
#include <math.h>

double
sigmoid(double x) {
    return 1 / (1 + exp(-x));
}

double
tanh(double x) {
    return 2 * sigmoid(2 * x) - 1;
}

double
ReLU(double x) {
    return x > 0 ? x : 0;
}

double
L_ReLU(double x) {
    return (x < 0) * (ALPHA * x) + (x >= 0) * x;
}
