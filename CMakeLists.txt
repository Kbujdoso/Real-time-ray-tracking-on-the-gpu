cmake_minimum_required(VERSION 3.10.0)
project(Ray_tracing)
set(CMAKE_CXX_STANDARD 17)
include_directories(${PROJECT_SOURCE_DIR}/include)
set(SOURCES
    src/Color.cpp
    src/Camera.cpp
    src/Geometry.cpp
    src/Globals.cpp
    src/Light.cpp
    src/main.cpp
    src/Objects.cpp
    src/Ray.cpp
    src/Renderer.cpp
    src/Resolution.cpp
    src/Scene.cpp
    src/Surface.cpp
)
add_executable(raytracer ${SOURCES})
