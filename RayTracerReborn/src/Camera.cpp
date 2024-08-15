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
  int thread_count = std::thread::hardware_concurrency();
  std::vector<PixelData> data;
  std::vector<std::future<PixelData>> asyncs;
  for (int y = 0; y < m_vsize_pixels; y ++) {
    std::cout << "ROW: " << y << std::endl;
    for (int x = 0; x < m_hsize_pixels; x += thread_count) {
      asyncs.clear();
      // GET PIXEL COLOR VALUES ASYNCRONOUSLY TO PREVENT THE RACE CONDITION ON DATA VECTOR
      if (!(x > m_hsize_pixels - thread_count)) {
        for (int i = 0; i < thread_count; i++) {
          asyncs.push_back(std::async(std::launch::async, &Camera::CalculatePixelData, std::ref(*this), x + i, y, std::ref(world), std::ref(data)));
        }
        // COPY DATA VECTOR TO A PERMANENT VECTOR
        for (auto& future : asyncs) {
          data.push_back(future.get());
        }
      } else {
        for (int i = 0; i < m_hsize_pixels - x; i++) {
          asyncs.push_back(std::async(std::launch::async, &Camera::CalculatePixelData, std::ref(*this), x + i, y, std::ref(world), std::ref(data)));
        }
        for (auto& future : asyncs) {
          data.push_back(future.get());
        }
      }
    }
  }
  ProccessPixelData(data);
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

PixelData Camera::CalculatePixelData(int x, int y, const World& world, std::vector<PixelData>& data) {
  Ray ray = RayForPixel(x, y);
  Tuple color = world.ColorAt(ray);
  // HAS TO BE COPIED INTO DATA MAYBE CHANGE IF IT ENDS UP SLOW
  return PixelData( color, x, y );
}

void Camera::ProccessPixelData(std::vector<PixelData>& data) {
  for (PixelData& pixel_data : data) {
    // ALSO COPYING DATA FROM VECTOR
    m_canvas.WritePixel(pixel_data.col, pixel_data.row, pixel_data.color);
  }
}

//std::latch done(thread_count);
//data.clear();
//threads.clear();
//if (!(x > m_hsize_pixels - thread_count)) {
//  for (int i = 0; i < thread_count; i++) {
//    threads.push_back(std::jthread(&Camera::CalculatePixelData, std::ref(*this), x + i, y, std::ref(world), std::ref(data)));
//    done.count_down();
//  }
//  done.wait();
//  for (auto& thread : threads) {
//    thread.join();
//  }
//  ProccessPixelData(data);
//} else {
//  std::latch remaining(m_hsize_pixels - x);
//  for (int i = 0; i < m_hsize_pixels - x; i++) {
//    threads.push_back(std::jthread(&Camera::CalculatePixelData, std::ref(*this), x + i, y, std::ref(world), std::ref(data)));
//    remaining.count_down();
//  }
//  remaining.wait();
//  for (auto& thread : threads) {
//    thread.join();
//  }
//  ProccessPixelData(data);
//}