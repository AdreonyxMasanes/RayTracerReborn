#ifndef TUPLE_H
#include <iostream>

#include "Utility.hpp"
#include <memory>


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

  float X() const;
  float Y() const;
  float Z() const;
  float W() const;

  bool operator==(const Tuple& rhs) const;
  void operator=(const Tuple& rhs);
  // If need to modify but do not want to take ownership of objects lifetime take object pointer as a parameter and pass in the raw pointer contained within unique pointer using .get()
  std::unique_ptr<Tuple> operator+(const Tuple& rhs) const;
  std::unique_ptr<Tuple> operator-(const Tuple& rhs) const;
  std::unique_ptr<Tuple> operator-() const;
  std::unique_ptr<Tuple> operator*(float scalar) const;

// TESTS
public:
  static void RunTest();

private:
  float m_x = 0, m_y = 0, m_z = 0, m_w = 0;

// TEST FUNCTIONS
private:
  static bool AdditionTest();
  static bool SubtractionTest();
  static bool NegationTest();
  static bool MultiplyTest();
  static bool IsPointTest();
  static bool IsEqualTest();
};

#endif // !TUPLE_H
