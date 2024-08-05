#include "TupleManager.hpp"
#include "BulletSim.hpp"
#include "Canvas.hpp"
#include "Matrix.hpp"
int main() {
  //SINGLETON TYPE IMPLEMENTATION
  TupleManager::Init();

  Tuple::RunTest();

  TupleManager::CreationTest();

  //BulletSim::Run(false);
  //BulletSim::Run(true);

  Canvas::CanvasTest();

  Matrix::RunTest();

  TupleManager::Shutdown();
  return 0;
}