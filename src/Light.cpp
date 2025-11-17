#include "Light.h"
#include "Color.h"
#include "Geometry.h"

Light::Light(){
    color = Color();
}
Light::Light(Color c){
    color = c;
}
Color Light::illuminate(point3D point, directional_vector normal){
    return Color();
}
Directional_Light::Directional_Light(){
    color = Color();
    direction = directional_vector();
}
Directional_Light::Directional_Light(Color c, directional_vector Direction){
    color = c; 
    direction = Direction;
}

directional_vector Directional_Light::get_direction(){
    return direction;
}

Point_Light::Point_Light(){
    coordinate = point3D();
    intensity = 1;
}
Point_Light::Point_Light(point3D Coordinate, float Intensity){
    coordinate = Coordinate;
    intensity = Intensity;
}

point3D Point_Light::get_coordinate(){
    return coordinate;
}
float Point_Light::get_intensity(){
    return intensity;
}
