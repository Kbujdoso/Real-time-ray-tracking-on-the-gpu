#ifndef RAY_H
#define RAY_H
#include "Geometry.h"
#include "Objects.h"
class Ray{
    private:
        point3D origin;
        directional_vector direction;
    public:
        Ray(point3D origin, directional_vector direction);
        point3D trace_ray(float t);
        directional_vector reflection(Objects object);
        directional_vector refraction(Objects object);
        point3D O();
        directional_vector D();
};
#endif