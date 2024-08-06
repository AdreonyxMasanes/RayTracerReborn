#include "TupleManager.hpp"
#include "BulletSim.hpp"
#include "ClockSim.hpp"
#include "Ray.hpp"
#include "Sphere.hpp"
int main() {
  //SINGLETON TYPE IMPLEMENTATION
  TupleManager::Init();

  //Tuple::RunTest();

  //TupleManager::CreationTest();

  //BulletSim::Run(false);
  //BulletSim::Run(true);
  //ClockSim::Run();

  //Canvas::CanvasTest();

  //Matrix::RunTest();
  Ray::RunTest();
  TupleManager::Shutdown();
  return 0;
}