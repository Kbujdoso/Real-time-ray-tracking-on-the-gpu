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
class Scene{
    private: 
        std::vector<Objects> objects;
        std::vector<Light> lights;
    public:
        Scene(std::vector<Objects> objects, std::vector<Light> lights);
        Scene();
        std::optional<point3D> sphere_intersection_test(Ray ray, Sphere sphere); 
        std::optional<std::pair<Objects, point3D>> rectangle_intersection_test(Ray ray); 
        std::optional<std::pair<Objects, point3D>> infinite_plane_intersection_test(Ray ray); 
        void add_object(Objects object);
        void remove_object(Objects object);
        std::vector<Objects> get_Objects();
        void add_light(Light light);
        void remove_light(Light light);
        std::vector<Light> get_lights();
        void clear();
};
#endif