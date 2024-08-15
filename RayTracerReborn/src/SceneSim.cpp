#include "SceneSim.hpp"

void SceneSim::Run(std::vector<Sphere>& spheres) {
  auto start = std::chrono::system_clock::now();
  
  Tuple light_pos = TupleManager::Instance()->Point(-10.0f, 10.0f, -10.0f);
  Tuple light_color = TupleManager::Instance()->Color(1.0f, 1.0f, 1.0f);

  Light light(light_pos, light_color);
  
  float pi_3 = 1.0471975512f;
  float fov = pi_3;
  World test_world(spheres, light);
  Camera test_camera(1920 , 1080, fov);

  Tuple from = TupleManager::Instance()->Point(0.0f, 1.5f, -5.0f);
  Tuple to = TupleManager::Instance()->Point(0.0f, 1.0f, 0.0f);
  Tuple up = TupleManager::Instance()->Vector(0.0f, 1.0f, 0.0f);

  Matrix view = GetViewTransform(from, to, up);
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
