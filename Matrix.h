// Matrix.h
#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <ios>
#include <cmath>
#include <fstream>
#include <cstring>


// You don't have to use the struct. Can help you with MlpNetwork.h
typedef struct matrix_dims {
    int rows, cols;
} matrix_dims;


class Matrix
{
 private:
  void delete_data () const; // private function - frees this->data's memory
  int rows, cols;
  float **data; // 2D array
  matrix_dims dims{};

 public:

  // ***************** C'tors and D'tors *****************
  // main constructor
  Matrix (int rows, int cols);

  // default constructor
  Matrix ();

  // copy constructor
  Matrix (const Matrix &m);

  // destructor
  ~ Matrix ();

  // ***************** Getters *****************
  /**
   * @return number of rows in the matrix
   */
  int get_rows () const;
  /**
   * @return number of columns in the matrix
   */
  int get_cols () const;

  // ***************** Operators *****************
  /**
   * Matrix a, b; → a += b
   * @param other Matrix
   * @return *this
   */
  Matrix &operator+= (const Matrix &other);

  /**
   * Matrix a, b; → a + b
   * @param other Matrix to add
   * @return new matrix
   */
  Matrix operator+ (const Matrix &other) const;

  /**
   * assignment: Matrix a, b; → a = b
   * deletes all data in a and deep copying data from b
   * @param other Matrix to copy from
   * @return *this
   */
  Matrix &operator= (const Matrix &other);

  /**
   * matrix multiplication: Matrix a, b; → a * b
   * @param other Matrix to multiply
   * @return new matrix
   */
  Matrix operator* (const Matrix &other) const;

  /**
   * scalar multiplication on the right: Matrix m; float c; → m * c
   * @param c scalar
   * @return new matrix
   */
  Matrix operator* (float c) const;

  /**
   * scalar multiplication on the left: Matrix m; float c; → c * m
   * uses the previous function!
   * @param c scalar
   * @param matrix *this
   * @return new matrix
   */
  friend Matrix operator* (float c, const Matrix &matrix);

  // ***************** indexing *****************
  /**
   * parenthesis indexing: For cell (i,j) in matrix m:
   * m(i,j) will return the element in cell (i,j) in m
   * @param row row index of the element
   * @param col colomn index of the element
   * @return element value
   */
  float &operator() (int row, int col) const;

  /**
   * brackets indexing: m[k] will return the k'th element
   * while k is rows * columns
   * @param index to find in the matrix
   * @return element value
   */
  float &operator[] (int index) const;

  /**
   * Pretty print of matrix
   * @param ostream standard output
   * @param matrix *this
   * @return output stream
   */

  // ***************** Input and Output *****************
  friend std::ostream &
  operator<< (std::ostream &ostream, const Matrix &matrix);

  /**
   * Fills matrix elements
   * @param istream standard input
   * @param matrix *this
   * @return input stream
   */
  friend std::istream &operator>> (std::istream &istream, Matrix &matrix);

  // ***************** Additional functions *****************
  /**
   * Transforms a matrix into its transpose matrix
   * Supports function call chaining/concatenation
   * @return *this
   */
  Matrix &transpose (); // changes original matrix

  /**
   * Transforms a matrix into a column vector
   * Supports function call chaining/concatenation
   * @return *this
   */
  Matrix &vectorize (); // changes original matrix

  /**
   * Prints matrix elements:
   *     space after each element (including last element in row)
   *     newline after each row (including last row)
   */
  void plain_print () const;

  /**
   * Hadamard product function
   * @param other Matrix to multiply with
   * @return element-wise multiplication of *this and other
   */
  Matrix dot (const Matrix &other) const;

  /**
   * Frobenius norm function
   * @return Frobenius norm of the given matrix
   */
  float norm () const;

  /**
   * reduced row echelon form function
   * @return new Matrix that is the reduced row echelon form of the original
   */
  Matrix rref () const;

  /**
   * finding the largest number in the matrix
   * @return  index of the largest number in the matrix
   */
  int argmax () const;

  /**
   * sum up all elements in matrix
   * @return sum of all elements in the matrix
   */
  float sum () const;
};

#endif //MATRIX_H