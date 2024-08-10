#include "Ray.hpp"

Ray::Ray() 
  : m_origin_p(Tuple(0.0f, 0.0f, 0.0f, 1.0f)), m_direction_v(Tuple(0.0f, 0.0f, 0.0f, 0.0f)) {
}

Ray::Ray(const Tuple& origin_p, const Tuple& direction_v) 
  : m_origin_p(origin_p), m_direction_v(direction_v) {
}

const Tuple& Ray::Origin() const {
  return m_origin_p;
}

const Tuple& Ray::Direction() const {
  return m_direction_v;
}


const std::vector<Intersection>& Ray::Intersections() const {
  return m_intersections;
}

std::vector<Intersection>& Ray::ModifyIntersections() {
  return m_intersections;
}

Tuple Ray::Position(float time) const {
  return m_origin_p + (m_direction_v * time);
}

void Ray::Cast(const Sphere& sphere) {
  Matrix inverted = sphere.Transform().Invert();
  Ray transformed_ray = Transform((inverted));
  
  Tuple world_origin = TupleManager::Instance()->Point(0.0f, 0.0f, 0.0f);

  Tuple sphere_to_ray = transformed_ray.Origin() - world_origin;

  float a = transformed_ray.Direction().Dot(transformed_ray.Direction());
  float b = 2 * transformed_ray.Direction().Dot(sphere_to_ray);
  float c = sphere_to_ray.Dot(sphere_to_ray) - 1;
  float discriminant = powf(b, 2) - 4 * a * c;

  if (!(discriminant < 0)) {
    m_intersections.push_back(Intersection((-b - sqrtf(discriminant)) / (2 * a), sphere));
    m_intersections.push_back(Intersection((-b + sqrtf(discriminant)) / (2 * a), sphere));
  }
}

void Ray::SortIntersections() {
  bool isSorted = false;
  while (!isSorted && m_intersections.size() > 0) {
    for (int i = 0; i < m_intersections.size(); i++) {
      if (!(i == m_intersections.size() - 1)) {
        if (m_intersections.at(i).Time() > m_intersections.at(i + 1).Time()) {
          Intersection temp = m_intersections.at(i);
          m_intersections.at(i) = m_intersections.at(i + 1);
          m_intersections.at(i + 1) = temp;
          break;
        }
      } else {
        isSorted = true;
      }
    }
  }
}

// CAN BE NULL SO WE NEED TO KNOW SO PASS POINTER INSTEAD OF REFERENCE
const Intersection* Ray::Hit() const{

  // WHILE SORTING JUST POP A VALUE IF IT IS NEGATIVE THEN CAN JUST RETURN INTERSECTIONS[0]
  // since it is sorted, returns the first non negative value.
  for (auto& intersection : m_intersections) {
    if (intersection.Time() >= 0) {
      return &intersection;
    }
  }
  return nullptr;
}

Ray Ray::Transform(const Matrix& transform) const{
  Tuple origin = transform * m_origin_p;
  Tuple direction = transform * m_direction_v;
  return Ray(origin, direction);
}

bool Ray::operator==(const Ray& rhs) const{
  if (!(m_origin_p == rhs.Origin())) {
    return false;
  } else if (!(m_direction_v == rhs.Direction())) {
    return false;
  } else {
    return true;
  }
}

void Ray::RunTest() {
  if (!(PositionTest())) {
    return;
  } else if (!(CastTest())) {
    return;
  } else if (!(HitTest())) {
    return;
  } else if (!(TransformTest())) {
    return;
  } else {
    std::cout << "RAY TESTS PASSED" << std::endl;
  }
}



