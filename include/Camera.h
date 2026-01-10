#ifndef CAMERA_H
#define CAMERA_H
#include "Geometry.h"
#include "Ray.h"
#include "Resolution.h"
#include "Scene.h"

class Camera{
    private: 
        point3D coordinate; 
        directional_vector direction;
        float fov; 
        float aspect_ratio;
        int image_width;
        int image_height;
        float view_port_height;
        float view_port_width;
    public: 
        Camera();
        Camera(point3D coordinate, directional_vector direction, float fov, float aspect_ratio, int width);
        
        directional_vector get_direction();
        point3D get_coordinate();
        float get_image_width();
        float get_image_height();
};
#endif