#include "SphereManager.hpp"

SphereManager::SphereManager() {
}

Sphere SphereManager::NewSphere() {
  total_entites++;
  return Sphere(total_entites);

}

SphereManager* SphereManager::Instance() {
  return g_sphere_manager;
}

void SphereManager::Init() {
  g_sphere_manager = new SphereManager();
}

void SphereManager::Shutdown() {
  delete g_sphere_manager;
  g_sphere_manager = nullptr;
}
