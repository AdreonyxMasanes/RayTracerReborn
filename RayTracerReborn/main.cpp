#include "TupleManager.hpp"
#include "BulletSim.hpp"
#include "Canvas.hpp"
int main() {
  TupleManager::Init();
  //Tuple::RunTest();
  // SINGLETON TYPE IMPLEMENTATION

  //TupleManager::CreationTest();
  //BulletSim::Run(false);
  //BulletSim::Run(true);

  //Canvas::CanvasTest();

  TupleManager::Shutdown();
  return 0;
}