#include "Sphere.hpp"

Sphere::Sphere() 
  : m_id(0), m_transform(Matrix::GetIdentityMatrix()) {
}

Sphere::Sphere(int id)
  :m_id(id), m_transform(Matrix::GetIdentityMatrix()) {

}

int Sphere::ID() const {
  return m_id;
}

Matrix& Sphere::ModifyTransform() {
  return m_transform;
}

Material& Sphere::ModifyMaterial() {
  return m_material;
}

const Matrix& Sphere::Transform() const{
  return m_transform;
}

const Material& Sphere::GetMaterial() const{
  return m_material;
}

bool Sphere::operator==(const Sphere& rhs) const{
  if (!(ID() == rhs.ID())) {
    return false;
  } else {
    return true;
  }
}

void Sphere::operator=(const Sphere& rhs) {
  SetID(rhs.ID());
  SetTransform(rhs.m_transform);
  SetMaterial(rhs.GetMaterial());
}

Tuple Sphere::NormalAt(const Tuple& world_point) const{
  Matrix inverted_transform = (Transform().Invert());
  Tuple object_point = (inverted_transform * world_point);
  Tuple object_normal = (object_point - TupleManager::Instance()->Point(0.0f, 0.0f, 0.0f));

  Tuple world_normal = ((inverted_transform).Transpose() * (object_normal));
  world_normal.SetW(0.0f);
  return world_normal.Normalize();
}

void Sphere::SetTransform(const Matrix& transform) {
  m_transform = transform;
}

void Sphere::SetID(int id) {
  m_id = id;
}

void Sphere::SetMaterial(const Material& material) {
  m_material = material;
}

void Sphere::RunTest() {
  if (!(NormalAtTest())) {
    return;
  } else {
    std::cout << "SPHERE TEST PASSED" << std::endl;
  }
}
bool Sphere::NormalAtTest() {
  Sphere test_sphere(1.0f);
  Tuple point = TupleManager::Instance()->Point(1.0f, 0.0f, 0.0f);
  Tuple result = test_sphere.NormalAt(point);
  Tuple success_v = TupleManager::Instance()->Vector(1.0f, 0.0f, 0.0f);
  if (!(result == success_v)) {
    std::cout << "NORMAL TEST 1 FAILED" << std::endl;
    return false;
  }

  point = TupleManager::Instance()->Point(0.0f, 1.0f, 0.0f);
  result = test_sphere.NormalAt(point);
  success_v = TupleManager::Instance()->Vector(0.0f, 1.0f, 0.0f);
  if (!(result == success_v)) {
    std::cout << "NORMAL TEST 2 FAILED" << std::endl;
    return false;
  }

  point = TupleManager::Instance()->Point(0.0f, 1.0f, 0.0f);
  result = test_sphere.NormalAt(point);
  success_v = TupleManager::Instance()->Vector(0.0f, 1.0f, 0.0f);
  if (!(result == success_v)) {
    std::cout << "NORMAL TEST 3 FAILED" << std::endl;
    return false;
  }

  point = TupleManager::Instance()->Point(sqrtf(3.0f) / 3.0f, sqrtf(3.0f) / 3.0f, sqrtf(3.0f) / 3.0f);
  result = test_sphere.NormalAt(point);
  success_v = TupleManager::Instance()->Vector(sqrtf(3.0f) / 3.0f, sqrtf(3.0f) / 3.0f, sqrtf(3.0f) / 3.0f);
  if (!(result == success_v)) {
    std::cout << "NORMAL TEST 4 FAILED" << std::endl;
    return false;
  }

  Matrix translation = Matrix::TranslationMatrix(0.0f, 1.0f, 0.0f);
  test_sphere.SetTransform(translation);
  point = TupleManager::Instance()->Point(0.0f, 1.70711f, -0.70711f);
  result = test_sphere.NormalAt(point);
  success_v = TupleManager::Instance()->Vector(0.0f, 0.70711f, -0.70711f);
  if (!(result == success_v)) {
    std::cout << "NORMAL TEST 5 FAILED" << std::endl;
    return false;
  }
  
  float pi_5 = 0.62831853071;
  Matrix scaling = Matrix::ScalingMatrix(1.0f, 0.50f, 1.0f);
  Matrix rotation_z = Matrix::RotationZMatrix(pi_5);
  Matrix transform = Matrix::TranformationMatrix(rotation_z, scaling);
  test_sphere.SetTransform(transform);
  point = TupleManager::Instance()->Point(0.0f, sqrtf(2) / 2.0f, -sqrtf(2) / 2.0f);
  result = test_sphere.NormalAt(point);
  success_v = TupleManager::Instance()->Vector(0.0f, 0.97014f, -0.24254f);
  if (!(result == success_v)) {
    std::cout << "NORMAL TEST 6 FAILED" << std::endl;
    return false;
  }
}

//float* Sphere::Intersect(Ray& ray) {
//  // SEMANTICS?!
//  Tuple world_origin = TupleManager::Instance()->Point(0.0f, 0.0f, 0.0f);
//
//  Tuple sphere_to_ray = ray.Origin() - *world_origin;
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



//bool Sphere::IntersectTest() {
//  Tuple ray_origin = TupleManager::Instance()->Point(0.0f, 0.0f, -5.0f);
//  Tuple ray_direction = TupleManager::Instance()->Vector(0.0f, 0.0f, 1.0f);
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
