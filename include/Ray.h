#ifndef RAY_H
#define RAY_H
#include "Geometry.h"
#include "Objects.h"
class Objects;
class Ray{
    private:
        point3D origin;
        directional_vector direction;
    public:
        Ray(point3D origin, directional_vector direction);
        point3D trace_ray(float t);
        directional_vector reflection(const Objects& object);
        directional_vector refraction(const Objects& object);
        point3D O();
        directional_vector D();
};
#endif