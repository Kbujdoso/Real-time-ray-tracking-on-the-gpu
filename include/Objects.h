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
public:
        Surface S();
        point3D C();
        float Re();
        float Ra();
        Objects();
        Objects(point3D coordinate, Surface surface, float refraction, float reflection);
        virtual ~Objects() {}
};

class Infinite_Plane : public Objects {
    private: 
        directional_vector direction;
        directional_vector normal_vector;
    public:
    Infinite_Plane();
    Infinite_Plane(point3D coordinate, Surface surface, float refraction, float reflection, directional_vector direction, directional_vector normal_vector);
    directional_vector D();
    directional_vector N();
};

class Rectangle : public Objects{ 
    private: 
        directional_vector u;
        directional_vector v;
    public:
        Rectangle(directional_vector U, directional_vector V, point3D coordinate, Surface surface, float refraction, float reflection);
        directional_vector U();
        directional_vector V();
};

class Sphere : public Objects{
    private:
        float r; 
    public: 
        Sphere(float r, point3D coordinate, Surface surface, float refraction, float reflection);
        float R();

};
#endif


