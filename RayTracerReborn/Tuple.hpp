#ifndef TUPLE_H
#include <iostream>
class Tuple {
public:
  Tuple();
  Tuple(float x, float y, float z, float w);

public:
  bool IsPoint();

public:
  static void RunTest();

private:
  float m_x = 0, m_y = 0, m_z = 0, m_w = 0;

private:
  static bool IsPointTest();
};

#endif // !TUPLE_H
