#ifndef MATRIX_H
#define MATRIX_H
#include <cmath>
#include <vector>
#include <memory>
#include <iostream>
#include "Utility.hpp"
#include "Tuple.hpp"
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
  float Width();
  float Height();
  std::vector<std::vector<float>>& GetMatrix();
  // SETS
public:
  void SetHeight(float height);
  void SetWidth(float width);
  
  static std::unique_ptr<Matrix> GetIdentityMatrix();
  // UTILTIY FUNCTIONS
public:
  std::unique_ptr<Matrix> Transpose();
  std::unique_ptr<Matrix> Submatrix(float row, float col);
  // MATH FUNCS
public:
  bool operator==(Matrix& rhs);
  std::unique_ptr<Matrix> operator*(Matrix& rhs);
  std::unique_ptr<Tuple> operator*(Tuple& rhs);
  Matrix& operator=(Matrix& rhs);

  float Determinant();
  float Minor(float row, float col);
  float Cofactor(float row, float col);
  std::unique_ptr<Matrix> Invert();

  // DEBUG
public:
  void Print();
  static void RunTest();
private:
  float m_width;
  float m_height;
  std::vector<std::vector<float>> m_matrix;

  static void CreationTest();
  static bool EqualityTest();
  static bool MatrixMultiplyTest();
  static bool MatrixMultiplyByTupleTest();
  static bool TransposeTest();
  static bool DeterimantTest();
  static bool InversionTest();
};
#endif // !MATRIX_H
