#ifndef MATH_H
#define MATH_H

#define ALPHA 0.01

/*
 * Calculate sigmoid of x
 *
 * Squashes real values to [0,1]
 *
 * Downsides:
 * 1. Sigmoids saturate and kill gradients
 * 2. Sigmoid outputs are not zero-centered. This has implications on the
dynamics during gradient descent, because if the data coming into a neuron is
always positive (e.g. x>0 elementwise in f=wTx+b)), then the gradient on the
weights w will during backpropagation become either all be positive, or all
negative
 *
 */
double sigmoid(double x);

/*
 * tanh
 *
 * tanh(x)=2σ(2x)−1
 *
 * squashes real numbers to range between [-1,1] and is zero centered unlike
 * sigmoid
 */
double tanh(double x);

/*
 * Rectified Linear Unit
 * Pros:
 * 1. greatly accelerate (e.g. a factor of 6 in Krizhevsky et al.) the
 * convergence of stochastic gradient descent
 * 2. faster since it does not use exponentials
 * Cons:
 * 1. ReLU units can be fragile during training and can “die”. For example, a
 * large gradient flowing through a ReLU neuron could cause the weights to
 * update in such a way that the neuron will never activate on any datapoint
 * again.
 *
 */
double ReLU(double x);

/*
 * Leaky ReLu
 *
 * f(x)=𝟙(x<0)(αx)+𝟙(x>=0)(x) where α is a small constant.
 */
double L_ReLU(double x);

#endif
