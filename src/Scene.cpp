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


Intersection_data::Intersection_data(){
}
Intersection_data::Intersection_data(Surface S, point3D P, float T){
    surface = S;
    p = P;
    t = T;
}
Surface Intersection_data::Surface_data(){
    return surface;
}
point3D Intersection_data::P(){
    return p;
}

Scene::Scene(std::vector<Objects*> Objects, std::vector<Light> Lights) {
    objects = Objects;
    lights = Lights;
}

Scene::Scene(){
    objects = {};
    lights = {};
}

std::optional<Intersection_data> Scene::sphere_intersection_test(Ray& ray, Sphere& sphere){
    const float eps = 1e-6f;
    float a = 1;
    segment_vector OC_vector = segment_vector(sphere.C(), ray.O());
    float b = 2 * dot_product(ray.D(), OC_vector);
    float r = sphere.R();
    float c = dot_product(OC_vector, OC_vector) - r*r;
    float discriminant = b*b - 4*a*c;
    if (discriminant < 0){ //we check for the discriminant if discriminant < 0 there is no real solution for the polinom
        return std::nullopt; 
    } else 
    if (std::fabs(discriminant) < eps){ //only one real solution for the polinom
        float t = -b/(2*a);
            return Intersection_data(sphere.Surface_data() ,ray.trace_ray(t), t); 
    } 
    else //two real solutions for the polinom we need the the smaller and greater than 0 else its behind the camera
    {
        float t1 = (-b-sqrt(discriminant))/(2*a);
        float t2 = (-b+sqrt(discriminant))/(2*a);
        if (t1 > 0 && t1 < t2){
            return Intersection_data(sphere.Surface_data() ,ray.trace_ray(t1), t1); 
        } else 
        if (t2 > 0){
            return Intersection_data(sphere.Surface_data() ,ray.trace_ray(t2), t2); 
        } else 
        {
            return std::nullopt;
        }
    }   
}

std::optional<Intersection_data> Scene::infinite_plane_intersection_test(Ray ray, Infinite_Plane infinite_plane){
    bool parallel = std::fabs(dot_product(ray.D(), infinite_plane.N())) < 1e-6f;
    if(parallel){ //if its paralel there is no intersection
        return std::nullopt;
    } else { //if its not parallel then we start calculating the intersection
        segment_vector OC_vector = segment_vector(ray.O(),infinite_plane.C()); 
        float t = dot_product(infinite_plane.N(), OC_vector)/dot_product(ray.D(), infinite_plane.N());
        if (t < 0 ){ // if t < 0 the object is behind the camera
            return std::nullopt;
        } else { // if not we trace the ray and returnthe point
            return Intersection_data(infinite_plane.Surface_data() ,ray.trace_ray(t), t); 
        }
    }
}

std::optional<Intersection_data> Scene::rectangle_intersection_test(Ray& ray, Rectangle& rectangle){
    segment_vector u = rectangle.U();
    segment_vector v = rectangle.V();
    directional_vector n = rectangle.N();
        bool parallel = std::fabs(dot_product(ray.D(), rectangle.N())) < 1e-6f;
    if(parallel){ //if its parallel there is no intersection
        return std::nullopt;
    } 
    else { //if not parallel we start calculating the intersection by starting calculating the intersection with the infinite plane
        segment_vector OC_vector = segment_vector(ray.O(), rectangle.C()); 
        float t = dot_product(rectangle.N(), OC_vector)/dot_product(ray.D(), rectangle.N());
        if (t < 0 ){ // if t < 0 then the object is behind the camera
            return std::nullopt;
        } 
        else{ //if not behind we calculate if it intersect not just the infinate plane but the rectangle
            point3D P = ray.trace_ray(t);
            segment_vector w = segment_vector(P, rectangle.C());
            float u_proj = dot_product(w, rectangle.U())/dot_product(rectangle.U(), rectangle.U());
            float v_proj = dot_product(w, rectangle.V())/dot_product(rectangle.V(), rectangle.V());
            if(0 <= u_proj && 1 >= u_proj && 0 <= v_proj && 1 >= v_proj){
            return Intersection_data(rectangle.Surface_data() ,P, t); 
            }
            else { return std::nullopt;}
        }
    }
}

std::optional<Intersection_data> Scene::trace(Ray ray){
    for (auto& obj : objects) {
        switch (obj->type())
        {
        case ObjectType::Rectangle:{
            auto* r = static_cast<Rectangle*>(obj); 
            auto opt_result = rectangle_intersection_test(ray, *r);
            if(opt_result){
                Intersection_data result = *opt_result;
                return result; 
            }
            break;
        }
        case ObjectType::Sphere: {
            auto* s = static_cast<Sphere*>(obj);
            auto opt_result = sphere_intersection_test(ray, *s);
            if (opt_result){
                Intersection_data result = *opt_result;
                return result;
            }
            break;
        }
        case ObjectType::Infinite_plane: {
            auto* i = static_cast<Infinite_Plane*>(obj);
            auto opt_result = infinite_plane_intersection_test(ray, *i);
            if (opt_result){
                Intersection_data result = *opt_result;
                return result;
            }
            break;
        }
        }
    }
    return std::nullopt;
}

