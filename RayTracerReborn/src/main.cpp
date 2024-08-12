#include "TupleManager.hpp"
#include "SphereManager.hpp"
#include "Ray.hpp"
#include "Material.hpp"
#include "World.hpp"
#include "Camera.hpp"

#include "BulletSim.hpp"
#include "ClockSim.hpp"
#include "ShadowSim.hpp"
#include "SceneSim.hpp"

int main() {
  //SINGLETON TYPE IMPLEMENTATION
  TupleManager::Init();
  SphereManager::Init();


  SceneSim::Run();
  
  
  SphereManager::Shutdown();
  TupleManager::Shutdown();
  return 0;
}