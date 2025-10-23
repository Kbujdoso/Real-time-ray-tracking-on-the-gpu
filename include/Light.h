#ifndef LIGHT_H
#define LIGHT_H
#include "Color.h"
#include "Geometry.h"
class Light{
    protected:
        Color color;
        virtual Color illuminate(point3D point, directional_vector normal);
};
class Directional : public Light{
    private:
        directional_vector direction;
    public:
        directional_vector get_direction();
};
class Point : public Light{
    private: 
        point3D coordinate;
        float intensity;
    public:
        point3D get_coordinate();
        float get_intensity();
};
#endif