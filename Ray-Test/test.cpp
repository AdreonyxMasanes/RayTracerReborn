#include "pch.h"
#include "Ray.hpp"

TEST(RayTest, PositionTest) {
  Tuple ray_origin = TupleManager::Instance()->Point(2.0f, 3.0f, 4.0f);
  Tuple ray_direction = TupleManager::Instance()->Vector(1.0f, 0.0f, 0.0f);
  Ray test_ray(ray_origin, ray_direction);
  Tuple position_success = TupleManager::Instance()->Point(2.0f, 3.0f, 4.0f);
  EXPECT_EQ(test_ray.Position(0.0f), position_success);

  position_success = TupleManager::Instance()->Point(3.0f, 3.0f, 4.0f);
  EXPECT_EQ(test_ray.Position(1.0f), position_success);

  position_success = TupleManager::Instance()->Point(1.0f, 3.0f, 4.0f);
  EXPECT_EQ(test_ray.Position(-1.0f), position_success);

  position_success = TupleManager::Instance()->Point(4.5f, 3.0f, 4.0f);
  EXPECT_EQ(test_ray.Position(2.5f), position_success);
}

TEST(RayTest, CastTest) {
  Tuple ray_origin = TupleManager::Instance()->Point(0.0f, 0.0f, -5.0f);
  Tuple ray_direction = TupleManager::Instance()->Vector(0.0f, 0.0f, 1.0f);
  Ray test_ray(ray_origin, ray_direction);
  Sphere test_sphere(1);
  test_ray.Cast(test_sphere);
  EXPECT_FLOAT_EQ(test_ray.Intersections()[0].Time(), 4.0f);
  EXPECT_FLOAT_EQ(test_ray.Intersections()[1].Time(), 6.0f);
  test_ray.ModifyIntersections().clear();

  ray_origin = TupleManager::Instance()->Point(0.0f, 1.0f, -5.0f);
  test_ray = Ray(ray_origin, ray_direction);
  test_ray.Cast(test_sphere);
  EXPECT_FLOAT_EQ(test_ray.Intersections()[0].Time(), 5.0f);
  EXPECT_FLOAT_EQ(test_ray.Intersections()[1].Time(), 5.0f);
  test_ray.ModifyIntersections().clear();

  ray_origin = TupleManager::Instance()->Point(0.0f, 2.0f, -5.0f);
  test_ray = Ray(ray_origin, ray_direction);
  test_ray.Cast(test_sphere);
  EXPECT_FLOAT_EQ(test_ray.Intersections().size(), 0.0f);
  test_ray.ModifyIntersections().clear();

  ray_origin = TupleManager::Instance()->Point(0.0f, 0.0f, 0.0f);
  test_ray = Ray(ray_origin, ray_direction);
  test_ray.Cast(test_sphere);
  EXPECT_FLOAT_EQ(test_ray.Intersections()[0].Time(), -1.0f);
  EXPECT_FLOAT_EQ(test_ray.Intersections()[1].Time(), 1.0f);
  test_ray.ModifyIntersections().clear();

  ray_origin = TupleManager::Instance()->Point(0.0f, 0.0f, 5.0f);
  test_ray = Ray(ray_origin, ray_direction);
  test_ray.Cast(test_sphere);
  EXPECT_FLOAT_EQ(test_ray.Intersections()[0].Time(), -6.0f);
  EXPECT_FLOAT_EQ(test_ray.Intersections()[1].Time(), -4.0f);
  test_ray.ModifyIntersections().clear();

  ray_origin = TupleManager::Instance()->Point(0.0f, 0.0f, -5.0f);
  ray_direction = TupleManager::Instance()->Vector(0.0f, 0.0f, 1.0f);
  test_ray = Ray(ray_origin, ray_direction);
  Matrix scaling = Matrix::ScalingMatrix(2.0f, 2.0f, 2.0f);
  test_sphere.SetTransform(scaling);
  test_ray.Cast(test_sphere);
  EXPECT_FLOAT_EQ(test_ray.Intersections()[0].Time(), 3.0f);
  EXPECT_FLOAT_EQ(test_ray.Intersections()[1].Time(), 7.0f);
  test_ray.ModifyIntersections().clear();

  Matrix translation = Matrix::TranslationMatrix(5.0f, 0.0f, 0.0f);
  test_sphere.SetTransform(translation);
  test_ray.Cast(test_sphere);
  EXPECT_FLOAT_EQ(test_ray.Intersections().size(), 0.0f);
  test_ray.ModifyIntersections().clear();
}

