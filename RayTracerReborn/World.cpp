#include "World.hpp"

World::World() {
  std::unique_ptr<Tuple> light_pos = TupleManager::Instance()->Point(-10.0f, 10.0f, -10.0f);
  std::unique_ptr<Tuple> light_color = TupleManager::Instance()->Color(1.0f, 1.0f, 1.0f);
  Light light(*light_pos, *light_color);
  AddLight(light);

  std::unique_ptr<Sphere> temp_sphere = SphereManager::Instance()->NewSphere();
  float material_ambient = 0.9f;
  float material_diffuse = 0.7f;
  float material_specular = 0.2f;
  float material_shininess = 200.0f;
  std::unique_ptr<Tuple> material_color = TupleManager::Instance()->Color(1.0f, 1.0f, 1.0f);
  temp_sphere->GetMaterial().SetAmbient(material_ambient);
  temp_sphere->GetMaterial().SetDiffuse(material_diffuse);
  temp_sphere->GetMaterial().SetSpecular(material_specular);
  temp_sphere->GetMaterial().SetShininess(material_shininess);
  temp_sphere->GetMaterial().SetColor(*material_color);
  AddSphere(*temp_sphere);
  
  temp_sphere = SphereManager::Instance()->NewSphere();
  std::unique_ptr<Matrix> transform = Matrix::ScalingMatrix(0.5f, 0.5f, 0.5f);
  temp_sphere->SetTransform(*transform);
  AddSphere(*temp_sphere);
}

const std::vector<Light>& World::Lights() const {
  return m_lights;
}

const std::vector<Sphere>& World::Spheres() const {
  return m_spheres;
}

void World::AddLight(Light& light) {
  m_lights.push_back(light);
}

void World::AddSphere(Sphere& sphere) {
  m_spheres.push_back(sphere);
}

void World::CastRay(Ray& ray) {
  for (auto& obj: m_spheres) {
    ray.Cast(obj);
    ray.SortIntersections();
  }
}

void World::RunTest() {
  if (!(WorldCastTest())) {
    return;
  } else {
    std::cout << "WORLD TEST PASSED" << std::endl;
  }
}

bool World::WorldCastTest() {
  std::unique_ptr<Tuple> ray_origin = TupleManager::Instance()->Point(0.0f, 0.0f, -5.0f);
  std::unique_ptr<Tuple> ray_direction = TupleManager::Instance()->Vector(0.0f, 0.0f, 1.0f);
  World test_world;
  Ray test_ray(*ray_origin, *ray_direction);
  test_world.CastRay(test_ray);
  if (
    !(Utility::FloatsAreEqual(test_ray.Intersections()[0].Time(), 4.0f)) &&
    !(Utility::FloatsAreEqual(test_ray.Intersections()[1].Time(), 4.5f)) &&
    !(Utility::FloatsAreEqual(test_ray.Intersections()[2].Time(), 5.5f)) &&
    !(Utility::FloatsAreEqual(test_ray.Intersections()[3].Time(), 6.0f))
    ) {
    std::cout << "WORLD RAY TEST FAILED" << std::endl;
    return false;
  }
}
