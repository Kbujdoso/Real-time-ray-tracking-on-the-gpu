#include <gtest/gtest.h>
#include "Scene.h"
#include "Objects.h"
#include <cmath>


TEST(sphere_intersection_test, NoIntersection){
    directional_vector dv({1,0,0});
    Ray ray = Ray(point3D(), dv);
    Sphere sphere = Sphere(1.0f, point3D(0,2,0), Surface(), 1.0f, 1.0f);
    Scene scene;
    auto result = scene.sphere_intersection_test(ray, sphere);
    if(result){
            std::cout << "P: (" 
            << result->P().x << ", " 
            << result->P().y << ", " 
            << result->P().z << ")\n";
            FAIL();
        } else {
            std::cout << "result is a nullpointer";
            EXPECT_EQ(result, std::nullopt);
        }}   

TEST(sphere_intersection_test, IntersectSinglePoint){
    directional_vector dv({1,0,0});
    Ray ray = Ray(point3D(), dv);
    Sphere sphere = Sphere(1.0f, point3D(1,1,0), Surface(), 1.0f, 1.0f);
    Scene scene;
    auto result = scene.sphere_intersection_test(ray, sphere);
    if(result){
        EXPECT_EQ(result->P().x, 1.0f);
        EXPECT_EQ(result->P().y, 0.0f);
        EXPECT_EQ(result->P().z, 0.0f);
        std::cout << "dicriminant == 0";
        std::cout << "P: (" 
          << result->P().x << ", " 
          << result->P().y << ", " 
          << result->P().z << ")\n";
    } else {
        std::cout << "dicriminant == 0";
        std::cout << "result is a nullpointer";
        FAIL();
    }
}

TEST(sphere_intersection_test, IntersecTwoPointFirstReturn){
        directional_vector dv({1,0,0});
    Ray ray = Ray(point3D(), dv);
    Sphere sphere = Sphere(1.0f, point3D(2,0,0), Surface(), 1.0f, 1.0f);
    Scene scene;
    auto result = scene.sphere_intersection_test(ray, sphere);
    if(result){
        EXPECT_EQ(result->P().x, 1.0f);
        EXPECT_EQ(result->P().y, 0.0f);
        EXPECT_EQ(result->P().z, 0.0f);
        std::cout << "P: (" 
          << result->P().x << ", " 
          << result->P().y << ", " 
          << result->P().z << ")\n";
    } else {
        std::cout << "result is a nullpointer";
        FAIL();
    }
}

TEST(sphere_intersection_test, IntersecTwoPointSecondReturn){
    directional_vector dv({1,0,0});
    Ray ray = Ray(point3D(), dv);
    Sphere sphere = Sphere(1.0f, point3D(0.5f,0,0), Surface(), 1.0f, 1.0f);
    Scene scene;
    auto result = scene.sphere_intersection_test(ray, sphere);
    if(result){
        EXPECT_EQ(result->P().x, 1.5f);
        EXPECT_EQ(result->P().y, 0.0f);
        EXPECT_EQ(result->P().z, 0.0f);
        std::cout << "P: (" 
          << result->P().x << ", " 
          << result->P().y << ", " 
          << result->P().z << ")\n";
    } else {
        std::cout << "result is a nullpointer";
        FAIL();
    }
}

TEST(Infinite_plane_intersetion_test, ParallelNoInterSection){

}