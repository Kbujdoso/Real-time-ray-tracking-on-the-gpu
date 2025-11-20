#include "Light.h"
#include "Color.h"
#include "Geometry.h"
#include "Ray.h"
#include "Scene.h"
Light::Light(){
    color = Color();
}
Light::Light(Color c){
    color = c;
}
Directional_Light::Directional_Light(){
    color = Color();
    direction = directional_vector();
}
Directional_Light::Directional_Light(Color c, directional_vector Direction, Scene Scene){
    color = c; 
    direction = Direction;
    scene = Scene;
}

directional_vector Directional_Light::get_direction(){
    return direction;
}

Point_Light::Point_Light(){
    coordinate = point3D();
    intensity = 1;
}
Point_Light::Point_Light(point3D Coordinate, float Intensity, Scene Scene){
    coordinate = Coordinate;
    intensity = Intensity;
    scene = Scene;
}

point3D Point_Light::get_coordinate(){
    return coordinate;
}
float Point_Light::get_intensity(){
    return intensity;
}

Color Light::illuminate(point3D c, directional_vector n, Color color, Point_Light light){
    Ray shadowRay = Ray(c, n);
    auto result = scene.trace(shadowRay);
    if(result){
        return color * 0.1; 
    }
    else{
        float scalar = light.get_intensity() / magnitude_of_segment_vector(segment_vector(c, light.get_coordinate()));
        return color * scalar;
    }
}
