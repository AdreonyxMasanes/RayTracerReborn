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

Tuple Tuple::operator+(const Tuple& rhs) const {
  return Tuple(X() + rhs.X(), Y() + rhs.Y(), Z() + rhs.Z(), W() + rhs.W());
}

Tuple Tuple::operator-(const Tuple& rhs) const {
  return Tuple(X() - rhs.X(), Y() - rhs.Y(), Z() - rhs.Z(), W() - rhs.W());
}

Tuple Tuple::operator-() const {
  return Tuple(-X(), -Y(), -Z(), -W());
}

Tuple Tuple::operator*(float scalar) const {
  return Tuple(X() * scalar, Y() * scalar, Z() * scalar, W() * scalar);
}

Tuple Tuple::operator*(const Tuple& rhs) const {
  return Tuple(X() * rhs.X(), Y() * rhs.Y(), Z() * rhs.Z(), W() * rhs.W());
}

Tuple Tuple::operator/(float scalar) const {
  return Tuple(X() / scalar, Y() / scalar, Z() / scalar, W() / scalar);
}

Tuple Tuple::Cross(const Tuple& rhs) const {
  return Tuple(Y() * rhs.Z() - Z() * rhs.Y(),
    Z() * rhs.X() - X() * rhs.Z(),
    X() * rhs.Y() - Y() * rhs.X(), 
    0.0f);
}

Tuple Tuple::Normalize() const {
  float magnitude = Magnitude();
  return Tuple(X() / magnitude, Y() / magnitude, Z() / magnitude, W() / magnitude);
}

Tuple Tuple::Reflect(const Tuple& normal) const {
  return *this - ((normal * (2 * Dot(normal))));
}

float Tuple::Magnitude() const {
  return sqrtf(powf(X(), 2) + powf(Y(), 2) + powf(Z(), 2) + powf(W(), 2));
}

float Tuple::Dot(const Tuple& rhs) const {
  return (X() * rhs.X()) + (Y() * rhs.Y()) + (Z() *  rhs.Z()) + (W() * rhs.W());
}