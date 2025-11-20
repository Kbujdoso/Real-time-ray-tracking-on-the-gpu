#ifndef OBJECTS_H
#define OBJECTS_H
#include "Geometry.h"
#include "Surface.h"
#include "ENUMS.h"
class Objects{
    protected:
        float reflection;
        float refraction;
        point3D coordinate; 
        Surface surface;
public:
        Surface Surface_data();
        point3D C();
        float Re();
        float Ra();
        Objects();
        Objects(point3D coordinate, Surface surface, float refraction, float reflection);
        virtual ~Objects() {}
        virtual ObjectType type();
};

class Infinite_Plane : public Objects {
    private: 
        directional_vector normal_vector;
    public:
    Infinite_Plane();
    Infinite_Plane(point3D coordinate, Surface surface, float refraction, float reflection, directional_vector normal_vector);
    directional_vector D();
    directional_vector N();
    ObjectType type() override;
};

class Rectangle : public Objects{ 
    private: 
        segment_vector u;
        segment_vector v;
        directional_vector normal_vector; 
    public:
        Rectangle(segment_vector U, segment_vector V, point3D coordinate, Surface surface, float refraction, float reflection);
        segment_vector U();
        segment_vector V();
        directional_vector N();
        ObjectType type() override;

};

class Sphere : public Objects{
    private:
        float r; 
    public: 
        Sphere(float r, point3D coordinate, Surface surface, float refraction, float reflection);
        float R();
        ObjectType type() override;


};

#endif


