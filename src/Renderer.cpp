#include "Renderer.h"
#include <array>
#include "Geometry.h"
Renderer::Renderer(const Camera& c, const Scene& s, const Resolution& r){
    camera = c;
    scene = s;
    resolution = r;
}




void Renderer::render(){
    directional_vector direction = camera.get_direction();
    std::array<directional_vector, 2> helpers = create_viewport_vectors(direction); 
    directional_vector right = helpers[0];
    directional_vector up = helpers[1];
    float image_height = camera.get_image_height();
    float image_width = camera.get_image_width();
    point3D coordinate = camera.get_coordinate();
    point3D viewport_center = coordinate + direction;
    point3D viewport_left_up = viewport_center + (up / 2.0) - (right / 2.0);
    

}