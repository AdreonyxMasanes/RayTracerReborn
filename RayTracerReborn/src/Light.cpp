#include "Light.hpp"

Light::Light()
  : m_position(Tuple(0.0f, 0.0f, 0.0f, 1.0f)), m_intensity(0.0f, 0.0f, 0.0f, 0.0f) {
}

Light::Light(const Tuple& position, const Tuple& intensity) 
  : m_position(position), m_intensity(intensity) {
}

const Tuple& Light::Intensity() const{
  return m_intensity;
}

const Tuple& Light::Position() const {
  return m_position;
}

void Light::SetIntensity(Tuple& intensity) {
  m_intensity = intensity;
}

void Light::SetPosition(Tuple& position) {
  m_position = position;
}
