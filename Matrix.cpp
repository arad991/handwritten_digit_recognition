#include "Matrix.h"

#define MIN_VALUE 0.1

// main constructor
Matrix::Matrix (int rows, int cols)
{
  if (rows <= 0 || cols <= 0)
  {
    throw std::exception (); // throw exception
  }
  this->rows = rows;
  this->cols = cols;
  data = new float *[rows]; // Allocate memory for the 2D array
  for (int i = 0; i < rows; ++i)
  {
    data[i] = new float[cols];
    for (int j = 0; j < cols; ++j)
    {
      data[i][j] = 0; // Initialize all elements to 0
    }
  }
}

// default constructor
Matrix::Matrix ():Matrix (1, 1)
{}

// copy constructor
Matrix::Matrix (const Matrix &m): Matrix (m.rows, m.cols)
{
for (int i = 0; i < rows; ++i)
  {
    for (int j = 0; j < cols; ++j)
    {
      data[i][j] = m.data[i][j];
    }
  }
}
// frees this->data's memory
void Matrix::delete_data () const
{
  for (int i = 0; i < rows; i++)
  {
    delete[] this->data[i];
  }
  delete[] this->data;
}

// destructor
Matrix::~ Matrix ()
{
  this->delete_data ();
}

// getters
int Matrix::get_rows () const
{ return this->rows; }

int Matrix::get_cols () const
{ return this->cols; }

//functions

Matrix &Matrix::transpose ()
{
  // creating a new matrix with the transposed dimensions
  Matrix tmp (this->cols, this->rows);
  for (int i = 0; i < this->rows; i++)
  {
    for (int j = 0; j < this->cols; j++)
    {
      // transposing the data
      tmp.data[j][i] = this->data[i][j];
    }
  }
  *this = tmp;
  return *this;
}

Matrix &Matrix::vectorize ()
{
  Matrix tmp (this->rows * this->cols, 1);
  int index = 0; // index for cells in the new matrix
  for (int i = 0; i < rows; ++i)
  {
    for (int j = 0; j < cols; ++j)
    {
      tmp.data[index][0] = this->data[i][j];
      index++; // incrementing the index when a cell is filled
    }
  }
  *this = tmp;
  return *this;
}

void Matrix::plain_print() const
{
  for (int i = 0; i < this->rows; ++i)
  {
    for (int j = 0; j < this->cols; ++j)
    {
      std::cout << this->data[i][j] << " ";
    }
    std::cout << std::endl;
  }
}

Matrix Matrix::dot (const Matrix &other) const
{
  Matrix tmp (rows, cols);
  for (int i = 0; i < rows; ++i)
  {
    for (int j = 0; j < cols; ++j)
    {
      tmp.data[i][j] = this->data[i][j] * other.data[i][j];
    }
  }
  return tmp;
}

float Matrix::norm () const
{
  float result = 0;
  for (int i = 0; i < rows; ++i)
  {
    for (int j = 0; j < cols; ++j)
    {
      result += this->data[i][j] * this->data[i][j];
    }
  }
  return std::sqrt (result);
}

Matrix Matrix::rref () const
{
  Matrix new_matrix (*this);
  int leader_element = 0;
  for (int r = 0; r < new_matrix.rows; ++r)
  {
    if (new_matrix.cols <= leader_element)
    { break; }
    int i = r;
    while (new_matrix.data[i][leader_element] == 0)
    {
      i++;
      if (new_matrix.rows == i)
      {
        i = r;
        leader_element++;
        if (new_matrix.cols == leader_element)
        { break; }
      }
    }
    if (r != i)
    {
      for (int j = 0; j < new_matrix.cols; ++j)
      {
        float temp = new_matrix.data[r][j];
        new_matrix.data[r][j] = new_matrix.data[i][j];
        new_matrix.data[i][j] = temp;
      }
    }
    float div = new_matrix.data[r][leader_element];
    if (div != 0)
    {
      for (int j = 0; j < new_matrix.cols; ++j)
      { new_matrix.data[r][j] /= div; }
    }
    for (int k = 0; k < new_matrix.rows; ++k)
    {
      if (k != r)
      {
        float mult = new_matrix.data[k][leader_element];
        for (int j = 0; j < new_matrix.cols; ++j)
        { new_matrix.data[k][j] -= new_matrix.data[r][j] * mult; }
      }
    }
    leader_element++;
  }
  return new_matrix;
}

