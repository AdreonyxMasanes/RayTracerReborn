#ifndef PPM_H
#define PPM_H
#include <string>
#include <iomanip>
#include <sstream>
#include "Canvas.hpp"
#include <iostream>
#include <fstream>

class PPM {
public:
  PPM(Canvas& c);
  std::string& Value();
private:
  //TODO: MAKE NO LINE LONGER THAN 70 CHAR
  int charCounter = 0;
  std::string m_value;
};
#endif // !PPM_H
