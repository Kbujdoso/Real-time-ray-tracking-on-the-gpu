#define CL_HPP_TARGET_OPENCL_VERSION 300 
#include <CL/opencl.hpp>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <array>
#include <algorithm>
#include <cmath>
#include <vector>

#include "GPU_Struct.h"
#include "Renderer.h"
#include "Geometry.h"
#include "Scene.h"
#include "Globals.h"
Renderer::Renderer(Camera c, Scene& s, Point_Light l) 
    : camera(c), scene(s), light(l)
{}

std::vector<GPU_Object> Renderer::prepareSceneForGPU(){
    std::vector<GPU_Object> objects;
    for(const auto& obj : scene.get_Objects()){
        GPU_Object object {};
        Color color = obj->Surface_data().Surface_color();
        point3D coordinate = obj->C();
        object.color = {{float(color.Red()), float(color.Green()),  float(color.Blue()), 0.0f}};
        object.position = {{coordinate.x, coordinate.y, coordinate.z, 0.0f}};
        object.reflection = 0.0f;
        object.shineness = 0.0f;
        switch (obj -> type())
        {
        case ObjectType::Infinite_plane: {
            Infinite_Plane* p = static_cast<Infinite_Plane*>(obj.get());
            object.type = 0;
            directional_vector normal = p->N();
            object.normal = {{normal.x, normal.y, normal.z, 0.0f}};
            break;
        }
        case ObjectType::Rectangle: {
            Rectangle* r = static_cast<Rectangle*>(obj.get());
            object.type = 1;
            directional_vector normal = r->N();
            object.normal = {{normal.x, normal.y, normal.z, 0.0f}};
            segment_vector  u = r->U();
            object.u = {{u.dx, u.dy, u.dz, 0.0f}};
            segment_vector v = r->V();
            object.v = {{v.dx, v.dy, v.dz, 0.0f}};
            break;
        }
        case ObjectType::Sphere: {
            Sphere* s = static_cast<Sphere*>(obj.get());
            object.type = 2;
            object.radius = s->R();
            break;
        }
        default:
            break;
        }
        objects.push_back(object);
    }
    return objects;
}

GPU_Camera Renderer::prepareCameraForGPU(){
    GPU_Camera GPU_camera = {};
    point3D position = camera.get_coordinate();
    directional_vector direction = camera.get_direction();
    std::array<directional_vector, 2> helpers = create_viewport_vectors(direction); 
    directional_vector down = helpers[0];
    directional_vector right = helpers[1];
    float image_height = camera.get_image_height();
    float image_width = camera.get_image_width();
    float v_height = camera.get_viewport_height(); 
    float v_width = camera.get_viewport_width();
    point3D viewport_center = position + direction; 


    point3D viewport_left_up = viewport_center 
                            - (right * (v_width / 2.0f)) 
                            - (down * (v_height / 2.0f));    
    point3D pixel_right  = right * v_width;
    point3D pixel_down = down * v_height;
    point3D pixel_delta_right = pixel_right / image_width;
    point3D pixel_delta_down = pixel_down / image_height;

    GPU_camera.position = {{position.x, position.y, position.z, 0.0f}};
    GPU_camera.direction = {{direction.x, direction.y, direction.z, 0.0f}};
    GPU_camera.view_port_left_up = {{viewport_left_up.x, viewport_left_up.y, viewport_left_up.z, 0.0f}};
    GPU_camera.pixel_delta_down = {{pixel_delta_down.x, pixel_delta_down.y, pixel_delta_down.z, 0.0f}};
    GPU_camera.pixel_delta_right = {{pixel_delta_right.x, pixel_delta_right.y, pixel_delta_right.z, 0.0f}};
    GPU_camera.image_height = image_height;
    GPU_camera.image_width = image_width;
    GPU_camera.dummy1 = 0.0f;
    GPU_camera.dummy2 = 0.0f;

    return GPU_camera;
}

GPU_Light Renderer::prepareLightForGPU(){
    GPU_Light GPU_light = {};
    point3D position = light.C();
    float intensity = light.get_intensity();
    Color color = light.get_color();

    GPU_light.position = {{position.x, position.y, position.z, 0.0f}};
    GPU_light.color = {{float(color.Red()), float(color.Green()),  float(color.Blue()), 0.0f}};
    GPU_light.intensity = intensity;
    GPU_light.dummy[0] = 0.0f;
    GPU_light.dummy[1] = 0.0f;
    GPU_light.dummy[2] = 0.0f;

    return GPU_light;
}

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
void Renderer::new_render(){
    
    std::vector<cl::Platform> platforms;
    cl::Platform::get(&platforms);
    cl::Platform default_platform = platforms[0];
    
    std::vector<cl::Device> all_devices;
    default_platform.getDevices(CL_DEVICE_TYPE_ALL, &all_devices);
    cl::Device default_device = all_devices[0];
    
    cl::Context context({default_device});
    
    std::vector<GPU_Object> objects_h = prepareSceneForGPU();
    GPU_Camera camera_h = prepareCameraForGPU();
    GPU_Light light_h = prepareLightForGPU();

    cl::Buffer objects_d(context, CL_MEM_READ_ONLY, objects_h.size()*sizeof(GPU_Object));
    cl::Buffer camera_d(context, CL_MEM_READ_ONLY, sizeof(GPU_Camera));
    cl::Buffer light_d(context, CL_MEM_READ_ONLY, sizeof(GPU_Light));

    cl::CommandQueue queue(context, default_device);

    queue.enqueueWriteBuffer(objects_d, CL_TRUE, 0, objects_h.size()*sizeof(GPU_Object), objects_h.data());
    queue.enqueueWriteBuffer(camera_d, CL_TRUE, 0, sizeof(GPU_Camera), &camera_h);
    queue.enqueueWriteBuffer(light_d, CL_TRUE, 0, sizeof(GPU_Light), &light_h);

    std::ifstream kernelFile("raytracer_kernel.cl");
    std::stringstream buffer;
       buffer << kernelFile.rdbuf();

    std::string kernel_code = buffer.str();
    
    cl::Program::Sources sources;
    sources.push_back({kernel_code.c_str(), kernel_code.length()});

    cl::Program program(context, sources);

    if (program.build({ default_device }) != CL_SUCCESS) {
        std::cout << " Error building: " << program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(default_device) << "\n";
        exit(1);
    }


}