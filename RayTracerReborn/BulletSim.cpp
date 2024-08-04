#include "BulletSim.hpp"

void BulletSim::Run() {
  Enviroment enviroment;
  Projectile projectile;

  TupleManager::Instance()->Vector(*enviroment.gravity_v,0.0f, -0.01f, 0.0f);
  TupleManager::Instance()->Vector(*enviroment.wind_v, 0.0f, 0.0f, 0.0f);

  TupleManager::Instance()->Point(*projectile.position_p, 0.0f, 1.0f, 0.0f);
  TupleManager::Instance()->Vector(*projectile.velocity_v, 1.0f, 1.0f, 0.0f);
  projectile.velocity_v  =  projectile.velocity_v->Normalize();
  projectile.velocity_v = *projectile.velocity_v * 3.25f;

  int max_iterations = 60000;
  int current_iteration = 0;
  while (projectile.position_p->Y() >= 0) {
    projectile.position_p->Print();
    Tick(enviroment, projectile);
    current_iteration++;
  }
}

void BulletSim::Tick(Enviroment& e, Projectile& p) {
  // THIS CREATES ANOTHER SHARED POINTER AND RETURNS IT. THE  PREVIOUS UNIQUE PTR IS DELETED
  p.position_p = *p.position_p + *p.velocity_v;
  p.velocity_v = *(*p.velocity_v + *e.gravity_v) + *e.wind_v;
}
