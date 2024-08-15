cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(RayTracerReborn VERSION 1.0)
include_directories(${PROJECT_SOURCE_DIR}/RayTracerReborn/src)

set(SRC_FILES 
${PROJECT_SOURCE_DIR}/RayTracerReborn/src/BulletSim.cpp
${PROJECT_SOURCE_DIR}/RayTracerReborn/src/Canvas.cpp
${PROJECT_SOURCE_DIR}/RayTracerReborn/src/Camera.cpp
${PROJECT_SOURCE_DIR}/RayTracerReborn/src/ClockSim.cpp
${PROJECT_SOURCE_DIR}/RayTracerReborn/src/Intersection.cpp
${PROJECT_SOURCE_DIR}/RayTracerReborn/src/Light.cpp
${PROJECT_SOURCE_DIR}/RayTracerReborn/src/main.cpp
${PROJECT_SOURCE_DIR}/RayTracerReborn/src/Material.cpp
${PROJECT_SOURCE_DIR}/RayTracerReborn/src/Matrix.cpp
${PROJECT_SOURCE_DIR}/RayTracerReborn/src/MatrixUtil.cpp
${PROJECT_SOURCE_DIR}/RayTracerReborn/src/PPM.cpp
${PROJECT_SOURCE_DIR}/RayTracerReborn/src/Ray.cpp
${PROJECT_SOURCE_DIR}/RayTracerReborn/src/SceneSim.cpp
${PROJECT_SOURCE_DIR}/RayTracerReborn/src/ShadowSim.cpp
${PROJECT_SOURCE_DIR}/RayTracerReborn/src/Sphere.cpp
${PROJECT_SOURCE_DIR}/RayTracerReborn/src/SphereManager.cpp
${PROJECT_SOURCE_DIR}/RayTracerReborn/src/Tuple.cpp
${PROJECT_SOURCE_DIR}/RayTracerReborn/src/TupleManager.cpp
${PROJECT_SOURCE_DIR}/RayTracerReborn/src/Utility.cpp
${PROJECT_SOURCE_DIR}/RayTracerReborn/src/World.cpp
)

add_executable(RayTracerReborn ${SRC_FILES})