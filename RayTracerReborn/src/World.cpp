#include "World.hpp"

World::World() {
  Tuple light_pos = TupleManager::Instance()->Point(-10.0f, 10.0f, -10.0f);
  Tuple light_color = TupleManager::Instance()->Color(1.0f, 1.0f, 1.0f);
  Light light(light_pos, light_color);
  SetLight(light);

  Sphere temp_sphere = SphereManager::Instance()->NewSphere();
  float material_ambient = 0.1f;
  float material_diffuse = 0.7f;
  float material_specular = 0.2f;
  float material_shininess = 200.0f;
  Tuple material_color = TupleManager::Instance()->Color(0.8f, 1.0f, 0.6f);
  temp_sphere.ModifyMaterial().SetAmbient(material_ambient);
  temp_sphere.ModifyMaterial().SetDiffuse(material_diffuse);
  temp_sphere.ModifyMaterial().SetSpecular(material_specular);
  temp_sphere.ModifyMaterial().SetShininess(material_shininess);
  temp_sphere.ModifyMaterial().SetColor(material_color);
  AddSphere(temp_sphere);
  
  Sphere temp_sphere_b = SphereManager::Instance()->NewSphere();
  Matrix transform = Matrix::ScalingMatrix(0.5f, 0.5f, 0.5f);
  temp_sphere_b.SetTransform(transform);
  AddSphere(temp_sphere);
}

World::World(const std::vector<Sphere>& spheres, const Light& light) 
  :m_light(light), m_spheres(spheres) {
}

const Light& World::Lights() const {
  return m_light;
}

std::vector<Sphere>& World::Spheres() {
  return m_spheres;
}

void World::SetLight(const Light& light) {
  m_light = light;
}

void World::AddSphere(const Sphere& sphere) {
  m_spheres.push_back(sphere);
}

void World::CastRay(Ray& ray) {
  for (auto& obj: m_spheres) {
    ray.Cast(obj);
  }
  ray.SortIntersections();
}




Tuple World::ColorAt(Ray& ray) {
  CastRay(ray);
  const Intersection* hit = nullptr;
  hit = ray.Hit();
  if (!(hit == nullptr)) {
    std::unique_ptr<CompiledData> data = PrepareData(*hit, ray);
    return ShadeHit(*data);
  } else {
    return TupleManager::Instance()->Color(0.0f, 0.0f, 0.0f);
  }
}

void World::RunTest() {
  if (!(WorldCastTest())) {
    return;
  }  else {
    std::cout << "WORLD TEST PASSED" << std::endl;
  }
}

std::unique_ptr<CompiledData> World::PrepareData(const Intersection& intersection, const Ray& ray) {
  std::unique_ptr<CompiledData> data = std::make_unique<CompiledData>();
  data->m_time = intersection.Time();
  data->m_sphere = intersection.GetSphere();
  data->m_point_p = ray.Position(data->m_time);
  data->m_eye_v = -ray.Direction();
  data->m_normal_v = data->m_sphere.NormalAt(data->m_point_p);

  if (data->m_normal_v.Dot(data->m_eye_v) < 0) {
    data->m_inside_sphere = true;
    data->m_normal_v = -data->m_normal_v;
  } else {
    data->m_inside_sphere = false;
  }

  return data;
}

Tuple World::ShadeHit(const CompiledData& data) const {
  return data.m_sphere.GetMaterial().Lighting(m_light, data.m_point_p, data.m_eye_v, data.m_normal_v);
}


bool World::WorldCastTest() {
  Tuple ray_origin = TupleManager::Instance()->Point(0.0f, 0.0f, -5.0f);
  Tuple ray_direction = TupleManager::Instance()->Vector(0.0f, 0.0f, 1.0f);
  World test_world;
  Ray test_ray(ray_origin, ray_direction);

  Tuple color_success = TupleManager::Instance()->Color(0.38066f, 0.47583f, 0.2855f);
  Tuple result = test_world.ColorAt(test_ray);
  if (!(result == color_success)) {
    std::cout << "COLOR AT TEST FAILED" << std::endl;
    return false;
  }
  
  ray_direction = TupleManager::Instance()->Vector(0.0f, 1.0f, 0.0f);
  test_ray = Ray(ray_origin, ray_direction);
  color_success = TupleManager::Instance()->Color(0.0f, 0.0f, 0.0f);
  result = test_world.ColorAt(test_ray);
  if (!(result == color_success)) {
    std::cout << "COLOR AT TEST 2 FAILED" << std::endl;
    return false;
  }

  test_world.Spheres()[0].ModifyMaterial().SetAmbient(1.0f);
  test_world.Spheres()[1].ModifyMaterial().SetAmbient(1.0f);
  ray_origin = TupleManager::Instance()->Point(0.0f, 0.0f, 0.75f);
  ray_direction = TupleManager::Instance()->Vector(0.0f, 0.0f, -1.0f);
  test_ray = Ray(ray_origin, ray_direction);
  color_success = test_world.Spheres()[1].ModifyMaterial().Color();
  result = test_world.ColorAt(test_ray);
  if (!(result == color_success)) {
    std::cout << "COLOR AT TEST 3 FAILED" << std::endl;
    return false;
  } else {
    return true;
  }
}

//bool World::PrepareDataTest() {
//  Tuple ray_origin = TupleManager::Instance()->Point(0.0f, 0.0f, -5.0f);
//  Tuple ray_direction = TupleManager::Instance()->Vector(0.0f, 0.0f, 1.0f);
//  Sphere sphere(1);
//  Intersection test_intersection(4.0f, sphere);
//  Ray test_ray(*ray_origin, *ray_direction);
//
//  World test_world;
//
//  std::unique_ptr<CompiledData> data = test_world.PrepareData(test_intersection, test_ray);
//  if (!(data->m_point_p == Tuple(0.0f, 0.0f, -1.0f, 1.0 ))) {
//    std::cout << "PREPARE DATA POINT FAILED" << std::endl;
//    return false;
//  } else if (!(data->m_eye_v == Tuple(0.0f, 0.0f, -1.0f, 0.0))) {
//    std::cout << "PREPARE DATA EYEV FAILED" << std::endl;
//    return false;
//  } else if (!(data->m_normal_v == Tuple(0.0f, 0.0f, -1.0f, 0.0))) {
//    std::cout << "PREPARE DATA NORMALV FAILED" << std::endl;
//    return false;
//  } else if (!(Utility::FloatsAreEqual(data->m_time, 4.0f))) {
//    std::cout << "PREPARE DATA TIME FAILED" << std::endl;
//    return false;
//  } else {
//    return true;
//  }
//}
