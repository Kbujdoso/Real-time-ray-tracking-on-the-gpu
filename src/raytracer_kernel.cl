#include "GPU_Struct.h"
typedef struct{
    int red;
    int green;
    int blue;
    int dummy;
}Color;

typedef struct{
    float4 direction;
    float4 origin;
}Ray;

typedef struct{
    bool exists;
    float t;
    float3 normal;
    float3 position;
    float3 color;
} GPU_Intersection_data;


GPU_Intersection_data intersect_sphere(const GPU_Object sphere, const Ray ray) {
    GPU_Intersection_data gpu_int;
    gpu_int.exists = false;

    const float eps = 0.001f; 
    
    float3 OC = ray.origin.xyz - sphere.position.xyz;
    float b = 2.0f * dot(ray.direction.xyz, OC);
    float r = sphere.radius;
    float c = dot(OC, OC) - r * r;
    
    float discriminant = b * b - 4.0f * c;

    if (discriminant < 0.0f) return gpu_int;

    float sqrtD = sqrt(discriminant);
    float t1 = (-b - sqrtD) / 2.0f;
    float t2 = (-b + sqrtD) / 2.0f;

    float t = -1.0f;
    if (t1 > eps && t1 < t2) {
        t = t1;
    } else if (t2 > eps) {
        t = t2;
    } else {
        return gpu_int; 
    }

    gpu_int.exists = true;
    gpu_int.t = t;
    gpu_int.position = ray.origin.xyz + t * ray.direction.xyz;
    gpu_int.normal = normalize(gpu_int.position - sphere.position.xyz);
    gpu_int.color = sphere.color.xyz;
    return gpu_int;
}
GPU_Intersection_data intersect_rectangle(const GPU_Object rectangle, const Ray ray){
    GPU_Intersection_data gpu_int;
    gpu_int.exists = false;
    const float eps = 0.001f; 
    float4 u = rectangle.u;
    float4 v = rectangle.v;
    float4 normal = rectangle.normal;
        bool parallel = fabs(dot(ray.direction.xyz, normal.xyz)) < 1e-6f;
    if(parallel){ //if its parallel there is no intersection
        return gpu_int;
    } 

    float3 CO = rectangle.position.xyz - ray.origin.xyz;
    float t = dot(normal.xyz, CO)/dot(ray.direction.xyz, normal.xyz);
    if (t < 0.0f ){ // if t < 0 then the object is behind the camera
        return gpu_int;
    }
    //if not behind we calculate if it intersect not just the infinate plane but the rectangle
    float3 hit_point = ray.origin.xyz + t * ray.direction.xyz;
    float3 w = hit_point - rectangle.position.xyz;
    float u_proj = dot(w, rectangle.u.xyz)/dot(rectangle.u.xyz, rectangle.u.xyz);
    float v_proj = dot(w, rectangle.v.xyz)/dot(rectangle.v.xyz, rectangle.v.xyz);
    if(0 <= u_proj && 1 >= u_proj && 0 <= v_proj && 1 >= v_proj){
        gpu_int.exists = true;
        gpu_int.t = t;
        gpu_int.position = hit_point;
        gpu_int.normal = rectangle.normal.xyz;
        gpu_int.color = rectangle.color.xyz;
        return gpu_int; }
    return gpu_int;

}

GPU_Intersection_data intersect_infiniteplane(const GPU_Object infinite_plane , const Ray ray){
    bool parallel = fabs(dot(ray.direction.xyz, infinite_plane.normal.xyz)) < 1e-6f;
    GPU_Intersection_data gpu_int;
    gpu_int.exists = false;
    if(parallel){ //if its paralel there is no intersection
        return gpu_int; }
    float3 OC_vector = infinite_plane.position.xyz - ray.origin.xyz;
    float t = dot(infinite_plane.normal.xyz, OC_vector)/dot(ray.direction.xyz, infinite_plane.normal.xyz);
    if (t < 0 ){ // if t < 0 the object is behind the camera
        return gpu_int; }
    gpu_int.exists = true;
    gpu_int.t = t;
    gpu_int.position = ray.origin.xyz + t * ray.direction.xyz;
    gpu_int.normal = infinite_plane.normal.xyz;
    gpu_int.color = infinite_plane.color.xyz;
    return gpu_int;  
}

GPU_Intersection_data trace(const Ray ray, __global GPU_Object* objects, int num_objects){
    GPU_Intersection_data closest_hit = {};
    closest_hit.exists = false;
    float min_t = INFINITY;
    for (int i  = 0; i < num_objects; i++) {
        GPU_Intersection_data current_hit = {};

        GPU_Object object = objects[i];
        switch(object.type){
            case 0:
                current_hit = intersect_infiniteplane(object, ray);
            break;
            case 1:
                current_hit = intersect_rectangle(object, ray);
            break;
            case 2:
                current_hit = intersect_sphere(object, ray);
            break;

        }

        if (current_hit.exists) {

            if (current_hit.t < min_t) {
                min_t = current_hit.t;
                closest_hit = current_hit;
            }
        }
    }

    return closest_hit;
}


float3 illuminate(GPU_Intersection_data data, GPU_Light light, __global GPU_Object* objects, int num_objects){
    float3 position = data.position;
    float3 light_position = light.position.xyz;
    float3 light_color = light.color.xyz;
    float3 object_color = data.color;
    float3 normal = data.normal;    

    float3 L_dir = normalize(light_position - position);
    float distance_to_light = distance(position, light_position);

    Ray shadowRay = {};
    shadowRay.origin.xyz = position + normal * 0.001f;
    shadowRay.direction.xyz = L_dir;
    GPU_Intersection_data gpu_int = {};
    gpu_int = trace(shadowRay, objects, num_objects);
    float3 ambient = object_color * 0.1f;

    if (gpu_int.exists && gpu_int.t < distance_to_light) {
        
        return ambient; 
    }
    float cos_theta = max(0.0f, dot(normal, L_dir));
    float intensity = light.intensity;
    float attenuation = intensity / (1.0f + distance_to_light * distance_to_light);
    float3 diffuse = (object_color * light_color) * (cos_theta * attenuation);
    return ambient + diffuse;
 }



__kernel void kernel_render(__global float3* output_image, GPU_Camera camera, GPU_Light light, __global GPU_Object* objects, int num_objects){
    int j = get_global_id(0);
    int i = get_global_id(1);
    if ( j >= camera.image_width || i >= camera.image_height)return;
    float3 pixel_center = camera.view_port_left_up.xyz 
                        + (camera.pixel_delta_right.xyz * (float)j) 
                        + (camera.pixel_delta_down.xyz * (float)i);
    float3 ray_direction = normalize(pixel_center -camera.position.xyz);
    Ray ray = {};
    ray.origin.xyz = camera.position.xyz;
    ray.direction.xyz = ray_direction;
    GPU_Intersection_data intersection_data = trace(ray, objects, num_objects); 
    float3 final_color;
    if (intersection_data.exists) {
        final_color = illuminate(intersection_data, light, objects, num_objects);
    } else {
        final_color = (float3)(30.0f, 30.0f, 30.0f);
    }
    int pixel_index = i * camera.image_width + j;
    output_image[pixel_index] = final_color;
}