#ifndef SPHERE_H
#define SPHERE_H
#include "Matrix.hpp"
#include "Material.hpp"
class Sphere {
public:
  Sphere();
  Sphere(int id);

  // GETS
public:
  int ID();
  Matrix& Transform();
  Material& GetMaterial();
  
  // UTILTIY
public:
  bool operator==(Sphere& rhs);
  void operator=(Sphere& rhs);
  std::unique_ptr<Tuple> NormalAt(Tuple& world_point);
  
  // SETS
public:
  void SetTransform(Matrix& transform);
  void SetID(int ID);
  void SetMaterial(Material& material);

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
