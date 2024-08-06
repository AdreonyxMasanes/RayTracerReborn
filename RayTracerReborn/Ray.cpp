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

void Ray::RunTest() {
  if (!(PositionTest())) {
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
