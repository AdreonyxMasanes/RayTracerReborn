#ifndef MATERIAL_H
#define MATERIAL_H
#include "TupleManager.hpp"
#include "Light.hpp"
class Material {
public:
  Material();
  Material(float ambient, float diffuse, float specular, float shininess, const Tuple& color);
public:
  float Ambient() const;
  float Diffuse() const;
  float Specular() const;
  float Shininess() const;
  const Tuple& Color() const;

public:
  void SetAmbient(float ambient);
  void SetDiffuse(float diffuse);
  void SetSpecular(float specular);
  void SetShininess(float shininess);
  void SetColor(const Tuple& color);

public:
  Tuple Lighting(const Light& light, const Tuple& position_p, const Tuple& eye_v, const Tuple& normal_v) const;
private:
  float m_ambient = 0.1f;
  float m_diffuse = 0.9f;
  float m_specular = 0.9f;
  float m_shininess = 200.0f;
  Tuple m_color = Tuple(1.0f, 1.0f, 1.0f, 0.0f);

};
#endif // !MATERIAL_H
