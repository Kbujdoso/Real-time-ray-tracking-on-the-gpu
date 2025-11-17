#ifndef LIGHT_H
#define LIGHT_H
#include "Color.h"
#include "Geometry.h"
class Light{
    protected:
        Color color;
        virtual Color illuminate(point3D point, directional_vector normal);
    public:
        Light();
        Light(Color color);
};
class Directional_Light : public Light{
    private:
        directional_vector direction;
    public:
        directional_vector get_direction();
        Directional_Light();
        Directional_Light(Color color, directional_vector Direction);
};
class Point_Light : public Light{
    private: 
        point3D coordinate;
        float intensity;
    public:
        Point_Light();
        Point_Light(point3D Coordinate, float intensity);
        point3D get_coordinate();
        float get_intensity();
};
#endif