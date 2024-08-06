#ifndef SPHERE_H
#define SPHERE_H
#include "Ray.hpp"
class Sphere {
public:
  Sphere(int id);

public:
  int ID();

public:
  float* Intersect(Ray& ray);

public:
  static void RunTest();
private:
  int m_id;

private:
  static bool IntersectTest();
};
#endif // !SPHERE_H
