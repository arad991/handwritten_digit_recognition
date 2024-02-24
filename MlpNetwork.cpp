#include "MlpNetwork.h"

MlpNetwork::MlpNetwork (Matrix weights[MLP_SIZE], Matrix biases[MLP_SIZE]) :
    layers{Dense (weights[L1], biases[L1], activation::relu),
           Dense (weights[L2], biases[L2], activation::relu),
           Dense (weights[L3], biases[L3], activation::relu),
           Dense (weights[L4], biases[L4], activation::softmax)}
{}

digit MlpNetwork::operator() (const Matrix &input) const
{
  Matrix result_mat (input);
  result_mat.vectorize ();
  for (const auto &layer: layers)
  {
    result_mat = layer (result_mat); //apply the layer to the result
  }
  return {(unsigned int) result_mat.argmax (),
          result_mat[result_mat.argmax ()]};
}