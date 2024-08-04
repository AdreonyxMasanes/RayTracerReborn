#include "TupleManager.hpp"
#include "BulletSim.hpp"

int main() {
  Tuple::RunTest();
  // SINGLETON TYPE IMPLEMENTATION
  TupleManager::Init();
  TupleManager::CreationTest();
  // BulletSim::Run();

  TupleManager::Shutdown();
  return 0;
}