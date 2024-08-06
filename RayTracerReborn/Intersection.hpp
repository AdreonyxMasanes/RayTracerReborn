#ifndef INTERSECTION_H
#define INTERSECTION_H
#include "Sphere.hpp"
class Intersection {
public:
  Intersection();
  Intersection(float time, Sphere& sphere);

public:
  float Time();
  Sphere& GetSphere();
  bool operator==(Intersection& rhs);
private:
  float m_time = 0;
  Sphere m_sphere;
};
#endif // !INTERSECTION_H