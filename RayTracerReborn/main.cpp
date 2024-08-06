#include "TupleManager.hpp"
#include "SphereManager.hpp"
#include "Ray.hpp"

#include "BulletSim.hpp"
#include "ClockSim.hpp"
#include "ShadowSim.hpp"

int main() {
  //SINGLETON TYPE IMPLEMENTATION
  TupleManager::Init();
  SphereManager::Init();
  //Tuple::RunTest();

  //TupleManager::CreationTest();

  //BulletSim::Run(false);
  //BulletSim::Run(true);
  //ClockSim::Run();
  //ShadowSim::Run(false);


  //Canvas::CanvasTest();

  //Matrix::RunTest();
  //Ray::RunTest();
  Sphere::RunTest();
  SphereManager::Shutdown();
  TupleManager::Shutdown();
  return 0;
}