#include "ClockSim.hpp"

void ClockSim::Run() {
  Canvas canvas(200.0f, 100.0f);
  float radius = canvas.Height() / 4.0f;
  float pi_6 = 0.52359877559f;
  Tuple center = TupleManager::Instance()->Point(canvas.Width() / 2.0f, canvas.Height() / 2.0f, 0.0f);
  Tuple point = TupleManager::Instance()->Point(0.0f, radius, 0.0f);
  Matrix rotation = RotationZMatrix(pi_6);
  Tuple twelve = point + center;
  Tuple white = TupleManager::Instance()->Color(1.0f, 1.0f, 1.0f);
  canvas.WritePixel(twelve.X(), canvas.Height() - twelve.Y(), white);


  // NO CHECK TO SEE IF WRITING OUTSIDE THE CANVAS!
  for (int i = 1; i < 12; i++) {
    Matrix new_rotation = RotationZMatrix(i * pi_6);
    Tuple rotated_p = new_rotation * (point);
    Tuple rotated_p_a = rotated_p + center;
    canvas.WritePixel(rotated_p.X(), canvas.Height() - rotated_p.Y(), white);
  }
  PPM ppm(canvas);
  std::cout << "CREATED PPM SUCCESSFULLY" << std::endl;
}
