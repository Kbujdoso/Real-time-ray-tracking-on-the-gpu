#ifndef SCENE_H
#define SCENE_H
#include <iostream>
#include <utility>
#include <vector>
#include <optional>
#include "Geometry.h"
#include "Ray.h"
#include "Resolution.h"
#include "Camera.h"
#include "Light.h"
#include "Objects.h"
#include "Surface.h"
class Scene{
    private: 
        std::vector<Objects> objects;
        std::vector<Light> lights;
    public:
        Scene(std::vector<Objects> objects, std::vector<Light> lights);
        Scene();
        std::optional<Intersection_data> sphere_intersection_test(Ray ray, Sphere sphere); 
        std::optional<Intersection_data> rectangle_intersection_test(Ray ray, Rectangle rectangle); 
        std::optional<Intersection_data> infinite_plane_intersection_test(Ray ray, Infinite_Plane infinite_plane); 
        void add_object(Objects object);
        void remove_object(Objects object);
        std::vector<Objects> get_Objects();
        void add_light(Light light);
        void remove_light(Light light);
        std::vector<Light> get_lights();
        void clear();
};

struct Intersection_data{
    private: 
        Surface surface;
        point3D p;
    public:
        Intersection_data();
        Intersection_data(Surface S, point3D P);
};
#endif