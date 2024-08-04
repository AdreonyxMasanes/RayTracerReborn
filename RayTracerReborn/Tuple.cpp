#include "Tuple.hpp"
Tuple::Tuple() {
}

// DOING IT IN THE INITALIZER LIST PREVENTS REDEFINITION
Tuple::Tuple(float x, float y, float z, float w)
  : m_x(x), m_y(y), m_z(z), m_w(w) {
}

bool Tuple::IsPoint() {
  // POINT IF W == 1.0f, VECTOR IF W == 0
  return m_w == 1.0f;
}

void Tuple::SetX(float x) {
    m_x = x;
}

void Tuple::SetY(float y) {
    m_y = y;
}

void Tuple::SetZ(float z) {
    m_z = z;
}

void Tuple::SetW(float w) {
    m_w = w;
}

float Tuple::X() const {
    return m_x;
}

float Tuple::Y() const {
    return m_y;
}

float Tuple::Z() const {
    return m_z;
}

float Tuple::W() const {
    return m_w;
}

bool Tuple::operator==(const Tuple& rhs) const {
    if (!(m_x == rhs.X())) {
        return false;
    } else if (!(m_y == rhs.Y())) {
        return false;
    } else if (!(m_z == rhs.Z())) {
        return false;
    } else if (!(m_w == rhs.W())) {
        return false;
    } else {
        return true;
    }
}

void Tuple::operator=(const Tuple& rhs) {
  m_x = rhs.X();
  m_y = rhs.Y();
  m_z = rhs.Z();
  m_w = rhs.W();
}

void Tuple::RunTest() {
  
  if (!Tuple::IsPointTest()) {
    return;
  } else {
    std::cout << "ALL TUPLE TEST PASSED " << std::endl;
  }
}

bool Tuple::IsPointTest() {
  bool is_point = true;
  Tuple test_p(0.0f, 0.0f, 0.0f, 1.0f);
  Tuple test_v(0.0f, 0.0f, 0.0f, 0.0f);

  // COULD DO THIS IN THE IF STATEMENT EXPRESSION
  is_point = test_p.IsPoint();
  if (!is_point) {
    std::cout << "POINT TEST FAILED AT TEST 1" << std::endl;
    return false;
  }
  
  // COULD DO THIS IN THE IF STATEMENT EXPRESSION
  is_point = test_v.IsPoint();
  if (is_point) {
    std::cout << "POINT TEST FAILED AT TEST 2" << std::endl;
    return false;
  }
  return true;
}

bool Tuple::IsEqualTest() {
  Tuple test_a_p(0.0f, 0.0f, 0.0f, 1.0f);
  Tuple test_b_p(0.0f, 0.0f, 0.0f, 1.0f);

  Tuple test_a_v(0.0f, 0.0f, 0.0f, 0.0f);
  Tuple test_b_v(0.0f, 0.0f, 0.0f, 0.0f);

  if (!(test_a_p == test_b_p)) {
      std::cout << "POINT EQUIVALENCE FAILED" << std::endl;
      return false;
  } else if (!(test_a_v == test_b_v)) {
      std::cout << "VECTOR EQUIVALENCE FAILED" << std::endl;
      return false;
  } else if (!(test_a_p == test_b_v)) {
      std::cout << "POINT VECTOR EQUIVALENCE FAILED" << std::endl;
      return false;
  } else {
      return true;
  }
}
