#include "pch.h"
#include "Tuple.hpp"

TEST(TupleTest, AdditionTest) {
  Tuple test_p(3.0f, -2.0f, 5.0f, 1.0f);
  Tuple test_v(-2.0f, 3.0f, 1.0f, 0.0f);
  Tuple test_success_p(1.0f, 1.0f, 6.0f, 1.0f);

  EXPECT_EQ(test_p + test_v, test_success_p);
}

TEST(TupleTest, SubtractionTest) {
  Tuple test_a_p(3.0f, 2.0f, 1.0f, 1.0f);
  Tuple test_b_p(5.0f, 6.0f, 7.0f, 1.0f);
  Tuple test_success_v(-2.0f, -4.0f, -6.0f, 0.0f);
  Tuple test_success_p(-2.0f, -4.0f, -6.0f, 1.0f);
  Tuple test_a_v(5.0f, 6.0f, 7.0f, 0.0f);
  Tuple test_b_v(3.0f, 2.0f, 1.0f, 0.0f);

  EXPECT_EQ(test_a_p - test_b_p, test_success_v);
  EXPECT_EQ(test_a_p - test_a_v, test_success_p);
  EXPECT_EQ(test_b_v - test_a_v, test_success_v);
}

TEST(TupleTest, NegationTest) {
  Tuple test_p(1.0f, -2.0f, 3.0f, -4.0f);
  Tuple test_success_t(-1.0f, 2.0f, -3.0f, 4.0f);

  EXPECT_EQ(-test_p, test_success_t);
}

TEST(TupleTest, MultiplicationTest) {
  Tuple test_t(1.0f, -2.0f, 3.0f, -4.0f);
  Tuple test_success_t(3.5f, -7.0f, 10.5f, -14.0f);

  EXPECT_EQ(test_t * 3.5f, test_success_t);

  test_success_t = Tuple(0.5f, -1.0f, 1.5f, -2.0f);
  EXPECT_EQ(test_t * 0.5f, test_success_t);
}

TEST(TupleTest, DivisionTest) {
  Tuple test_t(1.0f, -2.0f, 3.0f, -4.0f);
  Tuple test_success_t(0.5f, -1.0f, 1.5f, -2.0f);

  EXPECT_EQ(test_t / 2.0f, test_success_t);
}

TEST(TupleTest, MultiplyTwoTuples) {
  Tuple test_a_c(1.0f, 0.2f, 0.4f, 0.0f);
  Tuple test_b_c(0.9f, 1.0f, 0.1f, 0.0f);
  Tuple test_success_c(0.9f, 0.2f, 0.04f, 0.0f);

  EXPECT_EQ(test_a_c * test_b_c, test_success_c);
}

TEST(TupleTest, MagnitudeTest) {
  Tuple test_v(1.0f, 0.0f, 0.0f, 0.0f);
  EXPECT_FLOAT_EQ(test_v.Magnitude(), 1.0f);
  test_v = Tuple(1.0f, 2.0f, 3.0f, 0.0f);
  EXPECT_FLOAT_EQ(test_v.Magnitude(), sqrtf(14.0f));
}

TEST(TupleTest, NormalizeTest) {
  Tuple test_v(4.0f, 0.0f, 0.0f, 0.0f);
  Tuple test_success_v(1.0f, 0.0f, 0.0f, 0.0f);

  EXPECT_EQ(test_v.Normalize(), test_success_v);
  test_v = Tuple(1.0f, 2.0f, 3.0f, 0.0f);
  test_success_v = Tuple(1.0f / sqrtf(14), 2.0f / sqrtf(14), 3.0f / sqrtf(14), 0.0f);
  EXPECT_EQ(test_v.Normalize(), test_success_v);
}

TEST(TupleTest, ReflectTest) {
  Tuple test_a_v(1.0f, -1.0f, 0.0f, 0.0f);
  Tuple test_a_normal_v(0.0f, 1.0f, 0.0f, 0.0f);
  Tuple test_a_success_v(1.0f, 1.0f, 0.0f, 0.0f);
  EXPECT_EQ(test_a_v.Reflect(test_a_normal_v), test_a_success_v);

  test_a_v = Tuple(0.0f, -1.0f, 0.0f, 0.0f);
  test_a_normal_v = Tuple(sqrtf(2) / 2.0f, sqrtf(2) / 2.0f, 0.0f, 0.0f);
  test_a_success_v = Tuple(1.0f, 0.0f, 0.0f, 0.0f);
  EXPECT_EQ(test_a_v.Reflect(test_a_normal_v), test_a_success_v);
}

TEST(TupleTest, DotTest) {
  Tuple test_a_v(1.0f, 2.0f, 3.0f, 0.0f);
  Tuple test_b_v(2.0f, 3.0f, 4.0f, 0.0f);
  EXPECT_EQ(test_a_v.Dot(test_b_v), 20.0f);
}

TEST(TupleTest, CrossTest) {
  Tuple test_a_v(1.0f, 2.0f, 3.0f, 0.0f);
  Tuple test_b_v(2.0f, 3.0f, 4.0f, 0.0f);
  Tuple test_success_v(-1.0f, 2.0f, -1.0f, 0.0f);
  EXPECT_EQ(test_a_v.Cross(test_b_v), test_success_v);

  test_success_v = Tuple(1.0f, -2.0f, 1.0f, 0.0f);
  EXPECT_EQ(test_b_v.Cross(test_a_v), test_success_v);
}

TEST(TupleTest, IsPoint) {
  Tuple test_p(0.0f, 0.0f, 0.0f, 1.0f);
  Tuple test_v(0.0f, 0.0f, 0.0f, 0.0f);

  EXPECT_TRUE(test_p.IsPoint());
  EXPECT_FALSE(test_v.IsPoint());
}

TEST(TupleTest, EqualityTest) {
  Tuple test_a_p(0.0f, 0.0f, 0.0f, 1.0f);
  Tuple test_b_p(0.0f, 0.0f, 0.0f, 1.0f);

  Tuple test_a_v(0.0f, 0.0f, 0.0f, 0.0f);
  Tuple test_b_v(0.0f, 0.0f, 0.0f, 0.0f);
  EXPECT_EQ(test_a_p, test_b_p);
  //EXPECT_NE(test_a_p, test_a_v);
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}