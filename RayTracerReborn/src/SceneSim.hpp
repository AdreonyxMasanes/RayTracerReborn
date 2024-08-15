#ifndef SCENE_SIM_H
#define SCENE_SIM_H
#include "chrono"
#include "World.hpp"
#include "Camera.hpp"
#include "PPM.hpp"



namespace SceneSim {
  void Run(std::vector<Sphere>& spheres);
}
#endif // !SCENE_SIM_H
