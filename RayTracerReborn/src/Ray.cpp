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
