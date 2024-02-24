#include "Dense.h"


Dense::Dense (const Matrix &weights, const Matrix &bias, ActivationFunction func)
{
  this->weights = weights;
  this->bias = bias;
  this->activation_func = func;
}

Matrix Dense::get_weights () const
{
  return this->weights;
}

Matrix Dense::get_bias () const
{
  return this->bias;
}

ActivationFunction Dense::get_activation () const
{
  return this->activation_func;
}

Matrix Dense::operator() (const Matrix &input) const
{
  return this->activation_func (this->weights * input + this->bias);
}