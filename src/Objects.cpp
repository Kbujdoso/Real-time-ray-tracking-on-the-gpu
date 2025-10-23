#include "Objects.h"
#include "Geometry.h"
#include "Surface.h"

Objects::Objects(point3D c, Surface s, float ra, float re){
    coordinate = c;
    surface = s; 
    refraction = ra;
    reflection = re;
}
Objects::Objects(){}

Surface Objects::S(){
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
Plane::Plane(directional_vector U, directional_vector V, point3D c, Surface s, float re, float ra){
    u = U;
    v = V; 
    coordinate = c; 
    surface = s; 
    reflection = re;
    refraction = ra;
}
directional_vector Plane::U(){
    return u; 
}
directional_vector Plane::V(){
    return v;
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