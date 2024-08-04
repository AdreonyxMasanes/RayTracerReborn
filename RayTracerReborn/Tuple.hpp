#ifndef TUPLE_H
#include <iostream>
class Tuple {
public:
  Tuple();
  Tuple(float x, float y, float z, float w);
// UTILITY FUNCS
public:
  bool IsPoint();

  void SetX(float x);
  void SetY(float y);
  void SetZ(float z);
  void SetW(float w);

  float X();
  float Y();
  float Z();
  float W();

// TESTS
public:
  static void RunTest();

private:
  float m_x = 0, m_y = 0, m_z = 0, m_w = 0;

// TEST FUNCTIONS
private:
  static bool IsPointTest();
};

#endif // !TUPLE_H
