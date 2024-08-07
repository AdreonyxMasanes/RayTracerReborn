#ifndef WORLD_H
#define WORLD_H
#include <vector>
#include "Light.hpp"
#include "Ray.hpp"
#include "SphereManager.hpp"
#include "TupleManager.hpp"

struct CompiledData {
  float m_time;
  Sphere m_sphere;
  Tuple m_point_p;
  Tuple m_eye_v;
  Tuple m_normal_v;
  bool m_inside_sphere;
};

class World {
public:
  World();
  World(std::vector<Sphere>& spheres, Light& light);

  // GET
public:
  const Light& Lights() const;
  std::vector<Sphere>& Spheres();
  // ADDS
public:
  void SetLight(Light& light);
  void AddSphere(Sphere& sphere);

  // UTILITY
public:
  std::unique_ptr<Tuple> ColorAt(Ray& ray);
public:
  static void RunTest();
private:
  Light m_light;
  std::vector<Sphere> m_spheres;
private:
  void CastRay(Ray& ray);
  std::unique_ptr<CompiledData> PrepareData(Intersection& intersection, Ray& ray);
  std::unique_ptr<Tuple> ShadeHit(CompiledData& data);

private:
  static bool WorldCastTest();
  //static bool PrepareDataTest();
};
#endif // !WORLD_H
