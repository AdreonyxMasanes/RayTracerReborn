#include "Intersections.hpp"

Intersections::Intersections()
  :m_one(Intersection()), m_two(Intersection()) {
}

Intersections::Intersections(Intersection& one, Intersection& two)
  :m_one(one), m_two(two) {
}
