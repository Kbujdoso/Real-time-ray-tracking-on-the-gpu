cmake_minimum_required(VERSION 3.10.0)
project(Ray_tracing)
set(CMAKE_CXX_STANDARD 17)
include_directories(${PROJECT_SOURCE_DIR}/include)
set(SOURCES
    src/Camera.cpp
    src/Color.cpp
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

#--------------------------
#Google tests
#--------------------------

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG main  
)
FetchContent_MakeAvailable(googletest)

enable_testing()
file(GLOB TEST_SOURCES tests/*.cpp)
add_executable(raytracer_tests ${TEST_SOURCES})
target_link_libraries(raytracer_tests gtest_main pthread)
add_test(NAME RayTracerTests COMMAND raytracer_tests)