#include "Material.hpp"

Material::Material() {
}

Material::Material(float ambient, float diffuse, float specular, float shininess, Tuple& color) 
  :m_ambient(ambient), m_diffuse(diffuse), m_specular(specular), m_shininess(shininess), m_color(color) {
}

float Material::Ambient() {
  return m_ambient;
}

float Material::Diffuse() {
  return m_diffuse;
}

float Material::Specular() {
  return m_specular;
}

float Material::Shininess() {
  return m_shininess;
}

Tuple& Material::Color() {
  return m_color;
}

void Material::SetAmbient(float ambient) {
  m_ambient = ambient;
}

void Material::SetDiffuse(float diffuse) {
  m_diffuse = diffuse;
}

void Material::SetSpecular(float specular) {
  m_specular = specular;
}

void Material::SetShininess(float shininess) {
  m_shininess = shininess;
}

void Material::SetColor(Tuple& color) {
  m_color = color;
}

Tuple Material::Lighting(Light& light, Tuple& position_p, Tuple& eye_v, Tuple& normal_v) {
  Tuple effective_color = Color() * light.Intensity();
  Tuple light_v = (light.Position() - position_p).Normalize();
  Tuple ambient = effective_color * Ambient();

  Tuple diffuse;
  Tuple specular;
  
  float light_dot_normal = light_v.Dot(normal_v);

  if (light_dot_normal < 0) {
    diffuse = TupleManager::Instance()->Color(0.0f, 0.0f, 0.0f);
    specular = TupleManager::Instance()->Color(0.0f, 0.0f, 0.0f);
  } else {
    diffuse = (effective_color * Diffuse()) * light_dot_normal;
    Tuple negated_light_v = -light_v;
    Tuple reflect_v = negated_light_v.Reflect(normal_v);
    float reflect_dot_eye = reflect_v.Dot(eye_v);
    if (reflect_dot_eye <= 0) {
      specular = TupleManager::Instance()->Color(0.0f, 0.0f, 0.0f);
    } else {
      float factor = powf(reflect_dot_eye, Shininess());
      specular = (light.Intensity() * Specular()) * factor;
    }
  }
  Tuple result = (ambient + diffuse) + specular;
  return result;
}

