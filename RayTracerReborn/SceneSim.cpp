#include "SceneSim.hpp"

void SceneSim::Run() {
  auto start = std::chrono::system_clock::now();
  std::vector<Sphere> spheres;
  std::unique_ptr<Sphere> floor = SphereManager::Instance()->NewSphere();
  std::unique_ptr<Matrix> floor_transform = Matrix::ScalingMatrix(10.0f, 0.01f, 10.0f);
  std::unique_ptr<Tuple> floor_color = TupleManager::Instance()->Color(1.0f, 0.9f, 0.9f);
  float floor_specular = 0.0f;
  floor->SetTransform(*floor_transform);
  floor->GetMaterial().SetColor(*floor_color);
  floor->GetMaterial().SetSpecular(floor_specular);
  spheres.push_back(*floor);

  float pi_2 = 1.57079632679;
  float pi_4 = 0.78539816339;
  std::unique_ptr<Sphere> left_wall = SphereManager::Instance()->NewSphere();
  left_wall->SetMaterial(floor->GetMaterial());
  std::unique_ptr<Matrix> left_wall_scale = Matrix::ScalingMatrix(10.0f, 0.01f, 10.0f);
  std::unique_ptr<Matrix> left_wall_rotation_x = Matrix::RotationXMatrix(pi_2);
  std::unique_ptr<Matrix> left_wall_rotation_y = Matrix::RotationYMatrix(-pi_4);
  std::unique_ptr<Matrix> left_wall_translation = Matrix::TranslationMatrix(0.0f, 0.0f, 5.0f);

  std::unique_ptr<Matrix> temp = Matrix::TranformationMatrix(*left_wall_scale, *left_wall_rotation_x, *left_wall_rotation_y);
  std::unique_ptr<Matrix> transform = Matrix::TranformationMatrix(*temp, *left_wall_translation);
  left_wall->SetTransform(*transform);
  spheres.push_back(*left_wall);

  std::unique_ptr<Sphere> right_wall = SphereManager::Instance()->NewSphere();
  right_wall->SetMaterial(floor->GetMaterial());
  std::unique_ptr<Matrix> right_wall_scale = Matrix::ScalingMatrix(10.0f, 0.01f, 10.0f);
  std::unique_ptr<Matrix> right_wall_rotation_x = Matrix::RotationXMatrix(pi_2);
  std::unique_ptr<Matrix> right_wall_rotation_y = Matrix::RotationYMatrix(pi_4);
  std::unique_ptr<Matrix> right_wall_translation = Matrix::TranslationMatrix(0.0f, 0.0f, 5.0f);

  temp = Matrix::TranformationMatrix(*right_wall_scale, *right_wall_rotation_x, *right_wall_rotation_y);
  transform = Matrix::TranformationMatrix(*temp, *right_wall_translation);
  right_wall->SetTransform(*transform);
  spheres.push_back(*right_wall);

  std::unique_ptr<Sphere> middle = SphereManager::Instance()->NewSphere();
  std::unique_ptr<Matrix> middle_translation = Matrix::TranslationMatrix(-0.5f, 1.0f, 0.5f);
  std::unique_ptr<Tuple> middle_color = TupleManager::Instance()->Color(0.1f, 1.0f, 0.5f);
  float middle_diffuse = 0.7f;
  float middle_specular = 0.3f;
  middle->SetTransform(*middle_translation);
  middle->GetMaterial().SetColor(*middle_color);
  middle->GetMaterial().SetDiffuse(middle_diffuse);
  middle->GetMaterial().SetSpecular(middle_specular);
  spheres.push_back(*middle);

  std::unique_ptr<Sphere> right = SphereManager::Instance()->NewSphere();
  std::unique_ptr<Matrix> right_translation = Matrix::TranslationMatrix(1.5f, 0.5f, -0.5f);
  std::unique_ptr<Matrix> right_scale = Matrix::ScalingMatrix(0.5f, 0.5f, 0.5f);
  std::unique_ptr<Matrix> right_transform = Matrix::TranformationMatrix(*right_scale, *right_translation);
  std::unique_ptr<Tuple> right_color = TupleManager::Instance()->Color(0.5f, 1.0f, 0.1f);
  float right_diffuse = 0.7f;
  float right_specular = 0.3f;
  right->SetTransform(*right_transform);
  right->GetMaterial().SetColor(*right_color);
  right->GetMaterial().SetDiffuse(right_diffuse);
  right->GetMaterial().SetSpecular(right_specular);
  spheres.push_back(*right);

  std::unique_ptr<Sphere> left = SphereManager::Instance()->NewSphere();
  std::unique_ptr<Matrix> left_translation = Matrix::TranslationMatrix(-1.5f, 0.33f, -0.75f);
  std::unique_ptr<Matrix> left_scale = Matrix::ScalingMatrix(0.33f, 0.33f, 0.33f);
  std::unique_ptr<Matrix> left_transform = Matrix::TranformationMatrix(*left_scale, *left_translation);
  std::unique_ptr<Tuple> left_color = TupleManager::Instance()->Color(1.0f, 0.8f, 0.1f);
  float left_diffuse = 0.7f;
  float left_specular = 0.3f;
  left->SetTransform(*left_transform);
  left->GetMaterial().SetColor(*left_color);
  left->GetMaterial().SetDiffuse(left_diffuse);
  left->GetMaterial().SetSpecular(left_specular);
  spheres.push_back(*left);

  std::unique_ptr<Tuple> light_pos = TupleManager::Instance()->Point(-10.0f, 10.0f, -10.0f);
  std::unique_ptr<Tuple> light_color = TupleManager::Instance()->Color(1.0f, 1.0f, 1.0f);

  Light light(*light_pos, *light_color);
  
  float pi_3 = 1.0471975512f;
  float fov = pi_3;
  World test_world(spheres, light);
  Camera test_camera(160, 120, fov);

  std::unique_ptr<Tuple> from = TupleManager::Instance()->Point(0.0f, 1.5f, -5.0f);
  std::unique_ptr<Tuple> to = TupleManager::Instance()->Point(0.0f, 1.0f, 0.0f);
  std::unique_ptr<Tuple> up = TupleManager::Instance()->Vector(0.0f, 1.0f, 0.0f);

  std::unique_ptr<Matrix> view = Matrix::GetViewTransform(*from, *to, *up);
  test_camera.SetTransform(*view);
  test_camera.GenerateCanvas(test_world);
  PPM ppm(test_camera.GetCanvas());
  std::cout << "PPM GENERATED" << std::endl;
  auto end = std::chrono::system_clock::now();
  auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
  auto elapsed_s = std::chrono::duration_cast<std::chrono::seconds>(end - start);
  std::cout << "TIME: " << elapsed_ms.count() << " miliseconds" << std::endl;
  std::cout << "TIME: " << elapsed_s.count() << " seconds" << std::endl;
}
