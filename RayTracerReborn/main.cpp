#include "TupleManager.hpp"


int main() {
  Tuple::RunTest();
  TupleManager::Init();

  TupleManager::CreationTest();

  TupleManager::Shutdown();
  return 0;
}