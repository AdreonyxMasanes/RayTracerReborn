#ifndef SPHERE_MANAGER_H
#define SPHERE_MANAGER_H
#include "Sphere.hpp"
class SphereManager {

public:
	SphereManager();

public:
	Sphere NewSphere();

public:
	// GET FUNCTION
	static SphereManager* Instance();

	// LIFETIME MANAGER FUNCTIONS
public:
	static void Init();
	static void Shutdown();

private:
  int total_entites = 0;
};

static SphereManager* g_sphere_manager;
#endif // !SPHERE_MANAGER_H
