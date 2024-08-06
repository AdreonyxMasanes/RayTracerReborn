#include "ShadowSim.hpp"

void ShadowSim::Run(bool shading) {
  float canvas_pixels = 128.0f;
  Canvas canvas(canvas_pixels, canvas_pixels);
  std::unique_ptr<Tuple> ray_origin = TupleManager::Instance()->Point(0.0f, 0.0f, -5.0f);
  float wall_z = 10.0f;
  float wall_size = 7.0f;
  float pixel_size = wall_size / canvas_pixels;
  float half = wall_size / 2.0f;
  std::unique_ptr<Tuple> red = TupleManager::Instance()->Color(1.0f, 0.0f, 0.0f);
  std::unique_ptr<Sphere> sphere = SphereManager::Instance()->NewSphere();

  for (int row = 0; row < canvas_pixels; row++) {
    std::cout << "ROW: " << row << std::endl;
    float world_y = half - pixel_size * row;
    for (int col = 0; col < canvas_pixels; col++) {
      float world_x = -(half)+pixel_size * col;
      std::unique_ptr<Tuple> position = TupleManager::Instance()->Point(world_x, world_y, wall_z);
      Ray ray(*ray_origin, *(*position - *ray_origin)->Normalize());
      ray.Cast(*sphere);
      if (!(ray.Intersections().size() == 0)) {
        if (shading) {

        } else {
          canvas.WritePixel(row, col, *red);
        }
      }
    }
  }

  PPM ppm(canvas);
}
