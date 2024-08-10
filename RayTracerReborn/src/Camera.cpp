#include "Camera.hpp"

Camera::Camera() 
  : m_transform(GetIdentityMatrix()), m_hsize_pixels(128.0f), m_vsize_pixels(128.0f), m_canvas(Canvas(128.0f, 128.0f)) {
  CalculatePixelSize();
}

Camera::Camera(float hsize, float vsize, float field_of_view) 
  : m_transform(GetIdentityMatrix()), m_hsize_pixels(hsize),m_vsize_pixels(vsize), m_field_of_view(field_of_view), m_canvas(Canvas(m_hsize_pixels, m_vsize_pixels)) {
  CalculatePixelSize();
}

float Camera::PixelSize() const {
  return m_pixel_size;
}

const Canvas& Camera::GetCanvas() const{
  return m_canvas;
}

void Camera::SetTransform(const Matrix& transform) {
  m_transform = transform;
}

Ray Camera::RayForPixel(float px, float py) const {
  float xoffset = (px + 0.5f) * m_pixel_size;
  float yoffset = (py + 0.5f) * m_pixel_size;

  float world_x = m_half_width - xoffset;
  float world_y = m_half_height - yoffset;
  Matrix camera_matrix_inversion = m_transform.Invert();
  // LEAVE THIS COMMENT HERE FOR CONVERSION WITH MAX
  Tuple world_point = TupleManager::Instance()->Point(world_x, world_y, -1.0f);
  Tuple pixel = camera_matrix_inversion * world_point;
  Tuple temp_origin = TupleManager::Instance()->Point(0.0f, 0.0f, 0.0f);
  Tuple origin = camera_matrix_inversion * temp_origin;
  Tuple direction = (pixel - origin).Normalize();

  return Ray(origin, direction);

}

void Camera::GenerateCanvas(World& world) {
  for (int y = 0; y < m_vsize_pixels - 1; y ++) {
    std::cout << "ROW: " << y << std::endl;
    for (int x = 0; x < m_hsize_pixels - 1; x++) {
      Ray ray = RayForPixel(x, y);
      Tuple color = world.ColorAt(ray);
      m_canvas.WritePixel(x, y, color);
    }
  }
  std::cout << "CANVAS GENERATED" << std::endl;
}


void Camera::CalculatePixelSize() {
  float half_view = tanf(m_field_of_view / 2.0f);
  float aspect = m_hsize_pixels / m_vsize_pixels;
  if (aspect >= 1) {
    m_half_width = half_view;
    m_half_height = half_view / aspect;
  } else {
    m_half_width = half_view * aspect;
    m_half_height = half_view;
  }
  m_pixel_size = (m_half_width * 2) / m_hsize_pixels;
}
