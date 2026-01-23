#include <iostream>
#include "Camera.h"
#include "Color.h"
#include "ENUMS.h"
#include "Geometry.h"
#include "Globals.h"
#include "Light.h"
#include "Objects.h"
#include "Ray.h"
#include "Renderer.h"
#include "Resolution.h"
#include "Scene.h"
#include "Surface.h"
#include <cmath>

int main(){
    Color something = Color(20.2f, 100.2f, 230.2f);
    Color something2 = Color(20.0f, 250.0f, 50.0f);
    Scene scene;
    Surface base = Surface(something, 1.0f, 5.0f);
    Surface base2 = Surface(something2, 1.0f, 5.0f);
    auto sphere = std::make_unique<Sphere>(3.0f, point3D(0.0f, 0.0f, 2.0f), base, 5.0f, 5.0f);
    point3D rectangle_CO = point3D(0.0f, 0.0f, 1.0f);

    point3D c = point3D(0.0f, -3.0f, 0.0f);
    auto infinite_plane = std::make_unique<Infinite_Plane>(c, base2, 2.0f, 2.0f, Y_AXIS);
    Camera camera = Camera(point3D(0,0,-3), Z_AXIS, 90.0f, 4.0f /3.0f, 1080);
    auto light = Point_Light(point3D(5.0f, 10.0f, 2.0f), 5.0f, Color(20.0f, 20.0f, 20.0f));    
    scene.add_object(std::move(sphere));  
    scene.add_object(std::move(infinite_plane));
    Renderer renderer = Renderer(camera, scene, light);
    renderer.new_render();
}