bool Ray::PositionTest() {
  Tuple ray_origin = TupleManager::Instance()->Point(2.0f, 3.0f, 4.0f);
  Tuple ray_direction = TupleManager::Instance()->Vector(1.0f, 0.0f, 0.0f);
  Ray test_ray(ray_origin, ray_direction);

  Tuple result = test_ray.Position(0.0f);
  Tuple position_success = TupleManager::Instance()->Point(2.0f, 3.0f, 4.0f);
  if (!(result == position_success)) {
    std::cout << "RAY POSITION TEST 1 FAILED" << std::endl;
    return false;
  }

  result = test_ray.Position(1.0f);
  position_success = TupleManager::Instance()->Point(3.0f, 3.0f, 4.0f);
  if (!(result == position_success)) {
    std::cout << "RAY POSITION TEST 2 FAILED" << std::endl;
    return false;
  }
  
  result = test_ray.Position(-1.0f);
  position_success = TupleManager::Instance()->Point(1.0f, 3.0f, 4.0f);
  if (!(result == position_success)) {
    std::cout << "RAY POSITION TEST 3 FAILED" << std::endl;
    return false;
  }
  
  result = test_ray.Position(2.5f);
  position_success = TupleManager::Instance()->Point(4.5f, 3.0f, 4.0f);
  if (!(result == position_success)) {
    std::cout << "RAY POSITION TEST 4 FAILED" << std::endl;
    return false;
  } else {
    return true;
  }
}

bool Ray::CastTest() {
  Tuple ray_origin = TupleManager::Instance()->Point(0.0f, 0.0f, -5.0f);
  Tuple ray_direction = TupleManager::Instance()->Vector(0.0f, 0.0f, 1.0f);
  Ray test_ray(ray_origin, ray_direction);
  Sphere test_sphere(1);
  test_ray.Cast(test_sphere);
  if (!(Utility::FloatsAreEqual(test_ray.m_intersections[0].Time(), 4.0f) && Utility::FloatsAreEqual(test_ray.m_intersections[1].Time(), 6.0f))) {
    std::cout << "INTERSECTION TEST 1 FAILED" << std::endl;
    return false;
  }
  test_ray.m_intersections.clear();

  ray_origin = TupleManager::Instance()->Point(0.0f, 1.0f, -5.0f);
  test_ray = Ray(ray_origin, ray_direction);
  test_ray.Cast(test_sphere);
  if (!(Utility::FloatsAreEqual(test_ray.m_intersections[0].Time(), 5.0f) && Utility::FloatsAreEqual(test_ray.m_intersections[1].Time(), 5.0f))) {
    std::cout << "INTERSECTION TEST 2 FAILED" << std::endl;
    return false;
  }
  test_ray.m_intersections.clear();

  ray_origin = TupleManager::Instance()->Point(0.0f, 2.0f, -5.0f);
  test_ray = Ray(ray_origin, ray_direction);
  test_ray.Cast(test_sphere);
  if (!(test_ray.m_intersections.size() == 0)) {
    std::cout << "INTERSECTION TEST 3 FAILED" << std::endl;
    return false;
  }
  test_ray.m_intersections.clear();

  ray_origin = TupleManager::Instance()->Point(0.0f, 0.0f, 0.0f);
  test_ray = Ray(ray_origin, ray_direction);
  test_ray.Cast(test_sphere);
  if (!(Utility::FloatsAreEqual(test_ray.m_intersections[0].Time(), -1.0f) && Utility::FloatsAreEqual(test_ray.m_intersections[1].Time(), 1.0f))) {
    std::cout << "INTERSECTION TEST 4 FAILED" << std::endl;
    return false;
  }
  test_ray.m_intersections.clear();

  ray_origin = TupleManager::Instance()->Point(0.0f, 0.0f, 5.0f);
  test_ray = Ray(ray_origin, ray_direction);
  test_ray.Cast(test_sphere);
  if (!(Utility::FloatsAreEqual(test_ray.m_intersections[0].Time(), -6.0f) && Utility::FloatsAreEqual(test_ray.m_intersections[1].Time(), -4.0f))) {
    std::cout << "INTERSECTION TEST 5 FAILED" << std::endl;
    return false;
  }
  test_ray.m_intersections.clear();

  ray_origin = TupleManager::Instance()->Point(0.0f, 0.0f, -5.0f);
  ray_direction = TupleManager::Instance()->Vector(0.0f, 0.0f, 1.0f);
  test_ray = Ray(ray_origin, ray_direction);
  Matrix scaling = Matrix::ScalingMatrix(2.0f, 2.0f, 2.0f);
  test_sphere.SetTransform(scaling);
  test_ray.Cast(test_sphere);
  if (!(Utility::FloatsAreEqual(test_ray.m_intersections[0].Time(), 3.0f) && Utility::FloatsAreEqual(test_ray.m_intersections[1].Time(), 7.0f))) {
    std::cout << "INTERSECTION TEST 6 FAILED" << std::endl;
    return false;
  }
  test_ray.m_intersections.clear();

  Matrix translation = Matrix::TranslationMatrix(5.0f, 0.0f, 0.0f);
  test_sphere.SetTransform(translation);
  test_ray.Cast(test_sphere);
  if (!(test_ray.m_intersections.size() == 0)) {
    std::cout << "INTERSECTION TEST 7 FAILED" << std::endl;
    return false;
  } else {
    return true;
  }
}

