#ifndef MATRIX_UTIL_H
#include "Matrix.hpp"

namespace MatrixUtil{
  Matrix TranslationMatrix(float x, float y, float z);
  Matrix ScalingMatrix(float x, float y, float z);
  Matrix RotationXMatrix(float radians);
  Matrix RotationYMatrix(float radians);
  Matrix RotationZMatrix(float radians);
  Matrix ShearingMatrix(float xy, float xz, float yx, float yz, float zx, float zy);
  Matrix TranformationMatrix(const Matrix& first, const Matrix& second);
  Matrix TranformationMatrix(const Matrix& first, const Matrix& second, const Matrix& third);
  Matrix GetIdentityMatrix();
  Matrix GetViewTransform(const Tuple& from, const Tuple& to, const Tuple& up);
}
#endif // !MATRIX_UTIL_H


