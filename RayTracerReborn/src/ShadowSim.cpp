#include "ShadowSim.hpp"

void ShadowSim::Run(bool shading) {
  auto start = std::chrono::system_clock::now();
  float canvas_pixels = 128.0f;
  Canvas canvas(canvas_pixels, canvas_pixels);
  Tuple ray_origin = TupleManager::Instance()->Point(0.0f, 0.0f, -5.0f);
  float wall_z = 10.0f;
  float wall_size = 7.0f;
  float pixel_size = wall_size / canvas_pixels;
  float half = wall_size / 2.0f;
  Tuple red = TupleManager::Instance()->Color(1.0f, 0.0f, 0.0f);
  Sphere sphere = SphereManager::Instance()->NewSphere();

  Tuple material_color = TupleManager::Instance()->Color(1.0f, 0.2f, 1.0f);
  sphere.ModifyMaterial().SetColor(material_color);

  Tuple light_pos = TupleManager::Instance()->Point(-10.0f, 10.0f, 10.0f);
  Tuple light_color = TupleManager::Instance()->Color(1.0f, 1.0f, 1.0f);
  Light light(light_pos, light_color);

  for (int row = 0; row < canvas_pixels; row++) {
    std::cout << "ROW: " << row << std::endl;
    float world_y = half - pixel_size * row;
    for (int col = 0; col < canvas_pixels; col++) {
      float world_x = -(half)+pixel_size * col;
      Tuple position = TupleManager::Instance()->Point(world_x, world_y, wall_z);
      Tuple origin_to_pos = (position - ray_origin).Normalize();
      Ray ray(ray_origin, origin_to_pos);
      ray.Cast(sphere);
      ray.SortIntersections();
      if (!(ray.Intersections().size() == 0)) {
        if (shading) {
          const Intersection* hit = nullptr;
          hit = ray.Hit();
          Tuple point_p = ray.Position(hit->Time());
          Tuple normal_v = hit->GetSphere().NormalAt(point_p);
          Tuple eye_v = -ray.Direction();
          Tuple color = sphere.GetMaterial().Lighting(light, point_p, eye_v, normal_v, false);
          canvas.WritePixel(row, col, color);
        } else {
          canvas.WritePixel(row, col, red);
        }
      }
    }
  }

  PPM ppm(canvas);
  auto end = std::chrono::system_clock::now();
  auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
  auto elapsed_s = std::chrono::duration_cast<std::chrono::seconds>(end - start);
  std::cout << "TIME: " << elapsed_ms.count() << " miliseconds" << std::endl;
  std::cout << "TIME: " << elapsed_s.count() << " seconds" <<std::endl;
}