int Matrix::argmax () const
{
  float max = data[0][0];
  int max_index = 0, counter = 0;
  for (int i = 0; i < rows; ++i)
  {
    for (int j = 0; j < cols; ++j)
    {
      if (max < this->data[i][j])
      {
        max = this->data[i][j];
        max_index = counter;
      }
      counter++;
    }
  }
  return max_index;
}

float Matrix::sum () const
{
  float sum = 0;
  for (int i = 0; i < rows; ++i)
  {
    for (int j = 0; j < cols; ++j)
    {
      sum += this->data[i][j];
    }
  }
  return sum;
}

Matrix &Matrix::operator+= (const Matrix &other)
{
  if (rows != other.rows || cols != other.cols)
  { throw std::exception(); } // throw exception
  for (int i = 0; i < rows; ++i)
  {
    for (int j = 0; j < cols; ++j)
    {
      this->data[i][j] += other.data[i][j];
    }
  }
  return *this;
}

Matrix Matrix::operator+ (const Matrix &other) const
{
  if (rows != other.rows || cols != other.cols)
  { throw std::exception(); } // throw exception
  Matrix result_mat (rows, cols);
  for (int i = 0; i < rows; ++i)
  {
    for (int j = 0; j < cols; ++j)
    {
      result_mat.data[i][j] = this->data[i][j] + other.data[i][j];
    }
  }
  return result_mat;
}

Matrix &Matrix::operator= (const Matrix &other)
{
  {
    if (this == &other)
    { return *this; }
    this->delete_data (); // frees this->data memory
    this->rows = other.rows;
    this->cols = other.cols;
    this->data = new float *[this->rows];
    for (int i = 0; i < this->rows; ++i)
    {
      this->data[i] = new float[this->cols];
      for (int j = 0; j < this->cols; ++j)
      {
        this->data[i][j] = other.data[i][j];
      }
    }
    return *this;
  }
}

// scalar mult on the right
Matrix Matrix::operator* (float c) const
{
  Matrix result_mat (rows, cols);
  for (int i = 0; i < rows; ++i)
  {
    for (int j = 0; j < cols; ++j)
    {
      result_mat.data[i][j] = c * this->data[i][j];
    }
  }
  return result_mat;
}

//scalar mult on the left
Matrix operator* (float c, const Matrix &matrix)
{
  return matrix * c;
}

// matrix multiplication
Matrix Matrix::operator* (const Matrix &other) const
{
  if (cols != other.rows)
  { throw std::exception(); } // throw exception
  Matrix result_mat (rows, other.cols);
  for (int i = 0; i < result_mat.rows; ++i)
  {
    for (int j = 0; j < result_mat.cols; ++j)
    {
      for (int k = 0; k < cols; ++k)
      {
        result_mat.data[i][j] += this->data[i][k] * other.data[k][j];
      }
    }
  }
  return result_mat;
}

float &Matrix::operator() (int row, int col) const
{
  if (row < 0 || row >= rows || col < 0 || col >= cols)
  { throw std::exception(); } // throw exception
  return this->data[row][col];
}


float &Matrix::operator[] (int index) const
{
  if (index < 0 || index >= rows * cols)
  { throw std::exception(); } // throw exception
  return this->data[index / cols][index % cols];
}

std::ostream &operator<< (std::ostream &ostream, const Matrix &matrix)
{
  for (int i = 0; i < matrix.rows; ++i)
  {
    for (int j = 0; j < matrix.cols; ++j)
    {
      if (matrix (i, j) > MIN_VALUE)
      { ostream << "**"; }
      else
      { ostream << "  "; }
    }
    ostream << std::endl;
  }
  return ostream;
}

std::istream &operator>> (std::istream &istream, Matrix &matrix)
{
  long elem_size = sizeof (matrix.data[0][0]); // ~sizeof(float)
  long current_cursor = istream.gcount (); // if not starting from 0
  istream.seekg (0, std::istream::end);
  long length = istream.tellg () - current_cursor; // file length
  if (length < matrix.rows * matrix.cols * elem_size)
  { throw std::exception(); } // throw exception, meaning file is too short
  istream.seekg (current_cursor, std::istream::beg);
  for (int i = 0; i < matrix.rows; ++i)
  {
    if (!istream.read((char *) matrix.data[i], matrix.cols * elem_size))
    { throw std::exception(); } // throw exception
    // move the cursor to the next row in the file
    istream.seekg ((i + 1) * matrix.cols * elem_size, std::ios::beg);
  }
  return istream;
}
