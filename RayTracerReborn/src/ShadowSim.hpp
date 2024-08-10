#ifndef SHADOW_SIM_H
#define SHADOW_SIM_H
#include <chrono>
#include "SphereManager.hpp"
#include "TupleManager.hpp"
#include "Ray.hpp"
#include "Canvas.hpp"
#include "PPM.hpp"

namespace ShadowSim {
  void Run(bool shading);
};
#endif // !SHADOW_SIM_H
