#include <gtest/gtest.h>
#include "Scene.h"
#include "Objects.h"
#include "Globals.h"
#include <cmath>


TEST(sphere_intersection_test, NoIntersection){
    directional_vector dv({1,0,0});
    Ray ray = Ray(point3D(), dv);
    auto sphere = std::make_unique<Sphere>(1.0f, point3D(0,2,0), Surface(), 1.0f, 1.0f);
    Scene scene;
    
    auto result = sphere->intersect(ray); 
    
    if(result){
        FAIL();
    } else {
        EXPECT_EQ(result, std::nullopt);
    }
}
TEST(sphere_intersection_test, IntersectSinglePoint){
    directional_vector dv({1,0,0});
    Ray ray = Ray(point3D(), dv);
    auto sphere = std::make_unique<Sphere>(1.0f, point3D(1,1,0), Surface(), 1.0f, 1.0f);
    Scene scene;
    auto result = sphere->intersect(ray);
    if(result){
        EXPECT_EQ(result->C().x, 1.0f);
        EXPECT_EQ(result->C().y, 0.0f);
        EXPECT_EQ(result->C().z, 0.0f);
        std::cout << "dicriminant == 0";
        std::cout << "P: (" 
          << result->C().x << ", " 
          << result->C().y << ", " 
          << result->C().z << ")\n";
    } else {
        std::cout << "dicriminant == 0";
        std::cout << "result is a nullpointer";
        FAIL();
    }
}

TEST(sphere_intersection_test, IntersecTwoPointFirstReturn){
        directional_vector dv({1,0,0});
    Ray ray = Ray(point3D(), dv);
    auto sphere = std::make_unique<Sphere>(1.0f, point3D(2,0,0), Surface(), 1.0f, 1.0f);
    Scene scene;
    auto result = sphere->intersect(ray);
    if(result){
        EXPECT_EQ(result->C().x, 1.0f);
        EXPECT_EQ(result->C().y, 0.0f);
        EXPECT_EQ(result->C().z, 0.0f);
        std::cout << "P: (" 
          << result->C().x << ", " 
          << result->C().y << ", " 
          << result->C().z << ")\n";
    } else {
        std::cout << "result is a nullpointer";
        FAIL();
    }
}

TEST(sphere_intersection_test, IntersecTwoPointSecondReturn){
    directional_vector dv({1,0,0});
    Ray ray = Ray(point3D(), dv);
    auto sphere = std::make_unique<Sphere>(1.0f, point3D(0.5f,0,0), Surface(), 1.0f, 1.0f);
    Scene scene;
    auto result = sphere->intersect(ray);
    if(result){
        EXPECT_EQ(result->C().x, 1.5f);
        EXPECT_EQ(result->C().y, 0.0f);
        EXPECT_EQ(result->C().z, 0.0f);
        std::cout << "P: (" 
          << result->C().x << ", " 
          << result->C().y << ", " 
          << result->C().z << ")\n";
    } else {
        std::cout << "result is a nullpointer";
        FAIL();
    }
}

TEST(Infinite_plane_intersetion_test, ParallelNoInterSection){
    directional_vector dv({1,0,0});
    directional_vector nv({0,1,0});
    Ray ray = Ray(point3D(), dv);
    Scene scene;
    auto infinite_plane = std::make_unique<Infinite_Plane>(point3D(0,0,-1), Surface(), 1.0f, 1.0f, nv);
    auto result = infinite_plane->intersect(ray);
    if(result){
        std::cout << "not null";     
        std::cout << "P: (" 
          << result->C().x << ", " 
          << result->C().y << ", " 
          << result->C().z << ")\n";
        FAIL();
    }
    else {
        EXPECT_EQ(result, std::nullopt);
    }
}

TEST(Infinite_plane_intersetion_test, InterSection){
        directional_vector dv({1,0,0});
    directional_vector nv({1,0,0});
    Ray ray = Ray(point3D(), dv);
    Scene scene;
    auto infinite_plane = std::make_unique<Infinite_Plane>(point3D(5,0,2), Surface(), 1.0f, 1.0f, nv);
    auto result = infinite_plane->intersect(ray);
    if(result){
        EXPECT_EQ(result->C().x, 5);
        EXPECT_EQ(result->C().y, 0);
        EXPECT_EQ(result->C().z, 0);
        std::cout << "not null";     
        std::cout << "P: (" 
          << result->C().x << ", " 
          << result->C().y << ", " 
          << result->C().z << ")\n";
        
    }
    else {
        std::cout << "optnull was returned and was not expected";
        FAIL();
    }
}


