#ifndef WORLD_H
#define WORLD_H
#include <vector>
#include "Light.hpp"
#include "Ray.hpp"
#include "SphereManager.hpp"
#include "TupleManager.hpp"
#include "MatrixUtil.hpp"
using namespace MatrixUtil;

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
  World(const std::vector<Sphere>& spheres, const Light& light);

  // GET
public:
  const Light& Lights() const;
  std::vector<Sphere>& Spheres();
  // ADDS
public:
  void SetLight(const Light& light);
  void AddSphere(const Sphere& sphere);

  // UTILITY
public:
  Tuple ColorAt(Ray& ray);
public:
  static void RunTest();
private:
  Light m_light;
  std::vector<Sphere> m_spheres;
private:
  // Can not be const.
  void CastRay(Ray& ray);
  std::unique_ptr<CompiledData> PrepareData(const Intersection& intersection, const Ray& ray);
  Tuple ShadeHit(const CompiledData& data) const;

private:
  static bool WorldCastTest();
  //static bool PrepareDataTest();
};
#endif // !WORLD_H
