#include "Light.hpp"

Light::Light()
  : m_position(Tuple(0.0f, 0.0f, 0.0f, 1.0f)), m_intensity(0.0f, 0.0f, 0.0f, 0.0f) {
}

Light::Light(Tuple& position, Tuple& intensity) 
  : m_position(position), m_intensity(intensity) {
}

Tuple& Light::Intensity() {
  return m_intensity;
}

Tuple& Light::Position() {
  return m_position;
}

void Light::SetIntensity(Tuple& intensity) {
  m_intensity = intensity;
}

void Light::SetPosition(Tuple& position) {
  m_position = position;
}
