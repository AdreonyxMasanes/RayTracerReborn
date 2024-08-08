#ifndef MATERIAL_H
#define MATERIAL_H
#include "TupleManager.hpp"
#include "Light.hpp"
class Material {
public:
  Material();
  Material(float ambient, float diffuse, float specular, float shininess, Tuple& color);
public:
  float Ambient();
  float Diffuse();
  float Specular();
  float Shininess();
  Tuple& Color();

public:
  void SetAmbient(float ambient);
  void SetDiffuse(float diffuse);
  void SetSpecular(float specular);
  void SetShininess(float shininess);
  void SetColor(Tuple& color);

public:
  static void RunTest();
public:
  Tuple Lighting(Light& light, Tuple& position_p, Tuple& eye_v, Tuple& normal_v);
private:
  float m_ambient = 0.1f;
  float m_diffuse = 0.9f;
  float m_specular = 0.9f;
  float m_shininess = 200.0f;
  Tuple m_color = Tuple(1.0f, 1.0f, 1.0f, 0.0f);

private:
  static bool LightingTest();
};
#endif // !MATERIAL_H
