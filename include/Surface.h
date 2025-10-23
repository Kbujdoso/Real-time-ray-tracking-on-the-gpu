#ifndef SURFACE_H
#define SURFACE_H
#include "Color.h"
class Surface{
    public: 
        Color color;
        float shinness;
        float reflectivity;
        Surface();
        Surface(Color color, float shinness, float reflectivity);
};
#endif