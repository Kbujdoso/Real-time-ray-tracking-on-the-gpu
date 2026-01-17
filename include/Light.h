    #ifndef LIGHT_H
#define LIGHT_H
#include "Color.h"
#include "Geometry.h"
#include "Scene.h"
class Scene; 
struct Intersection_data; 
class Point_Light;
class Light{
    protected:
        Color color;
        public:
        Light();
        Light(Color color);
    public:
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
        Point_Light(point3D Coordinate, float Intensity, Color color);
        point3D C();
        float get_intensity();
        Color get_color();
    };
    Color illuminate(Intersection_data data, Point_Light light, Scene& scene);
    #endif