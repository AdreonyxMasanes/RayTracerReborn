#include "BulletSim.hpp"

void BulletSim::Run(bool print_to_ppm ) {
  Enviroment enviroment;
  Projectile projectile;

  enviroment.gravity_v =TupleManager::Instance()->Vector(0.0f, -0.01f, 0.0f);
  enviroment.wind_v = TupleManager::Instance()->Vector(0.0f, 0.0f, 0.0f);

  projectile.position_p = TupleManager::Instance()->Point(0.0f, 1.0f, 0.0f);
  projectile.velocity_v = TupleManager::Instance()->Vector(1.0f, 1.0f, 0.0f);
  projectile.velocity_v  =  projectile.velocity_v->Normalize();
  projectile.velocity_v = *projectile.velocity_v * 3.0f;

  int max_iterations = 60000;
  int current_iteration = 0;

  Canvas canvas(900.0f, 500.0f);

  std::unique_ptr<Tuple> red = TupleManager::Instance()->Color(1.0f, 0.0f, .0f);
  
  while (projectile.position_p->Y() >= 0 && current_iteration < max_iterations) {
    if (print_to_ppm) {
      // MAKE SURE NOT TRYING TO PRINT OUTSIDE OF CANVAS
      if (projectile.position_p->Y() < canvas.Height() - 1.0f &&
          projectile.position_p->X() < canvas.Width() - 1.0f  &&
          projectile.position_p->X() > 0) {
        canvas.WritePixel(projectile.position_p->X(), canvas.Height() - projectile.position_p->Y(), *red);
      }
    }

    projectile.position_p->Print();
    Tick(enviroment, projectile);
    current_iteration++;

  }

  if (print_to_ppm) {
    PPM result(canvas);
  }
}

void BulletSim::Tick(Enviroment& e, Projectile& p) {
  // THIS CREATES ANOTHER SHARED POINTER AND RETURNS IT. THE  PREVIOUS UNIQUE PTR IS DELETED
  p.position_p = *p.position_p + *p.velocity_v;
  p.velocity_v = *(*p.velocity_v + *e.gravity_v) + *e.wind_v;
}
