// Activation.h
#ifndef ACTIVATION_H
#define ACTIVATION_H

#include "Matrix.h"

// Insert Activation namespace here...
typedef Matrix (*ActivationFunction) (const Matrix &);

namespace activation
{
  /**
   * Applies the ReLU activation function on the given matrix.
   * @param mat - the matrix to apply the function on.
   * @return the matrix after applying the function.
   */
  Matrix relu (const Matrix &mat);

  /**
   * Applies the Softmax activation function on the given matrix.
   * @param mat - the matrix to apply the function on.
   * @return the matrix after applying the function.
   */
  Matrix softmax (const Matrix &mat);
}










#endif //ACTIVATION_H