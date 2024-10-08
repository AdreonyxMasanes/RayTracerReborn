#include "pch.h"
#include "Camera.hpp"
using namespace MatrixUtil;


class CameraTest : public testing::Test {
protected:
  float pi_2 = 1.57079632679f;
  Camera camera_a = Camera(200.0f, 125.0f, pi_2);
  Camera camera_b = Camera(11.0f, 11.0f, pi_2);
  Camera camera_c = Camera(125.05, 200.0f, pi_2);

  CameraTest() {
    World t_world;
    Tuple from = TupleManager::Instance()->Point(0.0f, 0.0f, -5.0f);
    Tuple to = TupleManager::Instance()->Point(0.0f, 0.0f, 0.0f);
    Tuple up = TupleManager::Instance()->Vector(0.0f, 1.0f, 0.0f);
    Matrix view = GetViewTransform(from, to, up);
    camera_b.SetTransform(view);
    camera_b.GenerateCanvas(t_world);
  }
};

TEST_F(CameraTest, PixelSizeCalculation) {
  EXPECT_EQ(camera_a.PixelSize(), 0.01f);
  EXPECT_FLOAT_EQ(camera_c.PixelSize(), 0.01f);
}

TEST_F(CameraTest, CanvasGeneration) {
  Tuple success_color = TupleManager::Instance()->Color(0.38066f, 0.47583f, 0.2855f);
  EXPECT_EQ(camera_b.GetCanvas().GetPixel(5.0f, 5.0f), success_color);
}

int main(int argc, char** argv) {
  TupleManager::Init();
  SphereManager::Init();

  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();

  SphereManager::Shutdown();
  TupleManager::Shutdown();
}