#ifndef SPHERE_H
#define SPHERE_H
class Sphere {
public:
  Sphere();
  Sphere(int id);

public:
  int ID();
  bool operator==(Sphere& rhs);
public:
  //float* Intersect(Ray& ray);

public:
  //static void RunTest();
private:
  int m_id;

private:
  //static bool IntersectTest();
};
#endif // !SPHERE_H
