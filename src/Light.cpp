#include "Light.h"
#include "Color.h"
#include "Geometry.h"
#include "Ray.h"
#include "Scene.h"
#include <cmath>
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
Point_Light::Point_Light(point3D Coordinate, float Intensity, Color c){
    coordinate = Coordinate;
    intensity = Intensity;
    color = c;
}

point3D Point_Light::C(){
    return coordinate;
}
float Point_Light::get_intensity(){
    return intensity;
}
Color Point_Light::get_color(){
    return color;
}

/*Color illuminate(Intersection_data data, Point_Light light, Scene& scene){
    point3D c = data.C();
    point3D light_c = light.C();
    Color color = light.get_color();
    directional_vector direction = segment_vector(c, light_c).normalize_vector();
    Ray shadowRay(c + (direction * 0.001f), direction);
    float distance_to_light = magnitude_of_segment_vector(segment_vector(c, light_c));
    float intensity = light.get_intensity();
    auto result = scene.trace(shadowRay);
    if(result && result->T() < distance_to_light){
        return color * 0.1f;
    }
    else{
        float scalar = intensity / std::pow(distance_to_light, 2);
        return color * scalar;
    }
} */

Color illuminate(Intersection_data data, Point_Light light,  Scene& scene) {
    point3D c = data.C();
    point3D light_c = light.C();
    Color light_color = light.get_color();
    Color object_color = data.Surface_data().Surface_color();
    directional_vector N = data.get_normal_vector();    

    directional_vector L_dir = segment_vector(c, light_c).normalize_vector();
    float distance_to_light = magnitude_of_segment_vector(segment_vector(c, light_c));

    Ray shadowRay(c + (N * 0.001f), L_dir);
    auto result = scene.trace(shadowRay);
    Color ambient = object_color * 0.1f;

    if (result && result->T() < distance_to_light) {
        
        return ambient; 
    }
    float cos_theta = std::max(0.0f, dot_product(N, L_dir));
    float intensity = light.get_intensity();
    float attenuation = intensity / std::pow(distance_to_light, 2);
    Color diffuse = (object_color * light_color) * (cos_theta * attenuation);
    return ambient + diffuse;
}