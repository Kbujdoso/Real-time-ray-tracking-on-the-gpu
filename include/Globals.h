#ifndef GLOBAL_H
#define GLOBAL_H
#include "Geometry.h"
#include "Surface.h"

const directional_vector X_AXIS = directional_vector(point3D(1, 0, 0));
const directional_vector Y_AXIS = directional_vector(point3D(0, 1, 0));
const directional_vector Z_AXIS = directional_vector(point3D(0, 0, 1));
float degree_to_radiant(float degree);
float tone(float x);

struct Intersection_data{
    private: 
        Surface surface;
        point3D p;
        float t;
    public:
        Intersection_data();
        Intersection_data(Surface S, point3D P, float T);
        Surface Surface_data();
        point3D C();
        float T();
};
#endif