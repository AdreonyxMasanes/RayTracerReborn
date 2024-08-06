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

std::vector<Intersection>& Ray::Intersections() {
  return m_intersections;
}

std::unique_ptr<Tuple> Ray::Position(float time) {
  return Origin() + *(Direction() * time);
}

void Ray::Cast(Sphere& sphere) {
  std::unique_ptr<Ray> transformed_ray = Transform(*(sphere.Transform().Invert()));
  
  std::unique_ptr<Tuple> world_origin = TupleManager::Instance()->Point(0.0f, 0.0f, 0.0f);

  std::unique_ptr<Tuple> sphere_to_ray = transformed_ray->Origin() - *world_origin;

  float a = transformed_ray->Direction().Dot(transformed_ray->Direction());
  float b = 2 * transformed_ray->Direction().Dot(*sphere_to_ray);
  float c = sphere_to_ray->Dot(*sphere_to_ray) - 1;
  float discriminant = powf(b, 2) - 4 * a * c;

  if (!(discriminant < 0)) {
    m_intersections.push_back(Intersection((-b - sqrtf(discriminant)) / (2 * a), sphere));
    m_intersections.push_back(Intersection((-b + sqrtf(discriminant)) / (2 * a), sphere));
  }
}

std::unique_ptr<Intersection> Ray::Hit() {
  // SORT LOW TO HIGH
  bool isSorted = false;
  while (!isSorted) {
    for (int i = 0; i < Intersections().size(); i++) {
      if (!(i == Intersections().size() - 1)) {
        if (Intersections().at(i).Time() > Intersections().at(i + 1).Time()) {
          Intersection temp = Intersections().at(i);
          Intersections().at(i) = Intersections().at(i + 1);
          Intersections().at(i + 1) = temp;
          break;
        }
      } else {
        isSorted = true;
      }
    }
  }

  // WHILE SORTING JUST POP A VALUE IF IT IS NEGATIVE THEN CAN JUST RETURN INTERSECTIONS[0]
  // since it is sorted, returns the first non negative value.
  for (auto& intersection : Intersections()) {
    if (intersection.Time() >= 0) {
      return std::make_unique<Intersection>(intersection);
    }
  }
  return nullptr;
}

std::unique_ptr<Ray> Ray::Transform(Matrix& transform) {
  return std::make_unique<Ray>(*(transform * Origin()), *(transform * Direction()));
}