TEST(Infinite_plane_intersetion_test, NoInterSectionBehindTheCamera){
    directional_vector dv({1,0,0});
    directional_vector nv({1,0,0});
    Ray ray = Ray(point3D(), dv);
    Scene scene;
    auto infinite_plane = std::make_unique<Infinite_Plane>(point3D(-5,0,2), Surface(), 1.0f, 1.0f, nv);
    auto result = infinite_plane->intersect(ray);
    if(result){

        std::cout << "not null";     
        std::cout << "P: (" 
          << result->C().x << ", " 
          << result->C().y << ", " 
          << result->C().z << ")\n";
        FAIL();
    }
    else {
        EXPECT_EQ(result, std::nullopt);
    }
}


TEST(plane_intersection_test, NoInterSectionParallel){
    directional_vector dv({1,0,0});
    Ray ray = Ray(point3D(), dv);
    point3D C({-1,0,0});
    Scene scene;
    auto rectangle = std::make_unique<Rectangle>(segment_vector(C, point3D(0,1,0)),segment_vector(C, point3D(0,0,1)), C, Surface(), 1.0f, 1.0f);
    auto result = rectangle->intersect(ray);
    if(result){
        std::cout << "not null";     
        std::cout << "P: (" 
          << result->C().x << ", " 
          << result->C().y << ", " 
          << result->C().z << ")\n";
        FAIL();
    }
    else {
        EXPECT_EQ(result, std::nullopt);
    }
}

TEST(plane_intersection_test, NoInterSectionNotParallel){
    directional_vector dv({1,0,0});
    Ray ray = Ray(point3D(), dv);
    point3D C({0,200,0});
    Scene scene;
    auto rectangle = std::make_unique<Rectangle>(segment_vector(C, point3D(1,0,0)),segment_vector(C, point3D(0,0.5f,0.5f)), C, Surface(), 1.0f, 1.0f);
    auto result = rectangle->intersect(ray);
    if(result){
        std::cout << "not null";     
        std::cout << "P: (" 
          << result->C().x << ", " 
          << result->C().y << ", " 
          << result->C().z << ")\n";
        FAIL();
    }
    else {
        EXPECT_EQ(result, std::nullopt);
    }
}
TEST(plane_intersection_test, Intersection){
    directional_vector dv({1,0,0});
    Ray ray = Ray(point3D(), dv);
    point3D C({5,0,0});
    Scene scene;
    auto rectangle = std::make_unique<Rectangle>(segment_vector(C, point3D(0,1,0)),segment_vector(C, point3D(0.5f,0,1)), C, Surface(), 1.0f, 1.0f);
    auto result = rectangle->intersect(ray);
    if(result){
        std::cout << "not null";     
        std::cout << "P: (" 
          << result->C().x << ", " 
          << result->C().y << ", " 
          << result->C().z << ")\n";
        EXPECT_EQ(result->C().x, 5);
        EXPECT_EQ(result->C().y, 0);
        EXPECT_EQ(result->C().z, 0);
    }
    else{
        std::cout << "null";
        FAIL();
    }
}

TEST(plane_intersection_test, NoIntersectionBehindTheCamera){
    directional_vector dv({1,0,0});
    Ray ray = Ray(point3D(), dv);
    point3D C({-5,0,0});
    Scene scene;
    auto rectangle = std::make_unique<Rectangle>(segment_vector(C, point3D(0,1,0)),segment_vector(C, point3D(0.5f,0,1)), C, Surface(), 1.0f, 1.0f);
    auto result = rectangle->intersect(ray);
    if(result){
        std::cout << "not null";     
        std::cout << "P: (" 
          << result->C().x << ", " 
          << result->C().y << ", " 
          << result->C().z << ")\n";
        FAIL();
    }
    else{
        std::cout << "null";
        EXPECT_EQ(result, std::nullopt);
    }

}
TEST(trace, sphere_trace_test){
    Color something = Color(230.2f, 230.2f, 230.2f);
    Scene scene;
    Surface base = Surface(something, 1.0f, 5.0f);
    auto sphere = std::make_unique<Sphere>(2.0f, point3D(0.0f, 0.0f, 2.0f), base, 5.0f, 5.0f);

    Camera camera = Camera(point3D(0,0,-3), Z_AXIS, 90.0f, 4.0f /3.0f, 1080);
    auto light = std::make_unique<Point_Light>(point3D(0.0f, 5.0f, 2.0f), 30.0f);    
    scene.add_light(std::move(light));
    scene.add_object(std::move(sphere));
    point3D origin = point3D(0,0,-2);
    directional_vector direction({0,0,1});
    Ray ray = Ray(origin, direction);
    auto intersection_data = scene.trace(ray); 
    if(intersection_data == std::nullopt){
        FAIL();
    }else{
        SUCCEED();
    }

}

