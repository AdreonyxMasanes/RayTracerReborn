#include "Camera.hpp"

Camera::Camera() 
  : m_transform(Matrix::GetIdentityMatrix()), m_hsize_pixels(128.0f), m_vsize_pixels(128.0f), m_canvas(Canvas(128.0f, 128.0f)) {
  CalculatePixelSize();
}

Camera::Camera(float hsize, float vsize, float field_of_view) 
  : m_transform(Matrix::GetIdentityMatrix()), m_hsize_pixels(hsize),m_vsize_pixels(vsize), m_field_of_view(field_of_view), m_canvas(Canvas(m_hsize_pixels, m_vsize_pixels)) {
  CalculatePixelSize();
}

float Camera::PixelSize() {
  return m_pixel_size;
}

Canvas& Camera::GetCanvas() {
  return m_canvas;
}

void Camera::SetTransform(Matrix& transform) {
  m_transform = transform;
}

void Camera::RunTest() {
  if (!(PixelSizeTest())) {
    return;
  } else if (!(GenerateCanvasTest())) {
    return;
  } else {
    std::cout << "CAMERA TEST PASSED" << std::endl;
    return;
  }
}

std::unique_ptr<Ray> Camera::RayForPixel(float px, float py) {
  float xoffset = (px + 0.5f) * m_pixel_size;
  float yoffset = (py + 0.5f) * m_pixel_size;

  float world_x = m_half_width - xoffset;
  float world_y = m_half_height - yoffset;
  Matrix camera_matrix_inversion = m_transform.Invert();
  Tuple pixel = camera_matrix_inversion * *TupleManager::Instance()->Point(world_x, world_y, -1.0f);
  Tuple origin = camera_matrix_inversion * *TupleManager::Instance()->Point(0.0f, 0.0f, 0.0f);
  Tuple direction = *(pixel - origin)->Normalize();

  return std::make_unique<Ray>(origin, direction);

}

void Camera::GenerateCanvas(World& world) {
  for (int y = 0; y < m_vsize_pixels - 1; y ++) {
    std::cout << "ROW: " << y << std::endl;
    for (int x = 0; x < m_hsize_pixels - 1; x++) {
      std::unique_ptr<Ray> ray = RayForPixel(x, y);
      std::unique_ptr<Tuple> color = world.ColorAt(*ray);
      m_canvas.WritePixel(x, y, *color);
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

bool Camera::PixelSizeTest() {
  float pi_2 = 1.57079632679f;
  Camera test_a_camera(200, 125, pi_2);
  Camera test_b_camera(125, 200, pi_2);

  if (!(Utility::FloatsAreEqual(test_a_camera.PixelSize(), 0.01f))) {
    std::cout << "FIRST PIXEL SIZE TEST FAILED" << std::endl;
    return false;
  } else if (!(Utility::FloatsAreEqual(test_b_camera.PixelSize(), 0.01f))) {
    std::cout << "SECOND PIXEL SIZE TEST FAILED" << std::endl;
    return false;
  } else {
    return true;
  }
}

bool Camera::GenerateCanvasTest() {
  float pi_2 = 1.57079632679f;
  World test_world;
  Camera test_camera(11.0f, 11.0f, pi_2);
  std::unique_ptr<Tuple> from = TupleManager::Instance()->Point(0.0f, 0.0f, -5.0f);
  std::unique_ptr<Tuple> to = TupleManager::Instance()->Point(0.0f, 0.0f, 0.0f);
  std::unique_ptr<Tuple> up = TupleManager::Instance()->Vector(0.0f, 1.0f, 0.0f);
  Matrix view = Matrix::GetViewTransform(*from, *to, *up);
  test_camera.SetTransform(view);
  test_camera.GenerateCanvas(test_world);
  
  Tuple success_color = *TupleManager::Instance()->Color(0.38066f, 0.47583f, 0.2855f);
  if (!(test_camera.GetCanvas().GetPixel(5.0f, 5.0f) == success_color)) {
    std::cout << "CANVAS FAILED TO GENERATE PROPERLY" << std::endl;
    return false;
  }
}
