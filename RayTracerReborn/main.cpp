#include "TupleManager.hpp"
#include "BulletSim.hpp"
#include "Canvas.hpp"
int main() {
  Tuple::RunTest();
  // SINGLETON TYPE IMPLEMENTATION
  TupleManager::Init();
  TupleManager::CreationTest();
  // BulletSim::Run();

  Canvas::CanvasTest();

  TupleManager::Shutdown();
  return 0;
}