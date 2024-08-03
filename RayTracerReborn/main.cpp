#include "TupleManager.hpp"


int main() {
  Tuple::RunTest();
  TupleManager::Init();



  TupleManager::Shutdown();
  return 0;
}