#ifndef LIGHT_H
#define LIGHT_H
#include "Color.h"
#include "Geometry.h"
#include "Scene.h"
class Light{
    protected:
        Color color;
        Scene scene;
        virtual Color illuminate(point3D point, directional_vector normal, Color color,Point_Light Light);
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
        Directional_Light(Color color, directional_vector Direction, Scene scene);
};
class Point_Light : public Light{
    private: 
        point3D coordinate;
        float intensity;
    public:
        Point_Light();
        Point_Light(point3D Coordinate, float Intensity, Scene scene);
        point3D get_coordinate();
        float get_intensity();
};
#endif