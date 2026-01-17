#ifndef GPU_STRUCT_H
#define GPU_STRUCT_H

#ifdef __cplusplus
    #include <CL/cl.h> 
    typedef cl_float4 float4;
    typedef cl_int   int1; 
    typedef cl_float3 float3;
#endif

typedef struct {
    int type; 
    float radius;
    float reflection;   
    float shineness;
    float4 normal;
    float4 u;
    float4 v; 
    float4 color;
    float4 position;
} GPU_Object;

typedef struct{
    float4 position;
    float4 direction;
    float4 view_port_left_up;
    float4 pixel_delta_right;
    float4 pixel_delta_down;
    float image_height;
    float image_width;
    float dummy1;
    float dummy2;
} GPU_Camera;

typedef struct{
    float4 position;
    float4 color;
    float intensity;
    float dummy[3];
} GPU_Light;
#endif