#ifndef DENSE_H
#define DENSE_H

#include "Activation.h"
#include "Matrix.h"

// Insert Dense class here...

class Dense
{
 private:
  Matrix weights;
  Matrix bias;
  ActivationFunction activation_func;

 public:
  /**
   * Dense constructor
   * @param weights matrix
   * @param bias matrix
   * @param func activation function
   */
  Dense (const Matrix &weights, const Matrix &bias, ActivationFunction func);

  // getters
  /**
   * Returns the weights matrix
   * @return weights matrix
   */
  Matrix get_weights () const;
    /**
     * Returns the bias matrix
     * @return bias matrix
     */
  Matrix get_bias () const;
    /**
     * Returns the activation function
     * @return activation function
     */
  ActivationFunction get_activation () const;

  // operators
  /**
   * Applies the layer on the input and returns an output matrix
   * @param input matrix to operate
   * @return new matrix
   */
  Matrix operator() (const Matrix &input) const;
};
#endif //DENSE_H