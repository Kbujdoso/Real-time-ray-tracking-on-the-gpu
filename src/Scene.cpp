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
#include <cmath>

Scene::Scene(std::vector<Objects> Objects, std::vector<Light> Lights) {
    objects = Objects;
    lights = Lights;
}

Scene::Scene(){
    objects = {};
    lights = {};
}

std::optional<point3D> Scene::sphere_intersection_test(Ray ray, Sphere sphere){
    float a = 1;
    segment_vector OC_vector = segment_vector(ray.O(), sphere.C());
    float b = dot_product(ray.D(), OC_vector);
    float r = sphere.R();
    float c = dot_product(OC_vector, OC_vector) - r*r;
    float discriminant = b*b - 4*a*c;
    if (discriminant < 0){
        return std::nullopt; 
    } else 
    if (discriminant = 0){
        float t = -1*(b/(2*a));
        return ray.trace_ray(t);
    } 
    else 
    {
        float t1 = -b+sqrt(discriminant)/(2*a);
        float t2 = -b-sqrt(discriminant)/(2*a);
        if (t1 > 0 && t1 < t2){
            return ray.trace_ray(t1);
        } else 
        if (t2 > 0 && t2 < t1){
            return ray.trace_ray(t2);
        } else 
        {
            return std::nullopt;
        }
    }   
}
std::optional<point3D> Scene::infinite_plane_intersection_test(Ray ray, Infinite_Plane infinite_plane){
    bool parallel = fabs(dot_product(ray.D(), infinite_plane.N())) < 1e-6f;
    if(parallel){
        return std::nullopt;
    } else {
        segment_vector CO_vector = segment_vector(infinite_plane.C() ,ray.O()); 
        float t = dot_product(infinite_plane.N(), CO_vector)/dot_product(ray.D(), infinite_plane.N());
        if (t < 0 ){
            return std::nullopt;
        } else {
            return ray.trace_ray(t); 
        }
    }
}

std::optional<point3D> Scene::rectangle_intersection_test(Ray ray, Rectangle rectangle){
    directional_vector u = rectangle.U().normalize_vector();
    directional_vector v = rectangle.V().normalize_vector();
    directional_vector normal_vector = cross_product(u, v).normalize_vector();

}