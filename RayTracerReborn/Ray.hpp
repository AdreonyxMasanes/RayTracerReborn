#ifndef RAY_H
#define RAY_H
#include "TupleManager.hpp"
#include "Sphere.hpp"
#include "Intersection.hpp"

class Ray {
public:
  Ray();
  Ray(Tuple& origin_p, Tuple& direction_v);
  // GETS
public:
  Tuple& Origin();
  Tuple& Direction();
public:
  std::unique_ptr<Tuple> Position(float time);
  Intersection* Cast(Sphere& sphere);
public:
  static void RunTest();
private:
  Tuple m_origin_p;
  Tuple m_direction_v;
private:
  static bool PositionTest();
  static bool CastTest();
};

#endif // !RAY_H
