#ifndef LIGHT_H
#define LIGHT_H
#include "TupleManager.hpp"
class Light {
public:
  Light();
  Light(Tuple& position, Tuple& intensity);

public:
  Tuple& Intensity();
  Tuple& Position();
public:
  void SetIntensity(Tuple& intensity);
  void SetPosition(Tuple& position);
private:
  Tuple m_intensity;
  Tuple m_position;
};
#endif // !LIGHT_H
