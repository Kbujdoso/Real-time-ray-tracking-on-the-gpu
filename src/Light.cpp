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

point3D Point_Light::C(){
    return coordinate;
}
float Point_Light::get_intensity(){
    return intensity;
}

Color Light::illuminate(Intersection_data data, Point_Light light){
    point3D c = data.C();
    point3D light_c = light.C();
    directional_vector direction = segment_vector(c, light_c).normalize_vector();
    Ray shadowRay(c + (direction * 0.001f), direction);
    float distance_to_light = magnitude_of_segment_vector(segment_vector(c, light_c));
    float intensity = light.get_intensity();
    auto result = scene.trace(shadowRay);
    if(result && result->T() < distance_to_light){
        return color * 0.1f;
    }
    else{
        float scalar = intensity / distance_to_light;
        return color * scalar;
    }
}
