#include "ClockSim.hpp"

void ClockSim::Run() {
  Canvas canvas(200.0f, 100.0f);
  float radius = canvas.Height() / 4.0f;
  float pi_6 = 0.52359877559f;
  std::unique_ptr<Tuple> center = TupleManager::Instance()->Point(canvas.Width() / 2.0f, canvas.Height() / 2.0f, 0.0f);
  std::unique_ptr<Tuple> point = TupleManager::Instance()->Point(0.0f, radius, 0.0f);
  Matrix rotation = Matrix::RotationZMatrix(pi_6);
  std::unique_ptr<Tuple> twelve = *point + *center;
  std::unique_ptr<Tuple> white = TupleManager::Instance()->Color(1.0f, 1.0f, 1.0f);
  canvas.WritePixel(twelve->X(), canvas.Height() - twelve->Y(), *white);


  // NO CHECK TO SEE IF WRITING OUTSIDE THE CANVAS!
  for (int i = 1; i < 12; i++) {
    Matrix new_rotation = Matrix::RotationZMatrix(i * pi_6);
    Tuple rotated_p = new_rotation * (*point);
    std::unique_ptr<Tuple> rotated_p_a = rotated_p + *center;
    canvas.WritePixel(rotated_p.X(), canvas.Height() - rotated_p.Y(), *white);
  }
  PPM ppm(canvas);
  std::cout << "CREATED PPM SUCCESSFULLY" << std::endl;
}
