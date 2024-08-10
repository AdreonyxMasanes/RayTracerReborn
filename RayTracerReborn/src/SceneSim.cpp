#include "SceneSim.hpp"

void SceneSim::Run() {
  auto start = std::chrono::system_clock::now();
  std::vector<Sphere> spheres;
  Sphere floor = SphereManager::Instance()->NewSphere();
  Matrix floor_transform = Matrix::ScalingMatrix(10.0f, 0.01f, 10.0f);
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
  Matrix left_wall_scale = Matrix::ScalingMatrix(10.0f, 0.01f, 10.0f);
  Matrix left_wall_rotation_x = Matrix::RotationXMatrix(pi_2);
  Matrix left_wall_rotation_y = Matrix::RotationYMatrix(-pi_4);
  Matrix left_wall_translation = Matrix::TranslationMatrix(0.0f, 0.0f, 5.0f);

  Matrix temp_a = Matrix::TranformationMatrix(left_wall_scale, left_wall_rotation_x, left_wall_rotation_y);
  Matrix transform_a = Matrix::TranformationMatrix(temp_a, left_wall_translation);
  left_wall.SetTransform(transform_a);
  spheres.push_back(left_wall);

  Sphere right_wall = SphereManager::Instance()->NewSphere();
  right_wall.SetMaterial(floor.GetMaterial());
  Matrix right_wall_scale = Matrix::ScalingMatrix(10.0f, 0.01f, 10.0f);
  Matrix right_wall_rotation_x = Matrix::RotationXMatrix(pi_2);
  Matrix right_wall_rotation_y = Matrix::RotationYMatrix(pi_4);
  Matrix right_wall_translation = Matrix::TranslationMatrix(0.0f, 0.0f, 5.0f);

  Matrix temp_b = Matrix::TranformationMatrix(right_wall_scale, right_wall_rotation_x, right_wall_rotation_y);
  Matrix transform_b = Matrix::TranformationMatrix(temp_b, right_wall_translation);
  right_wall.SetTransform(transform_b);
  spheres.push_back(right_wall);

  Sphere middle = SphereManager::Instance()->NewSphere();
  Matrix middle_translation = Matrix::TranslationMatrix(-0.5f, 1.0f, 0.5f);
  Tuple middle_color = TupleManager::Instance()->Color(0.1f, 1.0f, 0.5f);
  float middle_diffuse = 0.7f;
  float middle_specular = 0.3f;
  middle.SetTransform(middle_translation);
  middle.ModifyMaterial().SetColor(middle_color);
  middle.ModifyMaterial().SetDiffuse(middle_diffuse);
  middle.ModifyMaterial().SetSpecular(middle_specular);
  spheres.push_back(middle);

  Sphere right = SphereManager::Instance()->NewSphere();
  Matrix right_translation = Matrix::TranslationMatrix(1.5f, 0.5f, -0.5f);
  Matrix right_scale = Matrix::ScalingMatrix(0.5f, 0.5f, 0.5f);
  Matrix right_transform = Matrix::TranformationMatrix(right_scale, right_translation);
  Tuple right_color = TupleManager::Instance()->Color(0.0f, 0.0f, 1.0f);
  float right_diffuse = 0.7f;
  float right_specular = 0.3f;
  right.SetTransform(right_transform);
  right.ModifyMaterial().SetColor(right_color);
  right.ModifyMaterial().SetDiffuse(right_diffuse);
  right.ModifyMaterial().SetSpecular(right_specular);
  spheres.push_back(right);

  Sphere left = SphereManager::Instance()->NewSphere();
  Matrix left_translation = Matrix::TranslationMatrix(-1.5f, 0.33f, -0.75f);
  Matrix left_scale = Matrix::ScalingMatrix(0.33f, 0.33f, 0.33f);
  Matrix left_transform = Matrix::TranformationMatrix(left_scale, left_translation);
  Tuple left_color = TupleManager::Instance()->Color(1.0f, 0.8f, 0.1f);
  float left_diffuse = 0.7f;
  float left_specular = 0.3f;
  left.SetTransform(left_transform);
  left.ModifyMaterial().SetColor(left_color);
  left.ModifyMaterial().SetDiffuse(left_diffuse);
  left.ModifyMaterial().SetSpecular(left_specular);
  spheres.push_back(left);

  Tuple light_pos = TupleManager::Instance()->Point(-10.0f, 10.0f, -10.0f);
  Tuple light_color = TupleManager::Instance()->Color(1.0f, 1.0f, 1.0f);

  Light light(light_pos, light_color);
  
  float pi_3 = 1.0471975512f;
  float fov = pi_3;
  World test_world(spheres, light);
  Camera test_camera(256 , 128, fov);

  Tuple from = TupleManager::Instance()->Point(0.0f, 1.5f, -5.0f);
  Tuple to = TupleManager::Instance()->Point(0.0f, 1.0f, 0.0f);
  Tuple up = TupleManager::Instance()->Vector(0.0f, 1.0f, 0.0f);

  Matrix view = Matrix::GetViewTransform(from, to, up);
  test_camera.SetTransform(view);
  test_camera.GenerateCanvas(test_world);
  PPM ppm(test_camera.GetCanvas());
  std::cout << "PPM GENERATED" << std::endl;
  auto end = std::chrono::system_clock::now();
  auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
  auto elapsed_s = std::chrono::duration_cast<std::chrono::seconds>(end - start);
  std::cout << "TIME: " << elapsed_ms.count() << " miliseconds" << std::endl;
  std::cout << "TIME: " << elapsed_s.count() << " seconds" << std::endl;
}
