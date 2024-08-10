#include "Intersection.hpp"

Intersection::Intersection() 
  : m_time(0), m_sphere(Sphere()) {
}

Intersection::Intersection(float time, const Sphere& sphere) 
  : m_time(time), m_sphere(sphere) {
}

float Intersection::Time() const {
  return m_time;
}

const Sphere& Intersection::GetSphere() const {
  return m_sphere;
}

void Intersection::SetTime(float time) {
  m_time = time;
}

void Intersection::SetSphere(const Sphere& sphere) {
  m_sphere = sphere;
}

bool Intersection::operator==(const Intersection& rhs) const {
  if(!(m_time == rhs.Time())) {
    return false;
  } else if (!(m_sphere == rhs.GetSphere())) {
    return false;
  } else {
    return true;
  }
}

void Intersection::operator=(const Intersection& rhs) {
  SetTime(rhs.Time());
  SetSphere(rhs.GetSphere());
}

