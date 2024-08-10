#include "Utility.hpp"

namespace Utility {
  namespace FloatUtil {
    bool FloatsAreEqual(float a, float b) {
      const float kEpsilon = 0.0001f;
      if (abs(a - b) < kEpsilon) {
        return true;
      } else {
        return false;
      }
    }
  }

  namespace MatrixUtil {
    Matrix TranslationMatrix(float x, float y, float z) {
      return Matrix(
        1.0f, 0.0f, 0.0f, x,
        0.0f, 1.0f, 0.0f, y,
        0.0f, 0.0f, 1.0f, z,
        0.0f, 0.0f, 0.0f, 1.0f
      );
    }

    Matrix ScalingMatrix(float x, float y, float z) {
      return Matrix(
        x, 0.0f, 0.0f, 0.0f,
        0.0f, y, 0.0f, 0.0f,
        0.0f, 0.0f, z, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
      );
    }

    Matrix RotationXMatrix(float radians) {
      return Matrix(
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, cosf(radians), -sinf(radians), 0.0f,
        0.0f, sinf(radians), cosf(radians), 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
      );
    }

    Matrix RotationYMatrix(float radians) {
      return Matrix(
        cosf(radians), 0.0f, sinf(radians), 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        -sinf(radians), 0.0f, cosf(radians), 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
      );
    }

    Matrix RotationZMatrix(float radians) {
      return Matrix(
        cosf(radians), -sinf(radians), 0.0f, 0.0f,
        sinf(radians), cosf(radians), 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
      );
    }

    Matrix ShearingMatrix(float xy, float xz, float yx, float yz, float zx, float zy) {
      return Matrix(
        1.0f, xy, xz, 0.0f,
        yx, 1.0f, yz, 0.0f,
        zx, zy, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
      );
    }

    Matrix TranformationMatrix(const Matrix& first, const Matrix& second) {
      return second * first;
    }

    Matrix TranformationMatrix(const Matrix& first, const Matrix& second, const Matrix& third) {
      return (third * second) * first;
    }

    Matrix GetIdentityMatrix() {
      return Matrix(
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
      );
    }

    Matrix GetViewTransform(const Tuple& from, const Tuple& to, const Tuple& up) {
      Tuple forward = (to - from).Normalize();
      Tuple up_normal = up.Normalize();
      Tuple left = forward.Cross(up_normal);
      Tuple true_up = left.Cross(forward);

      Matrix orientation(
        left.X(), left.Y(), left.Z(), 0.0f,
        true_up.X(), true_up.Y(), true_up.Z(), 0.0f,
        -forward.X(), -forward.Y(), -forward.Z(), 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
      );

      Matrix translation = TranslationMatrix(-from.X(), -from.Y(), -from.Z());
      return orientation * translation;
    }
  }


}

