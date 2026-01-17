#include "Globals.h"
#include <cmath>
#include <algorithm>
float degree_to_radiant(float degree){
    return(degree * M_PI / 180);
}

float tone(float x) {
    float m = x / (1.0f + x);     // Reinhard
    m = std::clamp(m, 0.0f, 1.0f);
    m = pow(m, 1.0f / 2.2f);      // gamma correction
    return m;
}

Intersection_data::Intersection_data(){
}
Intersection_data::Intersection_data(Surface S, point3D P, float T, directional_vector N){
    surface = S;
    p = P;
    t = T;
    normal_vector = N;
}
Surface Intersection_data::Surface_data(){
    return surface;
}
point3D Intersection_data::C(){
    return p;
}
float Intersection_data::T(){
    return t;
}
directional_vector Intersection_data::get_normal_vector(){
    return normal_vector;
}
