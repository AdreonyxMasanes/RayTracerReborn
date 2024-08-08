#ifndef CAMERA_H
#define CAMERA_H
#include "Matrix.hpp"
#include "Ray.hpp"
#include "World.hpp"
#include "Canvas.hpp"
class Camera {
public:
  Camera();
  Camera(float hsize, float vsize, float field_of_view);

  // GETS
public:
  float PixelSize();
  Canvas& GetCanvas();
public: 
  void SetTransform(Matrix& transform);
public:
  static void RunTest();
  Ray RayForPixel(float px, float py);
  void GenerateCanvas(World& world);
private:
  float m_hsize_pixels = 0;
  float m_vsize_pixels = 0;
  float m_field_of_view = 0;
  float m_pixel_size = 0;
  float m_half_width = 0;
  float m_half_height = 0;
  Matrix m_transform;
  Canvas m_canvas;
private: 
  void CalculatePixelSize();
private:
  static bool PixelSizeTest();
  static bool GenerateCanvasTest();
};
#endif // !CAMERA_H
