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
__kernel void trace(){

}
void trace_ray(const float t){

}
__kernel void illuminate(){}

__kernel void kernel_render(){}

GPU_Intersection_data intersect_sphere(const GPU_Object sphere, Ray ray) {
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
GPU_Intersection_data intersect_rectangle(GPU_Object rectangle, Ray ray){
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

    float3 OC = rectangle.position.xyz - ray.origin.xyz;
    float t = dot(normal.xyz, OC)/dot(ray.direction.xyz, normal.xyz);
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

