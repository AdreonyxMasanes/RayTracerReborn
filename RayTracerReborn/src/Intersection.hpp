#ifndef INTERSECTION_H
#define INTERSECTION_H
#include "Sphere.hpp"
class Intersection {
public:
  Intersection();
  Intersection(float time, Sphere& sphere);

  // GETS
public:
  float Time();
  Sphere& GetSphere();

  // SETS
public:
  void SetTime(float time);
  void SetSphere(Sphere& sphere);

  //Utility
public:
  bool operator==(Intersection& rhs);
  void operator=(Intersection& rhs);
private:
  float m_time = 0;
  Sphere m_sphere;
};
#endif // !INTERSECTION_H