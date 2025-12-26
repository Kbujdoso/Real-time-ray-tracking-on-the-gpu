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
class Light;
class Scene{
    private: 
        std::vector<Objects*> objects;
        int num_objects;
        std::vector<Light*> lights;
        int num_lights;
    public:
        Scene(std::vector<Objects*> objects, std::vector<Light*> lights);
        Scene();
        std::optional<Intersection_data> sphere_intersection_test(Ray& ray, Sphere& sphere); 
        std::optional<Intersection_data> rectangle_intersection_test(Ray& ray, Rectangle& rectangle); 
        std::optional<Intersection_data> infinite_plane_intersection_test(Ray ray, Infinite_Plane infinite_plane);
        std::optional<Intersection_data> trace(Ray ray); 
        void add_object(Objects object);
        void remove_object(Objects object);
        std::vector<Objects> get_Objects();
        void add_light(Light light);
        void remove_light(Light light);
        std::vector<Light> get_lights();
        void clear();
};



#endif