bool Ray::HitTest() {
  Tuple ray_origin = TupleManager::Instance()->Point(0.0f, 0.0f, 0.0f);
  Tuple ray_direction = TupleManager::Instance()->Vector(0.0f, 0.0f, 1.0f);
  Ray test_ray(ray_origin, ray_direction);
  Sphere test_sphere(1);
  Intersection test_a_intersection(1.0f, test_sphere);
  Intersection test_b_intersection(2.0f, test_sphere);
  test_ray.m_intersections.push_back(test_b_intersection);
  test_ray.m_intersections.push_back(test_a_intersection);
  const Intersection* hit = test_ray.Hit();
  if (!(*hit == test_a_intersection)) {
    std::cout << "HIT TEST 1 FAILED" << std::endl;
    return false;
  }
  test_ray.m_intersections.clear();

  test_a_intersection.SetTime(1.0f);
  test_b_intersection.SetTime(1.0f);
  test_ray.m_intersections.push_back(test_b_intersection);
  test_ray.m_intersections.push_back(test_a_intersection);
  hit = test_ray.Hit();
  if (!(*hit == test_b_intersection)) {
    std::cout << "HIT TEST 2 FAILED" << std::endl;
    return false;
  }
  test_ray.m_intersections.clear();

  test_a_intersection.SetTime(-2.0f);
  test_b_intersection.SetTime(-1.0f);
  test_ray.m_intersections.push_back(test_b_intersection);
  test_ray.m_intersections.push_back(test_a_intersection);
  hit = test_ray.Hit();
  if (!(hit == nullptr)) {
    std::cout << "HIT TEST 3 FAILED" << std::endl;
    return false;
  }
  test_ray.m_intersections.clear();


  test_a_intersection.SetTime(5.0f);
  test_b_intersection.SetTime(7.0f);
  Intersection test_c_intersection(-3.0f, test_sphere);
  Intersection test_d_intersection(2.0f, test_sphere);
  test_ray.m_intersections.push_back(test_a_intersection);
  test_ray.m_intersections.push_back(test_b_intersection);
  test_ray.m_intersections.push_back(test_c_intersection);
  test_ray.m_intersections.push_back(test_d_intersection);
  hit = test_ray.Hit();
  if (!(*hit == test_d_intersection)) {
    std::cout << "HIT TEST 4 FAILED" << std::endl;
    return false;
  }
  test_ray.m_intersections.clear();

}

bool Ray::TransformTest() {
  Tuple ray_origin = TupleManager::Instance()->Point(1.0f, 2.0f, 3.0f);
  Tuple ray_direction = TupleManager::Instance()->Vector(0.0f, 1.0f, 0.0f);
  Tuple ray_origin_success = TupleManager::Instance()->Point(4.0f, 6.0f, 8.0f);
  Tuple ray_direction_success = TupleManager::Instance()->Vector(0.0f, 1.0f, 0.0f);
  Matrix translate = Matrix::TranslationMatrix(3.0f, 4.0f, 5.0f);
  Ray test_ray(ray_origin, ray_direction);
  Ray test_ray_success(ray_origin_success, ray_direction_success);
  Ray result = test_ray.Transform(translate);
  if (!(result == test_ray_success)) {
    std::cout << "RAY TRANSFORM TEST FAILED" << std::endl;
    return false;
  }

  Matrix scaling = Matrix::ScalingMatrix(2.0f, 3.0f, 4.0f);
  ray_origin_success = TupleManager::Instance()->Point(2.0f, 6.0f, 12.0f);
  ray_direction_success = TupleManager::Instance()->Vector(0.0f, 3.0f, 0.0f);
  test_ray_success = Ray(ray_origin_success, ray_direction_success);
  result = test_ray.Transform(scaling);
  if (!(result == test_ray_success)) {
    std::cout << "RAY TRANSFORM TEST 2 FAILED" << std::endl;
    return false;
  } else {
    return true;
  }
}
