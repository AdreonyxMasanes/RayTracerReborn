#ifndef BULLET_SIM_H
#include "TupleManager.hpp"
#include "Canvas.hpp"
#include "PPM.hpp"
class BulletSim {
public:
  static void Run(bool printToPPM);
private:
  struct Projectile {
    std::unique_ptr<Tuple> position_p = std::make_unique<Tuple>();
    std::unique_ptr<Tuple> velocity_v = std::make_unique<Tuple>();
  };

  struct Enviroment {
    std::unique_ptr<Tuple> gravity_v = std::make_unique<Tuple>();
    std::unique_ptr<Tuple> wind_v = std::make_unique<Tuple>();
  };

  static void Tick(Enviroment& e, Projectile& p);
};
#endif // !BULLET_SIM_H
