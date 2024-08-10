#ifndef INTERSECTION_H
#define INTERSECTION_H
#include "Sphere.hpp"
class Intersection {
public:
  Intersection();
  Intersection(float time, const Sphere& sphere);

  // GETS
public:
  float Time() const ;
  const Sphere& GetSphere() const;

  // SETS
public:
  void SetTime(float time);
  void SetSphere(const Sphere& sphere);

  //Utility
public:
  bool operator==(const Intersection& rhs) const;
  void operator=(const Intersection& rhs);
private:
  float m_time = 0;
  Sphere m_sphere;
};
#endif // !INTERSECTION_H