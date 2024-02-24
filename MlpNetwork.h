// MlpNetwork.h
#ifndef MLPNETWORK_H
#define MLPNETWORK_H

#include "Dense.h"

#define MLP_SIZE 4

/**
 * @struct digit
 * @brief Identified (by Mlp network) digit with
 *        the associated probability.
 * @var value - Identified digit value
 * @var probability - identification probability
 */
typedef struct digit {
	unsigned int value;
	float probability;
} digit;

const matrix_dims img_dims = {28, 28};
const matrix_dims weights_dims[] = {{128, 784},
									{64,  128},
									{20,  64},
									{10,  20}};
const matrix_dims bias_dims[] = {{128, 1},
								 {64,  1},
								 {20,  1},
								 {10,  1}};

// Insert MlpNetwork class here...

class MlpNetwork
{
 private:
  Dense layers[MLP_SIZE]; // array of 4 Dense types layers


  // to map each layer to its corresponding information
  enum Layers
  {
      L1, L2, L3, L4
  };

 public:
  /**
   * MlpNetwork constructor
   * @param weights array of matrix, weights[i] is the
   *                                        i'th layer weights matrix
   * @param biases array of matrix, biases[i] is the i'th layer bias matrix
   *          (which is actually a vector)
   */
  MlpNetwork (Matrix weights[],Matrix biases[]);
   /**
   * Applies the entire network on input.
   * Returns a digit struct type.
   * @param input matrix to apply the network
   * @return struct digit (value, probability)
   */
  digit operator() (const Matrix &input) const;

};

#endif // MLPNETWORK_H