#include "Objects.h"
#include "Geometry.h"
#include "Surface.h"
#include "ENUMS.h"

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


Infinite_Plane::Infinite_Plane(point3D c, Surface s, float ra, float re, directional_vector d, directional_vector n){
    coordinate = c;
    surface = s; 
    refraction = ra;
    reflection = re; 
    direction = d;
    normal_vector = n;
}
directional_vector Infinite_Plane::D(){
    return direction;
}
directional_vector Infinite_Plane::N(){
    return normal_vector;
}
ObjectType Infinite_Plane::type(){
    return ObjectType::Infinite_plane;
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