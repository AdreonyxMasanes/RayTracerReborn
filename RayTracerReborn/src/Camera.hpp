#ifndef CAMERA_H
#define CAMERA_H
#include "MatrixUtil.hpp"
#include "Ray.hpp"
#include "World.hpp"
#include "Canvas.hpp"
#include <latch>
#include <thread>
#include <future>

struct PixelData {
  Tuple color;
  float col;
  float row;
};

using namespace MatrixUtil;
class Camera {
public:
  Camera();
  Camera(float hsize, float vsize, float field_of_view);

  // GETS
public:
  float PixelSize() const;
  const Canvas& GetCanvas() const;
public: 
  void SetTransform(const Matrix& transform);
public:
  Ray RayForPixel(float px, float py) const;
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
  PixelData CalculatePixelData(int x, int y, const World& world, std::vector<PixelData>& data);
  void ProccessPixelData(std::vector<PixelData>& data);
};
#endif // !CAMERA_H