bool Ray::operator==(Ray& rhs) {
  if (!(Origin() == rhs.Origin())) {
    return false;
  } else if (!(Direction() == rhs.Direction())) {
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
  test_ray.Cast(test_sphere);
  if (!(Utility::FloatsAreEqual(test_ray.Intersections()[0].Time(), 4.0f) && Utility::FloatsAreEqual(test_ray.Intersections()[1].Time(), 6.0f))) {
    std::cout << "INTERSECTION TEST 1 FAILED" << std::endl;
    return false;
  }
  test_ray.Intersections().clear();

  ray_origin = TupleManager::Instance()->Point(0.0f, 1.0f, -5.0f);
  test_ray = Ray(*ray_origin, *ray_direction);
  test_ray.Cast(test_sphere);
  if (!(Utility::FloatsAreEqual(test_ray.Intersections()[0].Time(), 5.0f) && Utility::FloatsAreEqual(test_ray.Intersections()[1].Time(), 5.0f))) {
    std::cout << "INTERSECTION TEST 2 FAILED" << std::endl;
    return false;
  }
  test_ray.Intersections().clear();

  ray_origin = TupleManager::Instance()->Point(0.0f, 2.0f, -5.0f);
  test_ray = Ray(*ray_origin, *ray_direction);
  test_ray.Cast(test_sphere);
  if (!(test_ray.Intersections().size() == 0)) {
    std::cout << "INTERSECTION TEST 3 FAILED" << std::endl;
    return false;
  }
  test_ray.Intersections().clear();

  ray_origin = TupleManager::Instance()->Point(0.0f, 0.0f, 0.0f);
  test_ray = Ray(*ray_origin, *ray_direction);
  test_ray.Cast(test_sphere);
  if (!(Utility::FloatsAreEqual(test_ray.Intersections()[0].Time(), -1.0f) && Utility::FloatsAreEqual(test_ray.Intersections()[1].Time(), 1.0f))) {
    std::cout << "INTERSECTION TEST 4 FAILED" << std::endl;
    return false;
  }
  test_ray.Intersections().clear();

  ray_origin = TupleManager::Instance()->Point(0.0f, 0.0f, 5.0f);
  test_ray = Ray(*ray_origin, *ray_direction);
  test_ray.Cast(test_sphere);
  if (!(Utility::FloatsAreEqual(test_ray.Intersections()[0].Time(), -6.0f) && Utility::FloatsAreEqual(test_ray.Intersections()[1].Time(), -4.0f))) {
    std::cout << "INTERSECTION TEST 5 FAILED" << std::endl;
    return false;
  }
  test_ray.Intersections().clear();

  ray_origin = TupleManager::Instance()->Point(0.0f, 0.0f, -5.0f);
  ray_direction = TupleManager::Instance()->Vector(0.0f, 0.0f, 1.0f);
  test_ray = Ray(*ray_origin, *ray_direction);
  std::unique_ptr<Matrix> scaling = Matrix::ScalingMatrix(2.0f, 2.0f, 2.0f);
  test_sphere.SetTransform(*scaling);
  test_ray.Cast(test_sphere);
  if (!(Utility::FloatsAreEqual(test_ray.Intersections()[0].Time(), 3.0f) && Utility::FloatsAreEqual(test_ray.Intersections()[1].Time(), 7.0f))) {
    std::cout << "INTERSECTION TEST 6 FAILED" << std::endl;
    return false;
  }
  test_ray.Intersections().clear();

  std::unique_ptr<Matrix> translation = Matrix::TranslationMatrix(5.0f, 0.0f, 0.0f);
  test_sphere.SetTransform(*translation);
  test_ray.Cast(test_sphere);
  if (!(test_ray.Intersections().size() == 0)) {
    std::cout << "INTERSECTION TEST 7 FAILED" << std::endl;
    return false;
  } else {
    return true;
  }
}

bool Ray::HitTest() {
  std::unique_ptr<Tuple> ray_origin = TupleManager::Instance()->Point(0.0f, 0.0f, 0.0f);
  std::unique_ptr<Tuple> ray_direction = TupleManager::Instance()->Vector(0.0f, 0.0f, 1.0f);
  Ray test_ray(*ray_origin, *ray_direction);
  Sphere test_sphere(1);
  Intersection test_a_intersection(1.0f, test_sphere);
  Intersection test_b_intersection(2.0f, test_sphere);
  test_ray.Intersections().push_back(test_b_intersection);
  test_ray.Intersections().push_back(test_a_intersection);
  std::unique_ptr<Intersection> hit = test_ray.Hit();
  if (!(*hit == test_a_intersection)) {
    std::cout << "HIT TEST 1 FAILED" << std::endl;
    return false;
  }
  test_ray.Intersections().clear();

  test_a_intersection.SetTime(1.0f);
  test_b_intersection.SetTime(1.0f);
  test_ray.Intersections().push_back(test_b_intersection);
  test_ray.Intersections().push_back(test_a_intersection);
  hit = test_ray.Hit();
  if (!(*hit == test_b_intersection)) {
    std::cout << "HIT TEST 2 FAILED" << std::endl;
    return false;
  }
  test_ray.Intersections().clear();

  test_a_intersection.SetTime(-2.0f);
  test_b_intersection.SetTime(-1.0f);
  test_ray.Intersections().push_back(test_b_intersection);
  test_ray.Intersections().push_back(test_a_intersection);
  hit = test_ray.Hit();
  if (!(hit == nullptr)) {
    std::cout << "HIT TEST 3 FAILED" << std::endl;
    return false;
  }
  test_ray.Intersections().clear();


  test_a_intersection.SetTime(5.0f);
  test_b_intersection.SetTime(7.0f);
  Intersection test_c_intersection(-3.0f, test_sphere);
  Intersection test_d_intersection(2.0f, test_sphere);
  test_ray.Intersections().push_back(test_a_intersection);
  test_ray.Intersections().push_back(test_b_intersection);
  test_ray.Intersections().push_back(test_c_intersection);
  test_ray.Intersections().push_back(test_d_intersection);
  hit = test_ray.Hit();
  if (!(*hit == test_d_intersection)) {
    std::cout << "HIT TEST 4 FAILED" << std::endl;
    return false;
  }
  test_ray.Intersections().clear();

}

bool Ray::TransformTest() {
  std::unique_ptr<Tuple> ray_origin = TupleManager::Instance()->Point(1.0f, 2.0f, 3.0f);
  std::unique_ptr<Tuple> ray_direction = TupleManager::Instance()->Vector(0.0f, 1.0f, 0.0f);
  std::unique_ptr<Tuple> ray_origin_success = TupleManager::Instance()->Point(4.0f, 6.0f, 8.0f);
  std::unique_ptr<Tuple> ray_direction_success = TupleManager::Instance()->Vector(0.0f, 1.0f, 0.0f);
  std::unique_ptr<Matrix> translate = Matrix::TranslationMatrix(3.0f, 4.0f, 5.0f);
  Ray test_ray(*ray_origin, *ray_direction);
  Ray test_ray_success(*ray_origin_success, *ray_direction_success);
  std::unique_ptr<Ray> result = test_ray.Transform(*translate);
  if (!(*result == test_ray_success)) {
    std::cout << "RAY TRANSFORM TEST FAILED" << std::endl;
    return false;
  }

  std::unique_ptr<Matrix> scaling = Matrix::ScalingMatrix(2.0f, 3.0f, 4.0f);
  ray_origin_success = TupleManager::Instance()->Point(2.0f, 6.0f, 12.0f);
  ray_direction_success = TupleManager::Instance()->Vector(0.0f, 3.0f, 0.0f);
  test_ray_success = Ray(*ray_origin_success, *ray_direction_success);
  result = test_ray.Transform(*scaling);
  if (!(*result == test_ray_success)) {
    std::cout << "RAY TRANSFORM TEST 2 FAILED" << std::endl;
    return false;
  } else {
    return true;
  }
}
