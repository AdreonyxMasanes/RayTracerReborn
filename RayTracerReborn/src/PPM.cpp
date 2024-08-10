#include "PPM.hpp"
PPM::PPM(const Canvas& c) {
  std::string temp;
  std::ostringstream oss;
  oss << std::setprecision(8) << std::noshowpoint << c.Width();
  m_value += "P3\n";
  m_value += oss.str() + " ";
  oss.str("");
  
  oss << c.Height();
  m_value += oss.str() + "\n";
  oss.str("");
  // 255 BECAUSE THATS THE MAX COLOR VALUE
  m_value += "255\n";

  for (int i = 0; i < c.Height(); i++) {
    for (int j = 0; j < c.Width(); j++) {
      float r, g, b;
      r = abs(c.GetPixel(j, i).X());
      g = abs(c.GetPixel(j, i).Y());
      b = abs(c.GetPixel(j, i).Z());

      if (r >= 0) {
        if ( r >= 1) {
          r = 255.0f;
        } else {
          r = std::ceilf(255 * r);
        }
      } 

      if (g >= 0) {
        if (g >= 1) {
          g = 255.0f;
        } else {
          g = std::ceilf(255 * g);
        }
      }

      if (b >= 0) {
        if (b >= 1) {
          b = 255.0f;
        } else {
          b = std::ceilf(255 * b);
        }
      }

      oss << r << " " << g << " " << b;
      charCounter += 5;
      if (charCounter >= 64) {
        oss << "\n";
        charCounter = 0;
      } else {
        oss << " ";
        charCounter += 1;
      }
      m_value += oss.str();
      oss.str("");
    } 
  }

  std::ofstream ppm_file("img//PPM.ppm");
  ppm_file << m_value << std::endl;
  ppm_file.close();

}
