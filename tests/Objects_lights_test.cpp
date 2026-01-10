#include <gtest/gtest.h>
#include "Scene.h"
#include "Objects.h"
#include "Light.h"
#include "Globals.h"
#include "Renderer.h"
#include <cmath>
#include <memory>



TEST(add_object, SegmentationFaultTestObject){
    EXPECT_DEATH({
        Color gray = Color(200, 200, 200);
        Scene scene;
        point3D rectangle_CO = point3D(0.0f, 0.0f, 1.0f);
        Surface base = Surface(gray, 3.0f, 5.0f);
        auto sphere = std::make_unique<Sphere>(2.0f, point3D(0.0f, 5.0f, 3.0f), base, 5.0f, 5.0f);    
        auto rectangle = std::make_unique<Rectangle>(segment_vector(rectangle_CO, 
            point3D(5.0f, 1.0f, 0.0f))
            ,segment_vector(rectangle_CO,
                point3D(0.0f, 1.0f, 5.0f)),
                point3D(1.0f, 0.0f, 0.0f),
                base, 5.0f, 5.0f);

        scene.add_object(std::move(sphere));
    }, ".*");
}

TEST(add_light, SmentationFaultTestLight){

    Color gray = Color(200, 200, 200);
    Scene scene;
    point3D rectangleco = point3D(0.0f, 0.0f, 1.0f);
    Surface base = Surface(gray, 3.0f, 5.0f);
    Sphere sphere = Sphere(2.0f, point3D(0.0f, 5.0f, 3.0f), base, 5.0f, 5.0f);
    Rectangle rectangle = Rectangle(segment_vector(rectangleco, point3D(5.0f, 1.0f, 0.0f)),segment_vector(rectangleco, point3D(0.0f, 1.0f, 5.0f)), point3D(1.0f, 0.0f, 0.0f), base, 5.0f, 5.0f);
    Camera camera = Camera(point3D(), Z_AXIS, 90.0f, 4/3, 1080);
    auto light = std::make_unique<Point_Light>(point3D(-1.0f, 10.0f, 3.0f), 5.0f);

    EXPECT_DEATH({
        scene.add_light(std::move(light));
    }, ".*");
}


TEST(renderer, SmentationFaultRenderer){

    Color gray = Color(200, 200, 200);
    Scene scene;
    point3D rectangle_CO = point3D(0.0f, 0.0f, 1.0f);
    Surface base = Surface(gray, 3.0f, 5.0f);
    auto sphere = std::make_unique<Sphere>(2.0f, point3D(0.0f, 5.0f, 3.0f), base, 5.0f, 5.0f);    
    auto rectangle = std::make_unique<Rectangle>(segment_vector(rectangle_CO, 
        point3D(5.0f, 1.0f, 0.0f))
        ,segment_vector(rectangle_CO,
             point3D(0.0f, 1.0f, 5.0f)),
              point3D(1.0f, 0.0f, 0.0f),
               base, 5.0f, 5.0f);

    Camera camera = Camera(point3D(), Z_AXIS, 90.0f, 4/3, 1080);
    auto light = std::make_unique<Point_Light>(point3D(-1.0f, 10.0f, 3.0f), 5.0f);
    scene.add_light(std::move(light));
    scene.add_object(std::move(rectangle));
    scene.add_object(std::move(sphere));
    Renderer renderer = Renderer(camera, scene);

    EXPECT_DEATH({
        renderer.render();
    }, ".*");
}
