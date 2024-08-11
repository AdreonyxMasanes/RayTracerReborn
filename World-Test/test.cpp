#include "pch.h"
#include "World.hpp"

TEST(WorldTest, IsShadowedTest) {
  World world;
  Tuple point = TupleManager::Instance()->Point(0.0f, 10.0f, 0.0f);
  EXPECT_FALSE(world.IsShadowed(point));

  point = TupleManager::Instance()->Point(10.0f, -10.0f, 10.0f);
  EXPECT_TRUE(world.IsShadowed(point));

  point = TupleManager::Instance()->Point(-20.0f, 20.0f, -20.0f);
  EXPECT_FALSE(world.IsShadowed(point));

  point = TupleManager::Instance()->Point(-2.0f, 2.0f, -2.0f);
  EXPECT_FALSE(world.IsShadowed(point));
}

TEST(WorldTest, OverPointTest) {
  const float kEpsilon = 0.01f;
  World world;
  Tuple ray_origin = TupleManager::Instance()->Point(0.0f, 0.0f, -5.0f);
  Tuple ray_direction = TupleManager::Instance()->Vector(0.0f, 0.0f, 1.0f);
  Ray ray(ray_origin, ray_direction);
  Sphere sphere = SphereManager::Instance()->NewSphere();
  Matrix translate = MatrixUtil::TranslationMatrix(0.0f, 0.0f, 1.0f);
  sphere.SetTransform(translate);
  Intersection intersection(5.0f, sphere);
  std::unique_ptr<CompiledData> data = world.PrepareData(intersection, ray);
  EXPECT_LT(data->m_over_point_p.Z(), -kEpsilon / 2.0f);
  EXPECT_GT(data->m_point_p.Z(), data->m_over_point_p.Z());
  
}

TEST(WorldTest, ShadeHit) {
  Tuple light_pos = TupleManager::Instance()->Point(0.0f, 0.0f, -10.0f);
  Tuple light_color = TupleManager::Instance()->Color(1.0f, 1.0f, 1.0f);
  Light light(light_pos, light_color);
  std::vector<Sphere> spheres;
  Sphere temp = SphereManager::Instance()->NewSphere();
  spheres.push_back(temp);
  temp = SphereManager::Instance()->NewSphere();
  Matrix translate = MatrixUtil::TranslationMatrix(0.0f, 0.0f, 10.0f);
  temp.SetTransform(translate);
  spheres.push_back(temp);
  Tuple ray_origin = TupleManager::Instance()->Point(0.0f, 0.0f, 5.0f);
  Tuple ray_direction = TupleManager::Instance()->Vector(0.0f, 0.0f, 1.0f);
  Ray ray(ray_origin, ray_direction);
  World world(spheres, light);
  Intersection intersection(4.0f, spheres[1]);
  std::unique_ptr<CompiledData> data = world.PrepareData(intersection, ray);
  Tuple color = world.ShadeHit(*data);
  Tuple succes_color = TupleManager::Instance()->Color(0.1, 0.1f, 0.1f);
  EXPECT_EQ(color, succes_color);

}

int main(int argc, char**argv) {
  TupleManager::Init();
  SphereManager::Init();

  testing::InitGoogleTest(&argc, argv);
  int success = RUN_ALL_TESTS();
  TupleManager::Shutdown();
  SphereManager::Shutdown();
  return success;
}