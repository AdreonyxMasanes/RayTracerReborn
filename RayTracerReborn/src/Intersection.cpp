#include "Intersection.hpp"

Intersection::Intersection() 
  : m_time(0), m_sphere(Sphere()) {
}

Intersection::Intersection(float time, Sphere& sphere) 
  : m_time(time), m_sphere(sphere) {
}

float Intersection::Time() {
  return m_time;
}

Sphere& Intersection::GetSphere() {
  return m_sphere;
}

void Intersection::SetTime(float time) {
  m_time = time;
}

void Intersection::SetSphere(Sphere& sphere) {
  m_sphere = sphere;
}

bool Intersection::operator==(Intersection& rhs) {
  if(!(Time() == rhs.Time())) {
    return false;
  } else if (!(GetSphere() == rhs.GetSphere())) {
    return false;
  } else {
    return true;
  }
}

void Intersection::operator=(Intersection& rhs) {
  SetTime(rhs.Time());
  SetSphere(rhs.GetSphere());
}

