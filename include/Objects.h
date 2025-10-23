#ifndef OBJECTS_H
#define OBJECTS_H
#include "Geometry.h"
#include "Surface.h"
class Objects{
    protected:
        float reflection;
        float refraction;
        point3D coordinate; 
        Surface surface;
        Surface get_surface();
        point3D get_coordinate();
        float get_refraction();
        float get_reflection();
    public:
        Objects(point3D coordinate, Surface surface, float refraction, float reflection);
        virtual ~Objects() {}
};


class Plane : public Objects{ 
    private: 
        directional_vector U;
        directional_vector V;
    public:
        Plane(directional_vector U, directional_vector V, point3D coordinate, Surface surface, float refraction, float reflection);
        directional_vector get_U();
        directional_vector get_V();
};

class Sphere : public Objects{
    private:
        float r; 
    public: 
        Sphere(float r, point3D coordinate, Surface surface, float refraction, float reflection);
        float get_radius();

};
#endif


