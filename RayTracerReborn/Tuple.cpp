#include "Tuple.hpp"
Tuple::Tuple() {
}

// DOING IT IN THE INITALIZER LIST PREVENTS REDEFINITION
Tuple::Tuple(float x, float y, float z, float w)
  : m_x(x), m_y(y), m_z(z), m_w(w)
{
}

bool Tuple::IsPoint() {
  // POINT IF W == 1.0f, VECTOR IF W == 0
  return m_w == 1.0f;
}

void Tuple::RunTest() {
  
  if (!Tuple::IsPointTest()) {
    return;
  } else {
    std::cout << "ALL TEST PASSED " << std::endl;
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
