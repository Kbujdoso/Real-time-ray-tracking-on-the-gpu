#include "Ray.h"
#include "Geometry.h"
#include "Objects.h"

Ray::Ray(point3D o, directional_vector d){
    origin = o; 
    direction = d;
}

point3D Ray::trace_ray(float t){
    segment_vector distance = direction.multiply_directional_vector(t);
    point3D traced_point = origin;
    traced_point.x = origin.x + distance.p2.x;
    traced_point.y = origin.y + distance.p2.y;
    traced_point.z = origin.z + distance.p2.z;
    return traced_point;
}

point3D Ray::O(){
    return origin;
}
directional_vector Ray::D(){
    return direction;
}
directional_vector Ray::reflection(const Objects& o){}

directional_vector Ray::refraction(const Objects& o){}

