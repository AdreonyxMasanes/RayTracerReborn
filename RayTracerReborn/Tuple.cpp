#include "Tuple.hpp"
// _t is generic Tuple, _p is Point, _v is Vector

Tuple::Tuple() 
  : m_x(0), m_y(0), m_z(0), m_w(0) {

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

void Tuple::Print() {
  std::cout << "X: " << X() << " Y: " << Y() << " Z: " << Z() << " W: " << W() << std::endl;
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
    if (!(Utility::FloatsAreEqual(m_x, rhs.X()))) {
        return false;
    } else if (!(Utility::FloatsAreEqual(m_y, rhs.Y()))) {
        return false;
    } else if (!(Utility::FloatsAreEqual(m_z, rhs.Z()))) {
        return false;
    } else if (!(Utility::FloatsAreEqual(m_w, rhs.W()))) {
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

std::unique_ptr<Tuple> Tuple::operator+(const Tuple& rhs) const {
  return std::make_unique<Tuple>(X() + rhs.X(), Y() + rhs.Y(), Z() + rhs.Z(), W() + rhs.W());
}

std::unique_ptr<Tuple> Tuple::operator-(const Tuple& rhs) const {
  return std::make_unique<Tuple>(X() - rhs.X(), Y() - rhs.Y(), Z() - rhs.Z(), W() - rhs.W());
}

std::unique_ptr<Tuple> Tuple::operator-() const {
  return std::make_unique<Tuple>(-X(), -Y(), -Z(), -W());
}

std::unique_ptr<Tuple> Tuple::operator*(float scalar) const {
  return std::make_unique<Tuple>(X() * scalar, Y() * scalar, Z() * scalar, W() * scalar);
}

std::unique_ptr<Tuple> Tuple::operator*(const Tuple& rhs) const {
  return std::make_unique<Tuple>(X() * rhs.X(), Y() * rhs.Y(), Z() * rhs.Z(), W() * rhs.W());
}

std::unique_ptr<Tuple> Tuple::operator/(float scalar) const {
  return std::make_unique<Tuple>(X() / scalar, Y() / scalar, Z() / scalar, W() / scalar);
}

std::unique_ptr<Tuple> Tuple::Cross(const Tuple& rhs) const {
  return std::make_unique<Tuple>(Y() * rhs.Z() - Z() * rhs.Y(),
    Z() * rhs.X() - X() * rhs.Z(),
    X() * rhs.Y() - Y() * rhs.X(), 
    0.0f);
}

std::unique_ptr<Tuple> Tuple::Normalize() const {
  float magnitude = Magnitude();
  return std::make_unique<Tuple>(X() / magnitude, Y() / magnitude, Z() / magnitude, W() / magnitude);
}

float Tuple::Magnitude() const {
  return sqrtf(powf(X(), 2) + powf(Y(), 2) + powf(Z(), 2) + powf(W(), 2));
}

float Tuple::Dot(const Tuple& rhs) const {
  return (X() * rhs.X()) + (Y() * rhs.Y()) + (Z() *  rhs.Z()) + (W() * rhs.W());
}

void Tuple::RunTest() {
  
  if (!(Tuple::IsPointTest())) {
    return;
  } else if (!(Tuple::AdditionTest())) {
    return;
  } else if (!(Tuple::SubtractionTest())) {
    return;
  } else if (!(Tuple::NegationTest())) {
    return;
  } else if (!(Tuple::MultiplyTest())) {
    return;
  } else if (!(Tuple::DivisonTest())) {
    return;
  } else if (!(Tuple::MagnitudeTest())) {
    return;
  } else if (!(Tuple::NormalizeTest())) {
    return;
  } else if (!(Tuple::DotTest())) {
    return;
  } else if (!(Tuple::CrossTest())) {
    return;
  } else if (!(Tuple::MultipleTwoTuplesTest())) {
    return;
  } else {
    std::cout << "ALL TUPLE TEST PASSED " << std::endl;
  }
}

bool Tuple::AdditionTest() {
  Tuple test_p(3.0f, -2.0f, 5.0f, 1.0f);
  Tuple test_v(-2.0f, 3.0f, 1.0f, 0.0f);
  Tuple test_success_p(1.0f, 1.0f, 6.0f, 1.0f);

  std::unique_ptr<Tuple> result = test_p + test_v;
  
  if (!(*result == test_success_p)) {
    std::cout << "ADDITION TEST FAILED " << std::endl;
    return false;
  } else {
    return true;
  }
}

bool Tuple::SubtractionTest() {

  Tuple test_a_p(3.0f, 2.0f, 1.0f, 1.0f);
  Tuple test_b_p(5.0f, 6.0f, 7.0f, 1.0f);
  Tuple test_success_v(-2.0f, -4.0f, -6.0f, 0.0f);
  Tuple test_success_p(-2.0f, -4.0f, -6.0f, 1.0f);

  // TWO POINTS SUBTRACTED FROM EACH OTHER RETURNS A VECTOR FROM RHS POINTING TOWARDS LHS
  std::unique_ptr<Tuple> result = test_a_p - test_b_p;

  if (!(*result == test_success_v)) {
    std::cout << "SUBTRACTION TEST 1 FAILED " << std::endl;
    return false;
  }

  Tuple test_a_v(5.0f, 6.0f, 7.0f, 0.0f);
  // SUBTRACTING A VECTOR FROM A POINT RETURNS THE POINT THE VECTOR IS POINTING TOWARDS IF THE ORIGINAL POINT WAS THE ORIGIN
  result = test_a_p - test_a_v;

  if (!(*result == test_success_p)) {
    std::cout << "SUBTRACTION TEST 2 FAILED " << std::endl;
    return false;
  }


  Tuple test_b_v(3.0f, 2.0f, 1.0f, 0.0f);
  // SUBTRACING A VECTOR FROM A VECTOR GIVES ANOTHER VECTOR DEMONSTRATING THE CHANGE IN VECTORS
  result = test_b_v - test_a_v;


  if (!(*result == test_success_v)) {
    std::cout << "SUBTRACTION TEST 3 FAILED " << std::endl;
    return false;
  }
}

bool Tuple::NegationTest() {
  Tuple test_p(1.0f, -2.0f, 3.0f, -4.0f);
  Tuple test_success_t(-1.0f, 2.0f, -3.0f, 4.0f);
  std::unique_ptr<Tuple> result = -test_p;

  if (!(*result == test_success_t)) {
    std::cout << "NEGATION TEST FAILED " << std::endl;
    return false;
  }
}

bool Tuple::MultiplyTest() {
  Tuple test_t(1.0f, -2.0f, 3.0f, -4.0f);
  Tuple test_success_t(3.5f, -7.0f, 10.5f, -14.0f);
  std::unique_ptr<Tuple> result = test_t * 3.5f;

  if (!(*result == test_success_t)) {
    std::cout << "MULTIPLICATION TEST FAILED " << std::endl;
    return false;
  }

  test_success_t = Tuple(0.5f, -1.0f, 1.5f, -2.0f);
  result = test_t * 0.5f;

  if (!(*result == test_success_t)) {
    std::cout << "MULTIPLICATION TEST 2 FAILED " << std::endl;
    return false;
  }
  return true;
}

bool Tuple::MultipleTwoTuplesTest() {
  Tuple test_a_c(1.0f, 0.2f, 0.4f, 0.0f);
  Tuple test_b_c(0.9f, 1.0f, 0.1f, 0.0f);
  Tuple test_success_c(0.9f, 0.2f, 0.04f, 0.0f);
  std::unique_ptr<Tuple> result = test_a_c * test_b_c;

  if (!(*result == test_success_c)) {
    std::cout << "MULTIPLY TUPLES TOGETHER TEST FAILED " << std::endl;
    return false;
  }
  return true;
}

bool Tuple::DivisonTest() {
  Tuple test_t(1.0f, -2.0f, 3.0f, -4.0f);
  Tuple test_success_t(0.5f, -1.0f, 1.5f, -2.0f);
  std::unique_ptr<Tuple> result = test_t / 2.0f;

  if (!(*result == test_success_t)) {
    std::cout << "DIVISON TEST FAILED " << std::endl;
    return false;
  } else {
    return true;
  }
}

bool Tuple::MagnitudeTest() {
  Tuple test_v(1.0f, 0.0f, 0.0f, 0.0f);
  float succes = 1.0f;
  if (!(Utility::FloatsAreEqual(test_v.Magnitude(), succes))) {
    std::cout << "FAILED MAGNITUDE TEST" << std::endl;
    return false;
  }

  // SAME SUCCESS CASE AS FIRST TEST
  test_v = Tuple(0.0f, 1.0f, 0.0f, 0.0f);
  if (!(Utility::FloatsAreEqual(test_v.Magnitude(), succes))) {
    std::cout << "FAILED MAGNITUDE TEST 2" << std::endl;
    return false;
  }

  // SAME SUCCESS CASE AS FIRST TEST
  test_v = Tuple(0.0f, 0.0f, 1.0f, 0.0f);
  if (!(Utility::FloatsAreEqual(test_v.Magnitude(), succes))) {
    std::cout << "FAILED MAGNITUDE TEST 3" << std::endl;
    return false;
  }


  test_v = Tuple(1.0f, 2.0f, 3.0f, 0.0f);
  succes = sqrtf(14);
  if (!(Utility::FloatsAreEqual(test_v.Magnitude(), succes))) {
    std::cout << "FAILED MAGNITUDE TEST 4" << std::endl;
    return false;
  }

  // SAME SUCCESS CASE AS 4 TEST
  test_v = Tuple(-1.0f, -2.0f, -3.0f, 0.0f);
  if (!(Utility::FloatsAreEqual(test_v.Magnitude(), succes))) {
    std::cout << "FAILED MAGNITUDE TEST 5" << std::endl;
    return false;
  } else {
    return true;
  }
}

bool Tuple::NormalizeTest() {
  Tuple test_v(4.0f, 0.0f, 0.0f, 0.0f);
  Tuple test_success_v(1.0f, 0.0f, 0.0f, 0.0f);

  std::unique_ptr<Tuple> result = test_v.Normalize();
  if (!(*result == test_success_v)) {
    std::cout << "NORMALIZE TEST FAILED" << std::endl;
    return false;
  }

  test_v = Tuple(1.0f, 2.0f, 3.0f, 0.0f);
  test_success_v = Tuple(1.0f / sqrtf(14), 2.0f / sqrtf(14), 3.0f / sqrtf(14), 0.0f);
  result = test_v.Normalize();
  if (!(*result == test_success_v)) {
    std::cout << "NORMALIZE TEST 2 FAILED" << std::endl;
    return false;
  }

  if (!(Utility::FloatsAreEqual(result->Magnitude(), 1.0f))) {
    std::cout << "NORMALIZED TEST 3 FAILED" << std::endl;
    return false;
  } else {
    return true;
  }
}


bool Tuple::DotTest() {
  Tuple test_a_v(1.0f, 2.0f, 3.0f, 0.0f);
  Tuple test_b_v(2.0f, 3.0f, 4.0f, 0.0f);
  float result = test_a_v.Dot(test_b_v);

  if (!(Utility::FloatsAreEqual(result , 20.0f))) {
    std::cout << "DOT TEST FAILED" << std::endl;
    return false;
  } else {
    return true;
  }

}

bool Tuple::CrossTest() {
  Tuple test_a_v(1.0f, 2.0f, 3.0f, 0.0f);
  Tuple test_b_v(2.0f, 3.0f, 4.0f, 0.0f);
  Tuple test_success_v(-1.0f, 2.0f, -1.0f, 0.0f);

  std::unique_ptr<Tuple> result = test_a_v.Cross(test_b_v);
  if (!(*result == test_success_v)) {
    std::cout << "CROSS TEST FAILED" << std::endl;
    return false;
  }

  test_success_v = Tuple(1.0f, -2.0f, 1.0f, 0.0f);
  result = test_b_v.Cross(test_a_v);
  if (!(*result == test_success_v)) {
    std::cout << "CROSS TEST 2 FAILED" << std::endl;
    return false;
  } else {
    return true;
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
