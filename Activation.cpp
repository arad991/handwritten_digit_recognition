//
// Created by Arad on 2/23/2024.
//
#include "Activation.h"

using namespace activation;
Matrix activation::relu (const Matrix &mat)
{
  int matrix_size = mat.get_rows () * mat.get_cols ();
  Matrix result_mat (mat.get_rows (), mat.get_cols ());
  for (int i = 0; i < matrix_size; ++i)
  {
    if (mat[i] >= 0)
    {
      result_mat[i] = mat[i];
    }
  }
  return result_mat;
}


Matrix activation:: softmax (const Matrix &mat)
{
  int matrix_size = mat.get_rows () * mat.get_cols ();
  Matrix result_mat (mat.get_rows (), mat.get_cols ());
  float value = 0;
  for (int i = 0; i < matrix_size; ++i)
  {
    result_mat[i] = std::exp (mat[i]);
    value += result_mat[i];
  }
  result_mat = result_mat * (1 / (value));
  return result_mat;
}