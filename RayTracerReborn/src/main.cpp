#include "TupleManager.hpp"
#include "SphereManager.hpp"
#include "Ray.hpp"
#include "Material.hpp"
#include "World.hpp"
#include "Camera.hpp"

#include "BulletSim.hpp"
#include "ClockSim.hpp"
#include "ShadowSim.hpp"
#include "SceneSim.hpp"
void CreateSpheres(std::vector<Sphere>& spheres);

int main() {
  //SINGLETON TYPE IMPLEMENTATION
  TupleManager::Init();
  SphereManager::Init();

  std::vector<Sphere> spheres;
  CreateSpheres(spheres);
  SceneSim::Run(spheres);
  
  
  SphereManager::Shutdown();
  TupleManager::Shutdown();
  return 0;
}

// YOU CAN CHANGE THE WORLD HERE. ONLY MODIFY THE ONES COMMENTED MODIFY
void CreateSpheres(std::vector<Sphere>& spheres) {
  Sphere floor = SphereManager::Instance()->NewSphere();
  Matrix floor_transform = ScalingMatrix(10.0f, 0.01f, 10.0f);
  Tuple floor_color = TupleManager::Instance()->Color(1.0f, 0.9f, 0.9f);
  float floor_specular = 0.0f;
  floor.SetTransform(floor_transform);
  floor.ModifyMaterial().SetColor(floor_color);
  floor.ModifyMaterial().SetSpecular(floor_specular);
  spheres.push_back(floor);

  float pi_2 = 1.57079632679;
  float pi_4 = 0.78539816339;
  Sphere left_wall = SphereManager::Instance()->NewSphere();
  left_wall.SetMaterial(floor.GetMaterial());
  Matrix left_wall_scale = ScalingMatrix(10.0f, 0.01f, 10.0f);
  Matrix left_wall_rotation_x = RotationXMatrix(pi_2);
  Matrix left_wall_rotation_y = RotationYMatrix(-pi_4);
  Matrix left_wall_translation = TranslationMatrix(0.0f, 0.0f, 5.0f);

  Matrix temp_a = TranformationMatrix(left_wall_scale, left_wall_rotation_x, left_wall_rotation_y);
  Matrix transform_a = TranformationMatrix(temp_a, left_wall_translation);
  left_wall.SetTransform(transform_a);
  spheres.push_back(left_wall);

  Sphere right_wall = SphereManager::Instance()->NewSphere();
  right_wall.SetMaterial(floor.GetMaterial());
  Matrix right_wall_scale = ScalingMatrix(10.0f, 0.01f, 10.0f);
  Matrix right_wall_rotation_x = RotationXMatrix(pi_2);
  Matrix right_wall_rotation_y = RotationYMatrix(pi_4);
  Matrix right_wall_translation = TranslationMatrix(0.0f, 0.0f, 5.0f);

  Matrix temp_b = TranformationMatrix(right_wall_scale, right_wall_rotation_x, right_wall_rotation_y);
  Matrix transform_b = TranformationMatrix(temp_b, right_wall_translation);
  right_wall.SetTransform(transform_b);
  spheres.push_back(right_wall);
  
  // YOU CAN MODIFY THIS ONE
  Sphere middle = SphereManager::Instance()->NewSphere();
  // MODIFY ITS POS HERE
  Matrix middle_translation = TranslationMatrix(-0.5f, 1.0f, 0.5f);
  // MODIFY ITS COLOR HERE
  Tuple middle_color = TupleManager::Instance()->Color(0.1f, 1.0f, 0.5f);
  float middle_diffuse = 0.7f;
  float middle_specular = 0.3f;
  middle.SetTransform(middle_translation);
  middle.ModifyMaterial().SetColor(middle_color);
  middle.ModifyMaterial().SetDiffuse(middle_diffuse);
  middle.ModifyMaterial().SetSpecular(middle_specular);
  spheres.push_back(middle);

  // YOU CAN MODIFY THIS ONE
  Sphere right = SphereManager::Instance()->NewSphere();
  // MODIFY ITS POS HERE
  Matrix right_translation = TranslationMatrix(1.5f, 0.5f, -0.5f);
  Matrix right_scale = ScalingMatrix(0.5f, 0.5f, 0.5f);
  Matrix right_transform = TranformationMatrix(right_scale, right_translation);
  // MODIFY ITS COLOR HERE
  Tuple right_color = TupleManager::Instance()->Color(0.0f, 1.0f, 0.0f);
  float right_diffuse = 0.7f;
  float right_specular = 0.3f;
  right.SetTransform(right_transform);
  right.ModifyMaterial().SetColor(right_color);
  right.ModifyMaterial().SetDiffuse(right_diffuse);
  right.ModifyMaterial().SetSpecular(right_specular);
  spheres.push_back(right);

  // YOU CAN MODIFY THIS ONE
  Sphere left = SphereManager::Instance()->NewSphere();
  // MODIFY ITS POS HERE
  Matrix left_translation = TranslationMatrix(-1.5f, 0.33f, -0.75f);
  Matrix left_scale = ScalingMatrix(0.33f, 0.33f, 0.33f);
  Matrix left_transform = TranformationMatrix(left_scale, left_translation);
  // MODIFY ITS COLOR HERE
  Tuple left_color = TupleManager::Instance()->Color(1.0f, 0.8f, 0.1f);
  float left_diffuse = 0.7f;
  float left_specular = 0.3f;
  left.SetTransform(left_transform);
  left.ModifyMaterial().SetColor(left_color);
  left.ModifyMaterial().SetDiffuse(left_diffuse);
  left.ModifyMaterial().SetSpecular(left_specular);
  spheres.push_back(left);
}