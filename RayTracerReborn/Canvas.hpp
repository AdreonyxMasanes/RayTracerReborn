#ifndef CANVAS_H
#define CANVAS_H
#include <vector>
#include "TupleManager.hpp"

class Canvas {
public:
  Canvas();
  Canvas(float width, float height);
  // GET
public:
  std::vector<std::vector<Tuple>>& GetCanvas();
  float Height();
  float Width();
  Tuple& GetPixel(float row, float col);

  // SET
public:
  void WritePixel(float row, float col, const Tuple& color);


public:
  static void CanvasTest();
private:
  float m_width = 0;
  float m_height = 0;
  std::vector<std::vector<Tuple>> m_canvas;

private:

};
#endif // !CANVAS_h
