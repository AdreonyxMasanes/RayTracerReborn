#ifndef SPHERE_H
#define SPHERE_H
#include "MatrixUtil.hpp"
#include "Material.hpp"
using namespace MatrixUtil;
class Sphere {
public:
  Sphere();
  Sphere(int id);

  // GETS
public:
  int ID() const;
  const Matrix& Transform() const;
  const Material& GetMaterial() const;
  
  Matrix& ModifyTransform();
  Material& ModifyMaterial();
  // UTILTIY
public:
  bool operator==(const Sphere& rhs) const;
  void operator=(const Sphere& rhs);
  Tuple NormalAt(const Tuple& world_point) const;
  
  // SETS
public:
  void SetTransform(const Matrix& transform);
  void SetID(int ID);
  void SetMaterial(const Material& material);

public:
  //float* Intersect(Ray& ray);

public:
  static void RunTest();
private:
  int m_id;
  Matrix m_transform;
  Material m_material;
private:
  static bool NormalAtTest();
  //static bool IntersectTest();
};
#endif // !SPHERE_H
