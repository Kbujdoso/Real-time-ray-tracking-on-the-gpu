#include "Renderer.h"
#include <array>
#include "Geometry.h"
#include "Scene.h"
#include <fstream>
#include <algorithm>
#include <cmath>
#include "Globals.h"
Renderer::Renderer(Camera c, Scene& s, Point_Light l) 
    : camera(c), scene(s), light(l)
{}




void Renderer::render(){
    point3D cam_pos = camera.get_coordinate();
    directional_vector direction = camera.get_direction();
    std::array<directional_vector, 2> helpers = create_viewport_vectors(direction); 
    directional_vector down = helpers[0];
    directional_vector right = helpers[1];
    float image_height = camera.get_image_height();
    float image_width = camera.get_image_width();
    float v_height = camera.get_viewport_height(); 
    float v_width = camera.get_viewport_width();
    point3D viewport_center = cam_pos + direction; 


    point3D viewport_left_up = viewport_center 
                            - (right * (v_width / 2.0f)) 
                            - (down * (v_height / 2.0f));    
    point3D pixel_right  = right * v_width;
    point3D pixel_down = down * v_height;
    point3D pixel_delta_right = pixel_right / image_width;
    point3D pixel_delta_down = pixel_down / image_height;
    std::ofstream out("output.ppm");
    out << "P3\n" << image_width << " " << image_height << "\n255\n";

    for(int i = 0;i < image_height; i++)
    {
        for (int j = 0; j < image_width; j++)
        {
            Color color;
            point3D pixel_center = viewport_left_up 
                            + (pixel_delta_right * j) 
                            + (pixel_delta_down * i);
            directional_vector ray_direction = segment_vector(cam_pos, pixel_center).normalize_vector();
            Ray ray = Ray(cam_pos, ray_direction);
            auto opt_intersection_data = scene.trace(ray);
            Intersection_data intersection_data;
            if (opt_intersection_data != std::nullopt) {
                intersection_data = *opt_intersection_data; 
                color = illuminate(intersection_data, light ,scene);
            } else {
                color = Color(30.0f, 30.0f, 30.0f);
            }

            int r = std::round((color.Red()));
            int g = std::round(color.Green());
            int b = std::round(color.Blue());
            out << r << " " << g << " " << b << "\n";
        }

    }
    out.close();
}