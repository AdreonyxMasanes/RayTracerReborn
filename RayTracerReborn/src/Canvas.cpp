#include "Canvas.hpp"

Canvas::Canvas() {
}

//READ UP ON VECTORS
Canvas::Canvas(float width, float height) 
  : m_width(width), m_height(height) {
  for (int row = 0; row < height; row++ ) {
    std::vector<Tuple> temp;
    for (int col = 0; col < width; col++) {
      temp.push_back(Tuple(0.0f, 0.0f, 0.0f, 0.0f));
    }
    m_canvas.push_back(temp);
  }
}

const std::vector<std::vector<Tuple>>& Canvas::GetCanvas() const{
  return m_canvas;
}

std::vector<std::vector<Tuple>>& Canvas::ModifyCanvas() {
  return m_canvas;
}


float Canvas::Height() const {
  return m_height;
}

float Canvas::Width() const{
  return m_width;
}

void Canvas::WritePixel(float row, float col, const Tuple& color) {
  ModifyPixel(row, col) = color;
}

void Canvas::CanvasTest() {
  Canvas canvas(128.0f, 128.0f);
  
  Tuple red_c = TupleManager::Instance()->Color(1.0f, 0.0f, 0.0f);

  for (int row = 0; row < canvas.Height() / 2.0f; row++) {
    for (int col = 0; col < canvas.Width(); col++) {
      canvas.WritePixel(row, col, red_c);
    }
  }
  // SHOULD BE RED 1 0 0 0 
  Tuple test_b_c = canvas.GetPixel((canvas.Height() / 2.0f) - 1.0f, (canvas.Width() / 2.0f) - 1.0f);

  if (!(test_b_c == Tuple(1.0f, 0.0f, 0.0f, 0.0f))) {
    std::cout << "CANVAS FUNCTIONS FAILED" << std::endl;
  } else {
    std::cout << "CANVAS TEST PASSED" << std::endl;
  }

}

Tuple& Canvas::ModifyPixel(float row, float col) {
  return m_canvas.at(col).at(row);
}

const Tuple& Canvas::GetPixel(float row, float col) const {
  return m_canvas.at(col).at(row);
}
