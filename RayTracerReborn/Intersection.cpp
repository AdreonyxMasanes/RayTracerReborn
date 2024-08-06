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

bool Intersection::operator==(Intersection& rhs) {
  if(!(Time() == rhs.Time())) {
    return false;
  } else if (!(GetSphere() == rhs.GetSphere())) {
    return false;
  } else {
    return true;
  }
}

