#ifndef LIGHT_H
#define LIGHT_H
#include "TupleManager.hpp"
class Light {
public:
  Light();
  Light(const Tuple& position, const Tuple& intensity);

public:
  const Tuple& Intensity() const;
  const Tuple& Position() const;
public:
  void SetIntensity(Tuple& intensity);
  void SetPosition(Tuple& position);
private:
  Tuple m_intensity;
  Tuple m_position;
};
#endif // !LIGHT_H
