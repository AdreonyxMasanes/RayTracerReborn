#ifndef TUPLE_H
#define TUPLE_H
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

  void Print() const;

  float X() const;
  float Y() const;
  float Z() const;
  float W() const;

// MATH FUNCTIONS
public:
  // COMPARE
  bool operator==(const Tuple& rhs) const;
  
  // ASSIGNMENT
  void operator=(const Tuple& rhs);
  
  // If need to modify but do not want to take ownership of objects lifetime take object pointer as a parameter and pass in the raw pointer contained within unique pointer using .get()
  // If need to read the value but do not want to take ownership of object lifetime take const object reference and pass in unique ptr dereferenced.
  Tuple operator+(const Tuple& rhs) const;
  Tuple operator-(const Tuple& rhs) const;
  Tuple operator-() const;
  Tuple operator*(float scalar) const;
  Tuple operator*(const Tuple& rhs) const;
  Tuple operator/(float scalar) const;

  // NEW VECTOR THAT IS PERPENDICULAR TO BOTH ORIGINAL VECTORS
  Tuple Cross(const Tuple& rhs) const;
  
  // MAGNITUDE == 1.0f
  Tuple Normalize() const;

  Tuple Reflect(const Tuple& normal) const;

  // LENGTH OF VECTOR
  float Magnitude() const;
  
  // COSINE OF ANGLE BETWEEN TWO VECTORS, CLOSER TO 1 THE CLOSER THEY ARE TO BEING IDENTICAL, CLOSER TO -1 THE CLOSEST THEY ARE TO BEING OPPOSITES 
  float Dot(const Tuple& rhs) const;
private:
  float m_x = 0, m_y = 0, m_z = 0, m_w = 0;
};

#endif // !TUPLE_H
