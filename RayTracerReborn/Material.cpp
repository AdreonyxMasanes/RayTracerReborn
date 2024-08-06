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

void Material::RunTest() {
  if (!(LightingTest())) {
    return;
  } else {
    std::cout << "MATERIAL TEST PASSED" << std::endl;
    return;
  }
}

std::unique_ptr<Tuple> Material::Lighting(Light& light, Tuple& position_p, Tuple& eye_v, Tuple& normal_v) {
  std::unique_ptr<Tuple> effective_color = Color() * light.Intensity();
  std::unique_ptr<Tuple> light_v = (light.Position() - position_p)->Normalize();
  std::unique_ptr<Tuple> ambient = *effective_color * Ambient();

  std::unique_ptr<Tuple> diffuse;
  std::unique_ptr<Tuple> specular;
  
  float light_dot_normal = light_v->Dot(normal_v);

  if (light_dot_normal < 0) {
    diffuse = TupleManager::Instance()->Color(0.0f, 0.0f, 0.0f);
    specular = TupleManager::Instance()->Color(0.0f, 0.0f, 0.0f);
  } else {
    diffuse = *(*effective_color * Diffuse()) * light_dot_normal;
    std::unique_ptr<Tuple> reflect_v = -*light_v->Reflect(normal_v);
    float reflect_dot_eye = reflect_v->Dot(eye_v);
    if (reflect_dot_eye <= 0) {
      specular = TupleManager::Instance()->Color(0.0f, 0.0f, 0.0f);
    } else {
      float factor = powf(reflect_dot_eye, Shininess());
      specular = *(light.Intensity() * Specular()) * factor;
    }
  }
  return *(*ambient + *diffuse) + *specular;
}

bool Material::LightingTest() {
  Material default_material;
  std::unique_ptr<Tuple> position = TupleManager::Instance()->Point(0.0f, 0.0f, 0.0f);

  std::unique_ptr<Tuple> eye_v = TupleManager::Instance()->Vector(0.0f, 0.0f, -1.0f);
  std::unique_ptr<Tuple> normal_v = TupleManager::Instance()->Vector(0.0f, 0.0f, -1.0f);

  std::unique_ptr<Tuple> light_pos = TupleManager::Instance()->Point(0.0f, 0.0f, -10.0f);
  std::unique_ptr<Tuple> light_color = TupleManager::Instance()->Color(1.0f, 1.0f, 1.0f);
  Light test_light(*light_pos, *light_color);
  std::unique_ptr<Tuple> result = default_material.Lighting(test_light, *position, *eye_v, *normal_v);
  std::unique_ptr<Tuple> test_success_color = TupleManager::Instance()->Color(1.9f, 1.9f, 1.9f);
  if (!(*result == *test_success_color)) {
    std::cout << "LIGHTING TEST FAILED" << std::endl;
    return false;
  }

  eye_v = TupleManager::Instance()->Vector(0.0f, sqrtf(2.0f) / 2.0f, -sqrtf(2) / 2.0f);
  normal_v = TupleManager::Instance()->Vector(0.0f, 0.0f, -1.0f);

  light_pos = TupleManager::Instance()->Point(0.0f, 0.0f, -10.0f);
  light_color = TupleManager::Instance()->Color(1.0f, 1.0f, 1.0f);
  test_light = Light(*light_pos, *light_color);
  result = default_material.Lighting(test_light, *position, *eye_v, *normal_v);
  test_success_color = TupleManager::Instance()->Color(1.0f, 1.0f, 1.0f);
  if (!(*result == *test_success_color)) {
    std::cout << "LIGHTING TEST 2 FAILED" << std::endl;
    return false;
  }

  eye_v = TupleManager::Instance()->Vector(0.0f, 0.0f, -1.0f);
  normal_v = TupleManager::Instance()->Vector(0.0f, 0.0f, -1.0f);

  light_pos = TupleManager::Instance()->Point(0.0f, 10.0f, -10.0f);
  light_color = TupleManager::Instance()->Color(1.0f, 1.0f, 1.0f);
  test_light = Light(*light_pos, *light_color);
  result = default_material.Lighting(test_light, *position, *eye_v, *normal_v);
  test_success_color = TupleManager::Instance()->Color(0.7364f, 0.7364f, 0.7364f);
  if (!(*result == *test_success_color)) {
    std::cout << "LIGHTING TEST 3 FAILED" << std::endl;
    return false;
  }

  eye_v = TupleManager::Instance()->Vector(0.0f, -sqrtf(2.0f) / 2.0f, -sqrtf(2.0f) / 2.0f);
  normal_v = TupleManager::Instance()->Vector(0.0f, 0.0f, -1.0f);

  light_pos = TupleManager::Instance()->Point(0.0f, 10.0f, -10.0f);
  light_color = TupleManager::Instance()->Color(1.0f, 1.0f, 1.0f);
  test_light = Light(*light_pos, *light_color);
  result = default_material.Lighting(test_light, *position, *eye_v, *normal_v);
  test_success_color = TupleManager::Instance()->Color(1.6364f, 1.6364f, 1.6364f);
  if (!(*result == *test_success_color)) {
    std::cout << "LIGHTING TEST 4 FAILED" << std::endl;
    return false;
  }

  eye_v = TupleManager::Instance()->Vector(0.0f, 0.0f, -1.0f);
  normal_v = TupleManager::Instance()->Vector(0.0f, 0.0f, -1.0f);

  light_pos = TupleManager::Instance()->Point(0.0f, 0.0f, 10.0f);
  light_color = TupleManager::Instance()->Color(1.0f, 1.0f, 1.0f);
  test_light = Light(*light_pos, *light_color);
  result = default_material.Lighting(test_light, *position, *eye_v, *normal_v);
  test_success_color = TupleManager::Instance()->Color(0.1f, 0.1f, 0.1f);
  if (!(*result == *test_success_color)) {
    std::cout << "LIGHTING TEST 5 FAILED" << std::endl;
    return false;
  } else {
    return true;
  }
}
