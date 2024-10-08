#ifndef MATRIX_H
#define MATRIX_H
#include <cmath>
#include <vector>
#include <memory>
#include <iostream>
#include "TupleManager.hpp"
#include "Utility.hpp"
class Matrix {
public:
  Matrix();
  Matrix(float height, float width);
  
  // MAT4
  Matrix(float zero_zero, float zero_one, float zero_two, float zero_three,
    float one_zero, float one_one, float one_two, float one_three,
    float two_zero, float two_one, float two_two, float two_three,
    float three_zero, float three_one, float three_two, float three_three);

  // MAT3
  Matrix(float zero_zero, float zero_one, float zero_two,
    float one_zero, float one_one, float one_two,
    float two_zero, float two_one, float two_two);

  // MAT2
  Matrix(float zero_zero, float zero_one,
    float one_zero, float one_one);
  // GETS
public:
  float Width() const;
  float Height() const;
  const std::vector<std::vector<float>>& GetMatrix() const;
  // Return an non const reference that allows modification of the value
  std::vector<std::vector<float>>& ModifyMatrix();

  // SETS
public:
  void SetHeight(float height);
  void SetWidth(float width);
 
  // UTILTIY FUNCTIONS
public:
  Matrix Transpose();

  // MATH FUNCS
public:
  bool operator==(const Matrix& rhs) const;
  Matrix operator*(const Matrix& rhs) const;
  Tuple operator*(const Tuple& rhs) const;
  Matrix& operator=(const Matrix& rhs);

  float Determinant() const;
  Matrix Submatrix(float row, float col) const;
  float Minor(float row, float col) const;
  float Cofactor(float row, float col) const;
  Matrix Invert() const;

  // DEBUG
public:
  void Print() const;
private:
  float m_width;
  float m_height;
  std::vector<std::vector<float>> m_matrix;
};
#endif // !MATRIX_H
