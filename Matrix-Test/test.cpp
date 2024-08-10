#include "pch.h"
#include "MatrixUtil.hpp"
using namespace MatrixUtil;
TEST(MatrixTest, EqualityTest) {
  Matrix mat_4_a(
    1.0f, 2.0f, 3.0f, 4.0f,
    5.5f, 6.5f, 7.5f, 8.5f,
    9.0f, 10.0f, 11.0f, 12.0f,
    13.5f, 14.5f, 15.5f, 16.f);
  Matrix mat_4_b(
    1.0f, 2.0f, 3.0f, 4.0f,
    5.5f, 6.5f, 7.5f, 8.5f,
    9.0f, 10.0f, 11.0f, 12.0f,
    13.5f, 14.5f, 15.5f, 16.f);
  EXPECT_EQ(mat_4_a, mat_4_b);
}

TEST(MatrixTest, MultiplyTwoMatricies) {
  Matrix mat_4_a(
    1.0f, 2.0f, 3.0f, 4.0f,
    5.0f, 6.0f, 7.0f, 8.0f,
    9.0f, 8.0f, 7.0f, 6.0f,
    5.0f, 4.0f, 3.0f, 2.0f);
  Matrix mat_4_b(
    -2.0f, 1.0f, 2.0f, 3.0f,
    3.0f, 2.0f, 1.0f, -1.0f,
    4.0f, 3.0f, 6.0f, 5.0f,
    1.0f, 2.0f, 7.0f, 8.0f);

  Matrix mat_4_solution(
    20.0f, 22.0f, 50.0f, 48.0f,
    44.0f, 54.0f, 114.0f, 108.0f,
    40.0f, 58.0f, 110.0f, 102.0f,
    16.0f, 26.0f, 46.0f, 42.0f);

  EXPECT_EQ(mat_4_a * mat_4_b, mat_4_solution);
}

TEST(MatrixTest, MultiplyByTuple) {
  Matrix mat_4_a(
    1.0f, 2.0f, 3.0f, 4.0f,
    2.0f, 4.0f, 4.0f, 2.0f,
    8.0f, 6.0f, 4.0f, 1.0f,
    0.0f, 0.0f, 0.0f, 1.0f);
  Tuple test_t(1.0f, 2.0f, 3.0f, 1.0f);
  Tuple test_solution_t(18.0f, 24.0f, 33.0f, 1.0f);

  EXPECT_EQ(mat_4_a * test_t, test_solution_t);
}

TEST(MatrixTest, TransposeTest) {
  Matrix mat_4_a(
    0.0f, 9.0f, 3.0f, 0.0f,
    9.0f, 8.0f, 0.0f, 8.0f,
    1.0f, 8.0f, 5.0f, 3.0f,
    0.0f, 0.0f, 5.0f, 8.0f);
  Matrix mat_4_solution(
    0.0f, 9.0f, 1.0f, 0.0f,
    9.0f, 8.0f, 8.0f, 0.0f,
    3.0f, 0.0f, 5.0f, 5.0f,
    0.0f, 8.0f, 3.0f, 8.0f);

  EXPECT_EQ(mat_4_a.Transpose(), mat_4_solution);
}

TEST(MatrixTest, DeterminantTest) {
  Matrix mat_3(
    1.0f, 2.0f, 6.0f,
    -5.0f, 8.0f, -4.0f,
    2.0f, 6.0f, 4.0f);
  Matrix mat_4(
    -2.0f, -8.0f, 3.0f, 5.0f,
    -3.0f, 1.0f, 7.0f, 3.0f,
    1.0f, 2.0f, -9.0f, 6.0f,
    -6.0f, 7.0f, 7.0f, -9.0f);
  EXPECT_FLOAT_EQ(mat_3.Determinant(), -196.0f);
  EXPECT_FLOAT_EQ(mat_4.Determinant(), -4071.0f);
}

