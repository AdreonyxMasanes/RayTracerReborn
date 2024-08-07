#include "TupleManager.hpp"
#include "SphereManager.hpp"
#include "Ray.hpp"
#include "Material.hpp"
#include "World.hpp"

#include "BulletSim.hpp"
#include "ClockSim.hpp"
#include "ShadowSim.hpp"

int main() {
  //SINGLETON TYPE IMPLEMENTATION
  TupleManager::Init();
  SphereManager::Init();




  //BulletSim::Run(false);
  //BulletSim::Run(true);
  //ClockSim::Run();
  //ShadowSim::Run(false);
  //ShadowSim::Run(true);

  //Tuple::RunTest();
  //TupleManager::CreationTest();
  //Canvas::CanvasTest();
  Matrix::RunTest();
  //Ray::RunTest();
  //Sphere::RunTest();
  //Material::RunTest();
  //World::RunTest();
  SphereManager::Shutdown();
  TupleManager::Shutdown();
  return 0;
}