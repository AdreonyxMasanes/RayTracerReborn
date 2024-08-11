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




  //BulletSim::Run(false);
  //BulletSim::Run(true);
  ClockSim::Run();
  //ShadowSim::Run(false);
  //ShadowSim::Run(true);
  //SceneSim::Run();

  //Tuple::RunTest();
  //TupleManager::CreationTest();
  //Canvas::CanvasTest();
  //Matrix::RunTest();
  //Ray::RunTest();
  //Sphere::RunTest();
  //Material::RunTest();
  //World::RunTest();
  //Camera::RunTest();
  
  
  SphereManager::Shutdown();
  TupleManager::Shutdown();
  return 0;
}