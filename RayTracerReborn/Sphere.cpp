#include "Sphere.hpp"

Sphere::Sphere() 
  : m_id(0), m_transform(*Matrix::GetIdentityMatrix()){
}

Sphere::Sphere(int id)
  :m_id(id), m_transform(*Matrix::GetIdentityMatrix()) {

}

int Sphere::ID() {
  return m_id;
}

Matrix& Sphere::Transform() {
  return m_transform;
}

bool Sphere::operator==(Sphere& rhs) {
  if (!(ID() == rhs.ID())) {
    return false;
  } else {
    return true;
  }
}

void Sphere::operator=(Sphere& rhs) {
  SetID(rhs.ID());
  SetTransform(rhs.m_transform);
}

void Sphere::SetTransform(Matrix& transform) {
  m_transform = transform;
}

void Sphere::SetID(int id) {
  m_id = id;
}

//float* Sphere::Intersect(Ray& ray) {
//  // SEMANTICS?!
//  std::unique_ptr<Tuple> world_origin = TupleManager::Instance()->Point(0.0f, 0.0f, 0.0f);
//
//  std::unique_ptr<Tuple> sphere_to_ray = ray.Origin() - *world_origin;
//
//  float a = ray.Direction().Dot(ray.Direction());
//  float b = 2 * ray.Direction().Dot(*sphere_to_ray);
//  float c = sphere_to_ray->Dot(*sphere_to_ray) - 1;
//  float discriminant = powf(b, 2) - 4 * a * c;
//
//  if (discriminant < 0) {
//    return nullptr;
//  } else {
//    float hits[2]{
//      (-b - sqrtf(discriminant)) / (2 * a),
//      (-b + sqrtf(discriminant)) / (2 * a)
//      //Intersection((-b - sqrtf(discriminant)) / (2 * a), *this),
//      //Intersection((-b + sqrtf(discriminant)) / (2 * a), *this)
//    };
//    return hits;
//  }
//}

//void Sphere::RunTest() {
//  if (!(IntersectTest())) {
//    return;
//  } else {
//    std::cout << "SPHERE TEST PASSED" << std::endl;
//  }
//}

//bool Sphere::IntersectTest() {
//  std::unique_ptr<Tuple> ray_origin = TupleManager::Instance()->Point(0.0f, 0.0f, -5.0f);
//  std::unique_ptr<Tuple> ray_direction = TupleManager::Instance()->Vector(0.0f, 0.0f, 1.0f);
//  Ray test_ray(*ray_origin, *ray_direction);
//  Sphere test_sphere(1);
//  float* hits = test_sphere.Intersect(test_ray);
//  if (!(Utility::FloatsAreEqual(hits[0], 4.0f) && Utility::FloatsAreEqual(hits[1], 6.0f))) {
//    std::cout << "INTERSECTION TEST 1 FAILED" << std::endl;
//    return false;
//  }
//
//  ray_origin = TupleManager::Instance()->Point(0.0f, 1.0f, -5.0f);
//  test_ray = Ray(*ray_origin, *ray_direction);
//  hits = test_sphere.Intersect(test_ray);
//  if (!(Utility::FloatsAreEqual(hits[0], 5.0f) && Utility::FloatsAreEqual(hits[1], 5.0f))) {
//    std::cout << "INTERSECTION TEST 2 FAILED" << std::endl;
//    return false;
//  }
//
//  ray_origin = TupleManager::Instance()->Point(0.0f, 2.0f, -5.0f);
//  test_ray = Ray(*ray_origin, *ray_direction);
//  hits = test_sphere.Intersect(test_ray);
//  if (!(hits == nullptr)) {
//    std::cout << "INTERSECTION TEST 3 FAILED" << std::endl;
//    return false;
//  }
//
//  ray_origin = TupleManager::Instance()->Point(0.0f, 0.0f, 0.0f);
//  test_ray = Ray(*ray_origin, *ray_direction);
//  hits = test_sphere.Intersect(test_ray);
//  if (!(Utility::FloatsAreEqual(hits[0], -1.0f) && Utility::FloatsAreEqual(hits[1], 1.0f))) {
//    std::cout << "INTERSECTION TEST 4 FAILED" << std::endl;
//    return false;
//  }
//
//  ray_origin = TupleManager::Instance()->Point(0.0f, 0.0f, 5.0f);
//  test_ray = Ray(*ray_origin, *ray_direction);
//  hits = test_sphere.Intersect(test_ray);
//  if (!(Utility::FloatsAreEqual(hits[0], -6.0f) && Utility::FloatsAreEqual(hits[1], -4.0f))) {
//    std::cout << "INTERSECTION TEST 5 FAILED" << std::endl;
//    return false;
//  }
//}
