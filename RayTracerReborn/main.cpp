#include "TupleManager.hpp"


int main() {
  Tuple::RunTest();
  // SINGLETON TYPE IMPLEMENTATION
  TupleManager::Init();

  TupleManager::CreationTest();

  TupleManager::Shutdown();
  return 0;
}