TEST(MatrixTest, InversionTest) {
  Matrix mat_4_a(
    -5.0f, 2.0f, 6.0f, -8.0f,
    1.0f, -5.0f, 1.0f, 8.0f,
    7.0f, 7.0f, -6.0f, -7.0f,
    1.0f, -3.0f, 7.0f, 4.0f);
  Matrix mat_4_a_invert_success(
     0.21805f, 0.45113f, 0.24060f, -0.04511f,
    -0.80825f, -1.45677f, -0.44361f, 0.52068f,
    -0.07895f, -0.22368f, -0.05263f, 0.19737f,
    -0.52256f, -0.81391f, -0.30075f, 0.30639f);
  EXPECT_EQ(mat_4_a.Invert(), mat_4_a_invert_success);
}

TEST(MatrixTest, TranlastionTest) {
  Tuple test_a_p = TupleManager::Instance()->Point(-3.0f, 4.0f, 5.0f);
  Matrix translation = TranslationMatrix(5.0f, -3.0f, 2.0f);
  Tuple translation_success_p(2.0f, 1.0f, 7.0f, 1.0f);
  EXPECT_EQ(translation * test_a_p, translation_success_p);
}

TEST(MatrixTest, ScalingTest) {
  Tuple test_a_p = TupleManager::Instance()->Point(-4.0f, 6.0f, 8.0f);
  Matrix scaling = ScalingMatrix(2.0f, 3.0f, 4.0f);
  Tuple scaling_success_p(-8.0f, 18.0f, 32.0f, 1.0f);
  EXPECT_EQ(scaling * test_a_p, scaling_success_p);
}

TEST(MatrixTest, RotationXTest) {
  float pi_4 = 0.78539816339;
  float pi_2 = 1.57079632679;
  Tuple test_a_p = TupleManager::Instance()->Point(0.0f, 1.0f, 0.0f);
  Matrix half_quarer_rotation = RotationXMatrix(pi_4);
  Matrix full_quarter_rotation = RotationXMatrix(pi_2);
  Tuple rotation_x_half_success(0.0f, sqrtf(2.0f) / 2.0f, sqrtf(2.0f) / 2.0f, 1.0f);
  Tuple rotation_x_full_success(0.0f, 0.0f, 1.0f, 1.0f);
  EXPECT_EQ(half_quarer_rotation * test_a_p, rotation_x_half_success);
  EXPECT_EQ(full_quarter_rotation * test_a_p, rotation_x_full_success);
}

TEST(MatrixTest, RotationYTest) {
  float pi_4 = 0.78539816339;
  float pi_2 = 1.57079632679;
  Tuple test_a_p = TupleManager::Instance()->Point(0.0f, 0.0f, 1.0f);
  Matrix half_quarer_rotation = RotationYMatrix(pi_4);
  Matrix full_quarter_rotation = RotationYMatrix(pi_2);
  Tuple rotation_y_half_success(sqrtf(2.0f) / 2.0f, 0.0f, sqrtf(2.0f) / 2.0f, 1.0f);
  Tuple rotation_y_full_success(1.0f, 0.0f, 0.0f, 1.0f);
  EXPECT_EQ(half_quarer_rotation * test_a_p, rotation_y_half_success);
  EXPECT_EQ(full_quarter_rotation * test_a_p, rotation_y_full_success);
}

TEST(MatrixTest, RotationZTest) {
  float pi_4 = 0.78539816339;
  float pi_2 = 1.57079632679;
  Tuple test_a_p = TupleManager::Instance()->Point(0.0f, 1.0f, 0.0f);
  Matrix half_quarer_rotation = RotationZMatrix(pi_4);
  Matrix full_quarter_rotation = RotationZMatrix(pi_2);
  Tuple rotation_z_half_success(-sqrtf(2.0f) / 2.0f, sqrtf(2.0f) / 2.0f, 0.0f, 1.0f);
  Tuple rotation_z_full_success(-1.0f, 0.0f, 0.0f, 1.0f);
  EXPECT_EQ(half_quarer_rotation * test_a_p, rotation_z_half_success);
  EXPECT_EQ(full_quarter_rotation * test_a_p, rotation_z_full_success);
}

