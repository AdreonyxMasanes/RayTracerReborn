#include "Ray.hpp"

Ray::Ray() 
  : m_origin_p(Tuple(0.0f, 0.0f, 0.0f, 1.0f)), m_direction_v(Tuple(0.0f, 0.0f, 0.0f, 0.0f)) {
}

Ray::Ray(Tuple& origin_p, Tuple& direction_v) 
  : m_origin_p(origin_p), m_direction_v(direction_v) {
}

Tuple& Ray::Origin() {
  return m_origin_p;
}

Tuple& Ray::Direction() {
  return m_direction_v;
}

std::unique_ptr<Tuple> Ray::Position(float time) {
  return Origin() + *(Direction() * time);
}

Intersection* Ray::Cast(Sphere& sphere) {
  // SEMANTICS?!
  std::unique_ptr<Tuple> world_origin = TupleManager::Instance()->Point(0.0f, 0.0f, 0.0f);

  std::unique_ptr<Tuple> sphere_to_ray = Origin() - *world_origin;

  float a = Direction().Dot(Direction());
  float b = 2 * Direction().Dot(*sphere_to_ray);
  float c = sphere_to_ray->Dot(*sphere_to_ray) - 1;
  float discriminant = powf(b, 2) - 4 * a * c;

  if (discriminant < 0) {
    return nullptr;
  } else {
    Intersection hits[2]{
      //(-b - sqrtf(discriminant)) / (2 * a),
      //(-b + sqrtf(discriminant)) / (2 * a)
      Intersection((-b - sqrtf(discriminant)) / (2 * a), sphere),
      Intersection((-b + sqrtf(discriminant)) / (2 * a), sphere)
    };
    return hits;
  }
}

void Ray::RunTest() {
  if (!(PositionTest())) {
    return;
  } else if (!(CastTest())) {
    return;
  } else {
    std::cout << "RAY TESTS PASSED" << std::endl;
  }
}

bool Ray::PositionTest() {
  std::unique_ptr<Tuple> ray_origin = TupleManager::Instance()->Point(2.0f, 3.0f, 4.0f);
  std::unique_ptr<Tuple> ray_direction = TupleManager::Instance()->Vector(1.0f, 0.0f, 0.0f);
  Ray test_ray(*ray_origin, *ray_direction);

  std::unique_ptr<Tuple> result = test_ray.Position(0.0f);
  std::unique_ptr<Tuple> position_success = TupleManager::Instance()->Point(2.0f, 3.0f, 4.0f);
  if (!(*result == *position_success)) {
    std::cout << "RAY POSITION TEST 1 FAILED" << std::endl;
    return false;
  }

  result = test_ray.Position(1.0f);
  position_success = TupleManager::Instance()->Point(3.0f, 3.0f, 4.0f);
  if (!(*result == *position_success)) {
    std::cout << "RAY POSITION TEST 2 FAILED" << std::endl;
    return false;
  }
  
  result = test_ray.Position(-1.0f);
  position_success = TupleManager::Instance()->Point(1.0f, 3.0f, 4.0f);
  if (!(*result == *position_success)) {
    std::cout << "RAY POSITION TEST 3 FAILED" << std::endl;
    return false;
  }
  
  result = test_ray.Position(2.5f);
  position_success = TupleManager::Instance()->Point(4.5f, 3.0f, 4.0f);
  if (!(*result == *position_success)) {
    std::cout << "RAY POSITION TEST 4 FAILED" << std::endl;
    return false;
  } else {
    return true;
  }
}

bool Ray::CastTest() {
  std::unique_ptr<Tuple> ray_origin = TupleManager::Instance()->Point(0.0f, 0.0f, -5.0f);
  std::unique_ptr<Tuple> ray_direction = TupleManager::Instance()->Vector(0.0f, 0.0f, 1.0f);
  Ray test_ray(*ray_origin, *ray_direction);
  Sphere test_sphere(1);
  Intersection* hits = test_ray.Cast(test_sphere);
  if (!(Utility::FloatsAreEqual(hits[0].Time(), 4.0f) && Utility::FloatsAreEqual(hits[1].Time(), 6.0f))) {
    std::cout << "INTERSECTION TEST 1 FAILED" << std::endl;
    return false;
  }

  ray_origin = TupleManager::Instance()->Point(0.0f, 1.0f, -5.0f);
  test_ray = Ray(*ray_origin, *ray_direction);
  hits = test_ray.Cast(test_sphere);
  if (!(Utility::FloatsAreEqual(hits[0].Time(), 5.0f) && Utility::FloatsAreEqual(hits[1].Time(), 5.0f))) {
    std::cout << "INTERSECTION TEST 2 FAILED" << std::endl;
    return false;
  }

  ray_origin = TupleManager::Instance()->Point(0.0f, 2.0f, -5.0f);
  test_ray = Ray(*ray_origin, *ray_direction);
  hits = test_ray.Cast(test_sphere);
  if (!(hits == nullptr)) {
    std::cout << "INTERSECTION TEST 3 FAILED" << std::endl;
    return false;
  }

  ray_origin = TupleManager::Instance()->Point(0.0f, 0.0f, 0.0f);
  test_ray = Ray(*ray_origin, *ray_direction);
  hits = test_ray.Cast(test_sphere);
  if (!(Utility::FloatsAreEqual(hits[0].Time(), -1.0f) && Utility::FloatsAreEqual(hits[1].Time(), 1.0f))) {
    std::cout << "INTERSECTION TEST 4 FAILED" << std::endl;
    return false;
  }

  ray_origin = TupleManager::Instance()->Point(0.0f, 0.0f, 5.0f);
  test_ray = Ray(*ray_origin, *ray_direction);
  hits = test_ray.Cast(test_sphere);
  if (!(Utility::FloatsAreEqual(hits[0].Time(), -6.0f) && Utility::FloatsAreEqual(hits[1].Time(), -4.0f))) {
    std::cout << "INTERSECTION TEST 5 FAILED" << std::endl;
    return false;
  }
}
