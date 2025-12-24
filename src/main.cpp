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
    Color gray = Color(200, 200, 200);
    Scene scene;
    point3D rectangleco = point3D(0.0f, 0.0f, 1.0f);
    Surface base = Surface(gray, 3.0f, 5.0f);
    Sphere sphere = Sphere(2.0f, point3D(0.0f, 5.0f, 3.0f), base, 5.0f, 5.0f);
    Rectangle rectangle = Rectangle(segment_vector(rectangleco, point3D(5.0f, 1.0f, 0.0f)),segment_vector(rectangleco, point3D(0.0f, 1.0f, 5.0f)), point3D(1.0f, 0.0f, 0.0f), base, 5.0f, 5.0f);
    Camera camera = Camera(point3D(), Z_AXIS, 90.0f, 4/3, 1080);
    Point_Light light = Point_Light(point3D(-1.0f, 10.0f, 3.0f), 5.0f);
    scene.add_light(light);
    scene.add_object(rectangle);
    scene.add_object(sphere);
    Renderer renderer = Renderer(camera, scene);
    renderer.render();
}