#ifndef OBJECTS_H
#define OBJECTS_H
#include "Geometry.h"
#include "Surface.h"
#include "ENUMS.h"
#include <optional>

class Scene;
struct Intersection_data;
class Ray;


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
        virtual std::optional<Intersection_data> intersect(Ray ray);
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
    std::optional<Intersection_data> intersect(Ray ray) override;
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
        std::optional<Intersection_data> intersect(Ray ray) override;


};

class Sphere : public Objects{
    private:
        float r; 
    public: 
        Sphere(float r, point3D coordinate, Surface surface, float refraction, float reflection);
        float R();
        ObjectType type() override;
        std::optional<Intersection_data> intersect(Ray ray) override;
};

#endif


