#ifndef WORLD_H
#define WORLD_H
#include <vector>
#include "Light.hpp"
#include "Ray.hpp"
#include "SphereManager.hpp"
#include "TupleManager.hpp"

class World {
public:
  World();

  // GET
public:
  const std::vector<Light>& Lights() const;
  const std::vector<Sphere>& Spheres() const;
  // ADDS
public:
  void AddLight(Light& light);
  void AddSphere(Sphere& sphere);

  // UTILITY
public:
  void CastRay(Ray& ray);
public:
  static void RunTest();
private:
  std::vector<Light> m_lights;
  std::vector<Sphere> m_spheres;
private:
  static bool WorldCastTest();
};
#endif // !WORLD_H
