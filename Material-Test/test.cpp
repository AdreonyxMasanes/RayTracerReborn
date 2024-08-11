#include "pch.h"
#include "Material.hpp"
TEST(MaterialTest, LightingTest) {
  Material default_material;
  Tuple position = TupleManager::Instance()->Point(0.0f, 0.0f, 0.0f);
  Tuple eye_v = TupleManager::Instance()->Vector(0.0f, 0.0f, -1.0f);
  Tuple normal_v = TupleManager::Instance()->Vector(0.0f, 0.0f, -1.0f);
  Tuple light_pos = TupleManager::Instance()->Point(0.0f, 0.0f, -10.0f);
  Tuple light_color = TupleManager::Instance()->Color(1.0f, 1.0f, 1.0f);
  Light test_light(light_pos, light_color);
  Tuple test_success_color = TupleManager::Instance()->Color(1.9f, 1.9f, 1.9f);
  EXPECT_EQ(default_material.Lighting(test_light, position, eye_v, normal_v, false), test_success_color);

  eye_v = TupleManager::Instance()->Vector(0.0f, sqrtf(2.0f) / 2.0f, -sqrtf(2) / 2.0f);
  normal_v = TupleManager::Instance()->Vector(0.0f, 0.0f, -1.0f);
  light_pos = TupleManager::Instance()->Point(0.0f, 0.0f, -10.0f);
  light_color = TupleManager::Instance()->Color(1.0f, 1.0f, 1.0f);
  test_light = Light(light_pos, light_color);
  test_success_color = TupleManager::Instance()->Color(1.0f, 1.0f, 1.0f);
  EXPECT_EQ(default_material.Lighting(test_light, position, eye_v, normal_v, false), test_success_color);

  eye_v = TupleManager::Instance()->Vector(0.0f, 0.0f, -1.0f);
  normal_v = TupleManager::Instance()->Vector(0.0f, 0.0f, -1.0f);
  light_pos = TupleManager::Instance()->Point(0.0f, 10.0f, -10.0f);
  light_color = TupleManager::Instance()->Color(1.0f, 1.0f, 1.0f);
  test_light = Light(light_pos, light_color);
  test_success_color = TupleManager::Instance()->Color(0.7364f, 0.7364f, 0.7364f);
  EXPECT_EQ(default_material.Lighting(test_light, position, eye_v, normal_v, false), test_success_color);

  eye_v = TupleManager::Instance()->Vector(0.0f, -sqrtf(2.0f) / 2.0f, -sqrtf(2.0f) / 2.0f);
  normal_v = TupleManager::Instance()->Vector(0.0f, 0.0f, -1.0f);
  light_pos = TupleManager::Instance()->Point(0.0f, 10.0f, -10.0f);
  light_color = TupleManager::Instance()->Color(1.0f, 1.0f, 1.0f);
  test_light = Light(light_pos, light_color);
  test_success_color = TupleManager::Instance()->Color(1.6364f, 1.6364f, 1.6364f);
  EXPECT_EQ(default_material.Lighting(test_light, position, eye_v, normal_v, false), test_success_color);

  eye_v = TupleManager::Instance()->Vector(0.0f, 0.0f, -1.0f);
  normal_v = TupleManager::Instance()->Vector(0.0f, 0.0f, -1.0f);
  light_pos = TupleManager::Instance()->Point(0.0f, 0.0f, 10.0f);
  light_color = TupleManager::Instance()->Color(1.0f, 1.0f, 1.0f);
  test_light = Light(light_pos, light_color);
  test_success_color = TupleManager::Instance()->Color(0.1f, 0.1f, 0.1f);
  EXPECT_EQ(default_material.Lighting(test_light, position, eye_v, normal_v, false), test_success_color);

  position = TupleManager::Instance()->Point(0.0f, 0.0f, 0.0f);
  eye_v = TupleManager::Instance()->Vector(0.0f, 0.0f, -1.0f);
  normal_v = TupleManager::Instance()->Vector(0.0f, 0.0f, -1.0f);
  light_pos = TupleManager::Instance()->Point(0.0f, 0.0f, -10.0f);
  light_color = TupleManager::Instance()->Color(1.0f, 1.0f, 1.0f);
  test_light = Light(light_pos, light_color);
  test_success_color = TupleManager::Instance()->Color(0.1f, 0.1f, 0.1f);
  EXPECT_EQ(default_material.Lighting(test_light, position, eye_v, normal_v, true), test_success_color);
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}