#ifndef RAY_H
#define RAY_H
#include "TupleManager.hpp"
#include "Sphere.hpp"
#include "Intersection.hpp"
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
public:
  std::unique_ptr<Tuple> Position(float time);
  void Cast(Sphere& sphere);
public:
  static void RunTest();
private:
  Tuple m_origin_p;
  Tuple m_direction_v;
  std::vector<Intersection> m_intersections;
private:
  static bool PositionTest();
  static bool CastTest();
};

#endif // !RAY_H
