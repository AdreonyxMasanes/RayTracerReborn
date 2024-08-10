#ifndef RAY_H
#define RAY_H
#include "TupleManager.hpp"
#include "Sphere.hpp"
#include "Intersection.hpp"
#include "Matrix.hpp"
#include <vector>

class Ray {
public:
  Ray();
  Ray(const Tuple& origin_p, const Tuple& direction_v);
  // GETS
public:
  const Tuple& Origin() const;
  const Tuple& Direction() const;
  const std::vector<Intersection>& Intersections() const;
  std::vector<Intersection>& ModifyIntersections();
  // UTILITY
public:
  Tuple Position(float time) const;
  void Cast(const Sphere& sphere);
  void SortIntersections();
  const Intersection* Hit() const;
  Ray Transform(const Matrix& transform) const;
  bool operator==(const Ray& rhs) const;

public:
  static void RunTest();
private:
  Tuple m_origin_p;
  Tuple m_direction_v;
  std::vector<Intersection> m_intersections;
private:


  static bool PositionTest();
  static bool CastTest();
  static bool HitTest();
  static bool TransformTest();
};

#endif // !RAY_H
