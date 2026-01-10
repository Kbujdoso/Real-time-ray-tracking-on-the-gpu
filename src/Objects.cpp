#include "Objects.h"
#include "Geometry.h"
#include "Surface.h"
#include "ENUMS.h"
#include <optional>
#include "Globals.h"
#include <cmath>
#include "Ray.h"

Objects::Objects(point3D c, Surface s, float ra, float re){
    coordinate = c;
    surface = s; 
    refraction = ra;
    reflection = re;
}
Objects::Objects(){}

Surface Objects::Surface_data(){
    return surface;
}
point3D Objects::C(){
    return coordinate;
}
float Objects::Re(){
    return refraction;
}

float Objects::Ra(){
    return refraction;
}
ObjectType Objects::type(){
    return ObjectType::Unkown;
}


Infinite_Plane::Infinite_Plane(point3D c, Surface s, float ra, float re, directional_vector n){
    coordinate = c;
    surface = s; 
    refraction = ra;
    reflection = re; 
    normal_vector = n;
}

directional_vector Infinite_Plane::N(){
    return normal_vector;
}
ObjectType Infinite_Plane::type(){
    return ObjectType::Infinite_plane;
}
std::optional<Intersection_data> Infinite_Plane::intersect(Ray ray){
    bool parallel = std::fabs(dot_product(ray.D(),N())) < 1e-6f;
    if(parallel){ //if its paralel there is no intersection
        return std::nullopt;
    } else { //if its not parallel then we start calculating the intersection
        segment_vector OC_vector = segment_vector(ray.O(),C()); 
        float t = dot_product(N(), OC_vector)/dot_product(ray.D(), N());
        if (t < 0 ){ // if t < 0 the object is behind the camera
            return std::nullopt;
        } else { // if not we trace the ray and returnthe point
            return Intersection_data(Surface_data() ,ray.trace_ray(t), t); 
        }
    }
}

Rectangle::Rectangle(segment_vector U, segment_vector V, point3D c, Surface s, float re, float ra){
    u = U;
    v = V; 
    coordinate = c; 
    surface = s; 
    reflection = re;
    refraction = ra;
    normal_vector = (cross_product(U.normalize_vector(), V.normalize_vector())).normalize_vector();
}
segment_vector Rectangle::U(){
    return u; 
}
segment_vector Rectangle::V(){
    return v;
}
directional_vector Rectangle::N(){
    return normal_vector; 
}
ObjectType Rectangle::type(){
    return ObjectType::Rectangle;
}

std::optional<Intersection_data> Rectangle::intersect(Ray ray){
    segment_vector u = U();
    segment_vector v = V();
    directional_vector n = N();
        bool parallel = std::fabs(dot_product(ray.D(), N())) < 1e-6f;
    if(parallel){ //if its parallel there is no intersection
        return std::nullopt;
    } 
    else { //if not parallel we start calculating the intersection by starting calculating the intersection with the infinite plane
        segment_vector OC_vector = segment_vector(ray.O(), C()); 
        float t = dot_product(N(), OC_vector)/dot_product(ray.D(), N());
        if (t < 0 ){ // if t < 0 then the object is behind the camera
            return std::nullopt;
        } 
        else{ //if not behind we calculate if it intersect not just the infinate plane but the rectangle
            point3D P = ray.trace_ray(t);
            segment_vector w = segment_vector(P, C());
            float u_proj = dot_product(w, U())/dot_product(U(), U());
            float v_proj = dot_product(w, V())/dot_product(V(), V());
            if(0 <= u_proj && 1 >= u_proj && 0 <= v_proj && 1 >= v_proj){
            return Intersection_data(Surface_data() ,P, t); 
            }
            else { return std::nullopt;}
        }
    }
}



Sphere::Sphere(float R, point3D c, Surface s, float re, float ra){
    r = R;
    coordinate = c; 
    surface = s; 
    reflection = re; 
    refraction = ra; 
}
float Sphere::R(){
    return r;
}
ObjectType Sphere::type(){
    return ObjectType::Sphere;
}
std::optional<Intersection_data> Sphere::intersect(Ray ray){
    const float eps = 1e-6f;
    float a = 1;
    segment_vector OC_vector = segment_vector(C(), ray.O());
    float b = 2 * dot_product(ray.D(), OC_vector);
    float r = R();
    float c = dot_product(OC_vector, OC_vector) - r*r;
    float discriminant = b*b - 4*a*c;
    if (discriminant < 0){ //we check for the discriminant if discriminant < 0 there is no real solution for the polinom
        return std::nullopt; 
    } else 
    if (std::fabs(discriminant) < eps){ //only one real solution for the polinom
        float t = -b/(2*a);
            return Intersection_data(Surface_data() ,ray.trace_ray(t), t); 
    } 
    else //two real solutions for the polinom we need the the smaller and greater than 0 else its behind the camera
    {
        float t1 = (-b-sqrt(discriminant))/(2*a);
        float t2 = (-b+sqrt(discriminant))/(2*a);
        if (t1 > 0 && t1 < t2){
            return Intersection_data(Surface_data() ,ray.trace_ray(t1), t1); 
        } else 
        if (t2 > 0){
            return Intersection_data(Surface_data() ,ray.trace_ray(t2), t2); 
        } else 
        {
            return std::nullopt;
        }
    }   
}