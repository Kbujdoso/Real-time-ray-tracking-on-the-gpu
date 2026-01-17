#ifndef SURFACE_H
#define SURFACE_H
#include "Color.h"
class Surface{
    private: 
        Color color;
        float shinness;
        float reflectivity;
    public:
        Surface();
        Surface(Color color, float shinness, float reflectivity);
        Color Surface_color();
        float Shinness();
        float Reflectivity();
};
#endif