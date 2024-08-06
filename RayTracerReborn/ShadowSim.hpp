#ifndef SHADOW_SIM_H
#define SHADOW_SIM_H
#include "SphereManager.hpp"
#include "TupleManager.hpp"
#include "Ray.hpp"
#include "Canvas.hpp"
#include "PPM.hpp"

class ShadowSim {
public:
  static void Run(bool shading);
};
#endif // !SHADOW_SIM_H