TEST(MatrixTest, ShearingTest) {
  Matrix shearing = ShearingMatrix(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
  Tuple test_p = TupleManager::Instance()->Point(2.0f, 3.0f, 4.0f);
  Tuple shearing_success(5.0f, 3.0f, 4.0f, 1.0f);
  EXPECT_EQ(shearing * test_p, shearing_success);

  shearing = ShearingMatrix(0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
  test_p = TupleManager::Instance()->Point(2.0f, 3.0f, 4.0f);
  shearing_success = Tuple(6.0f, 3.0f, 4.0f, 1.0f);
  EXPECT_EQ(shearing * test_p, shearing_success);

  shearing = ShearingMatrix(0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f);
  test_p = TupleManager::Instance()->Point(2.0f, 3.0f, 4.0f);
  shearing_success = Tuple(2.0f, 5.0f, 4.0f, 1.0f);
  EXPECT_EQ(shearing * test_p, shearing_success);

  shearing = ShearingMatrix(0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
  test_p = TupleManager::Instance()->Point(2.0f, 3.0f, 4.0f);
  shearing_success = Tuple(2.0f, 7.0f, 4.0f, 1.0f);
  EXPECT_EQ(shearing * test_p, shearing_success);

  shearing = ShearingMatrix(0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
  test_p = TupleManager::Instance()->Point(2.0f, 3.0f, 4.0f);
  shearing_success = Tuple(2.0f, 3.0f, 6.0f, 1.0f);
  EXPECT_EQ(shearing * test_p, shearing_success);

  shearing = ShearingMatrix(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
  test_p = TupleManager::Instance()->Point(2.0f, 3.0f, 4.0f);
  shearing_success = Tuple(2.0f, 3.0f, 7.0f, 1.0f);
  EXPECT_EQ(shearing * test_p, shearing_success);
}

TEST(MatrixTest, MatrixChaining) {
  float pi_4 = 0.78539816339;
  float pi_2 = 1.57079632679;

  Tuple test_p = TupleManager::Instance()->Point(1.0f, 0.0f, 1.0f);
  Matrix rotation_x = RotationXMatrix(pi_2);
  Matrix scale = ScalingMatrix(5.0f, 5.0f, 5.0f);
  Matrix translate = TranslationMatrix(10.0f, 5.0f, 7.0f);
  Matrix transform = TranformationMatrix(rotation_x, scale, translate);
  Tuple test_success_p(15.0f, 0.0f, 7.0f, 1.0f);

  EXPECT_EQ(transform * test_p, test_success_p);
}

TEST(MatrixTest, ViewMatrix) {
  Tuple from = TupleManager::Instance()->Point(0.0f, 0.0f, 0.0f);
  Tuple to = TupleManager::Instance()->Point(0.0f, 0.0f, -1.0f);
  Tuple up = TupleManager::Instance()->Vector(0.0f, 1.0f, 0.0f);
  Matrix view = GetViewTransform(from, to, up);
  Matrix success = GetIdentityMatrix();
  EXPECT_EQ(view, success);

  from = TupleManager::Instance()->Point(0.0f, 0.0f, 0.0f);
  to = TupleManager::Instance()->Point(0.0f, 0.0f, 1.0f);
  up = TupleManager::Instance()->Vector(0.0f, 1.0f, 0.0f);
  view = GetViewTransform(from, to, up);
  success = ScalingMatrix(-1.0f, 1.0f, -1.0f);
  EXPECT_EQ(view, success);

  from = TupleManager::Instance()->Point(0.0f, 0.0f, 8.0f);
  to = TupleManager::Instance()->Point(0.0f, 0.0f, 0.0f);
  up = TupleManager::Instance()->Vector(0.0f, 1.0f, 0.0f);
  view = GetViewTransform(from, to, up);
  success = TranslationMatrix(0.0f, 0.0f, -8.0f);
  EXPECT_EQ(view, success);

  from = TupleManager::Instance()->Point(1.0f, 3.0f, 2.0f);
  to = TupleManager::Instance()->Point(4.0f, -2.0f, 8.0f);
  up = TupleManager::Instance()->Vector(1.0f, 1.0f, 0.0f);
  view = GetViewTransform(from, to, up);
  success = Matrix(
    -0.50709f, 0.50709f, 0.67612f, -2.36643f,
    0.76772f, 0.60609f, 0.12122f, -2.82843f,
    -0.35857f, 0.59761f, -0.71714f, 0.00000f,
    0.00000f, 0.00000f, 0.00000f, 1.00000f
  );
  EXPECT_EQ(view, success);
}