TEST(RayTest, TransformTest) {
  Tuple ray_origin = TupleManager::Instance()->Point(1.0f, 2.0f, 3.0f);
  Tuple ray_direction = TupleManager::Instance()->Vector(0.0f, 1.0f, 0.0f);
  Tuple ray_origin_success = TupleManager::Instance()->Point(4.0f, 6.0f, 8.0f);
  Tuple ray_direction_success = TupleManager::Instance()->Vector(0.0f, 1.0f, 0.0f);
  Matrix translate = Matrix::TranslationMatrix(3.0f, 4.0f, 5.0f);
  Ray test_ray(ray_origin, ray_direction);
  Ray test_ray_success(ray_origin_success, ray_direction_success);
  EXPECT_EQ(test_ray.Transform(translate), test_ray_success);

  Matrix scaling = Matrix::ScalingMatrix(2.0f, 3.0f, 4.0f);
  ray_origin_success = TupleManager::Instance()->Point(2.0f, 6.0f, 12.0f);
  ray_direction_success = TupleManager::Instance()->Vector(0.0f, 3.0f, 0.0f);
  test_ray_success = Ray(ray_origin_success, ray_direction_success);
  EXPECT_EQ(test_ray.Transform(scaling), test_ray_success);
}

TEST(RayTest, HitTest) {
  Tuple ray_origin = TupleManager::Instance()->Point(0.0f, 0.0f, 0.0f);
  Tuple ray_direction = TupleManager::Instance()->Vector(0.0f, 0.0f, 1.0f);
  Ray test_ray(ray_origin, ray_direction);
  Sphere test_sphere(1);
  Intersection test_a_intersection(1.0f, test_sphere);
  Intersection test_b_intersection(2.0f, test_sphere);
  test_ray.ModifyIntersections().push_back(test_b_intersection);
  test_ray.ModifyIntersections().push_back(test_a_intersection);
  test_ray.SortIntersections();
  const Intersection* hit = test_ray.Hit();
  Intersection hit_value = *hit;
  EXPECT_EQ(hit_value, test_a_intersection);
  test_ray.ModifyIntersections().clear();

  test_a_intersection.SetTime(1.0f);
  test_b_intersection.SetTime(1.0f);
  test_ray.ModifyIntersections().push_back(test_b_intersection);
  test_ray.ModifyIntersections().push_back(test_a_intersection);
  test_ray.SortIntersections();
  hit = test_ray.Hit();
  hit_value = *hit;
  EXPECT_EQ(hit_value, test_b_intersection);
  test_ray.ModifyIntersections().clear();

  test_a_intersection.SetTime(-2.0f);
  test_b_intersection.SetTime(-1.0f);
  test_ray.ModifyIntersections().push_back(test_b_intersection);
  test_ray.ModifyIntersections().push_back(test_a_intersection);
  test_ray.SortIntersections();
  hit = test_ray.Hit();
  EXPECT_EQ(hit, nullptr);

  test_a_intersection.SetTime(5.0f);
  test_b_intersection.SetTime(7.0f);
  Intersection test_c_intersection(-3.0f, test_sphere);
  Intersection test_d_intersection(2.0f, test_sphere);
  test_ray.ModifyIntersections().push_back(test_a_intersection);
  test_ray.ModifyIntersections().push_back(test_b_intersection);
  test_ray.ModifyIntersections().push_back(test_c_intersection);
  test_ray.ModifyIntersections().push_back(test_d_intersection);
  test_ray.SortIntersections();
  hit = test_ray.Hit();
  hit_value = *hit;
  EXPECT_EQ(hit_value, test_d_intersection);
  test_ray.ModifyIntersections().clear();
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}