#ifndef POINT_H
#define POINT_H
#include "Tuple.h"

class Point : public Tuple {
 public:
   Point();
   Point(float x, float y, float z);
   static std::shared_ptr<Tuple> Translate(float x, float y, float z);
};

#endif // !POINT_H
