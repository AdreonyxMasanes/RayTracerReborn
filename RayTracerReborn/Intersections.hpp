#ifndef INTERSECTIONS_H
#define INTERSECTIONS_H
#include "Intersection.hpp"
class Intersections {
public:
  Intersections();
  Intersections(Intersection& one, Intersection& two);

private:
  Intersection m_one;
  Intersection m_two;
};
#endif // !INTERSECTIONS_H
