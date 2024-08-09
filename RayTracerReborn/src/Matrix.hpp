#ifndef MATRIX_H
#define MATRIX_H
#include <cmath>
#include <vector>
#include <memory>
#include <iostream>
#include "Utility.hpp"
#include "TupleManager.hpp"
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
  float Width();
  float Height();
  const std::vector<std::vector<float>>& GetMatrix() const;
  std::vector<std::vector<float>>& GetMatrix();

  // SETS
public:
  void SetHeight(float height);
  void SetWidth(float width);
 
  // UTILTIY FUNCTIONS
public:
  Matrix Transpose();

  static Matrix TranslationMatrix(float x, float y, float z);
  static Matrix ScalingMatrix(float x, float y, float z);
  static Matrix RotationXMatrix(float radians);
  static Matrix RotationYMatrix(float radians);
  static Matrix RotationZMatrix(float radians);
  static Matrix ShearingMatrix(float xy, float xz, float yx, float yz, float zx, float zy);
  static Matrix TranformationMatrix(Matrix& first, Matrix& second);
  static Matrix TranformationMatrix(Matrix& first, Matrix& second, Matrix& third);
  static Matrix GetIdentityMatrix();
  static Matrix GetViewTransform(Tuple& from, Tuple& to, Tuple& up);

  // MATH FUNCS
public:
  bool operator==(const Matrix& rhs) const;
  Matrix operator*(Matrix& rhs);
  Tuple operator*(Tuple& rhs);
  Matrix& operator=(Matrix& rhs);

  float Determinant();
  Matrix Submatrix(float row, float col);
  float Minor(float row, float col);
  float Cofactor(float row, float col);
  Matrix Invert();

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
  static bool TransformTest();
  static bool ShearingTest();
  static bool TranformChainingTest();
  static bool ViewTransformTest();
};
#endif // !MATRIX_H
