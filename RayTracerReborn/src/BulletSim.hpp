#ifndef BULLET_SIM_H
#include "TupleManager.hpp"
#include "Canvas.hpp"
#include "PPM.hpp"
namespace BulletSim {
  void Run(bool printToPPM);
  struct Projectile {
    Tuple position_p;
    Tuple velocity_v;
  };

  struct Enviroment {
    Tuple gravity_v;
    Tuple wind_v;
  };

  static void Tick(Enviroment& e, Projectile& p);
};
#endif // !BULLET_SIM_H
