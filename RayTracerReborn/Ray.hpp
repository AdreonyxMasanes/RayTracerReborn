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
  Ray(Tuple& origin_p, Tuple& direction_v);
  // GETS
public:
  Tuple& Origin();
  Tuple& Direction();
  std::vector<Intersection>& Intersections();
  // UTILITY
public:
  std::unique_ptr<Tuple> Position(float time);
  void Cast(Sphere& sphere);
  void SortIntersections();
  Intersection* Hit();
  Ray Transform(Matrix& transform);
  bool operator==(Ray& rhs);

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
