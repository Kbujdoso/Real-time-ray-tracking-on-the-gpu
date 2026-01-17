#include "Camera.h"
#include "Geometry.h"
#include "Ray.h"
#include "Resolution.h"
#include "Scene.h"
#include "Globals.h"
#include <cmath>

Camera::Camera(){
    coordinate = point3D();
    direction = directional_vector(point3D(0,0,1));
    fov = degree_to_radiant(90);
    aspect_ratio = 0.5f;
    image_width = 1200;
    image_height = static_cast<int>(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;
    view_port_height = 2 * tan(fov/2);
    view_port_width = aspect_ratio * view_port_height;
}



Camera::Camera(point3D c, directional_vector d, float f, float a, int w){
    coordinate = c;
    direction = d;
    fov = degree_to_radiant(f);
    aspect_ratio = a;
    image_width = w;
    image_height = static_cast<int>(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;
    view_port_height = 2 * tan(fov/2);
    view_port_width = aspect_ratio * view_port_height;
}



directional_vector Camera::get_direction(){
    return direction;
}
point3D Camera::get_coordinate(){
    return coordinate;
}
float Camera::get_image_width(){
    return image_width;
}
float Camera::get_image_height(){
    return image_height;
}
float Camera::get_viewport_height(){
    return view_port_height;
}
float Camera::get_viewport_width(){
    return view_port_width;
}
float Camera::get_fov(){
    return fov;
}
float Camera::get_aspect_ratio(){
    return aspect_ratio;
}
