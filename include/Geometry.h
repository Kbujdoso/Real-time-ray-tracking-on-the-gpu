#ifndef GEOMETRY_H
#define GEOMETRY_H
#include <array>
struct point3D;
struct directional_vector;
struct segment_vector;

struct point3D{
    float x; 
    float y; 
    float z;
    point3D();
    point3D(float x, float y, float z);

};

struct segment_vector{
    point3D p1;
    point3D p2;
        segment_vector();
        segment_vector(point3D p1, point3D p2);
        segment_vector add_vector(segment_vector v);       
        segment_vector multiply_segment_vector(float x);
        directional_vector normalize_vector();
        point3D add_vector_to_point(segment_vector v);
    };
    
    struct directional_vector{
        float x;
    float y; 
    float z;
    directional_vector();
    directional_vector(point3D p);
    segment_vector multiply_directional_vector(float x);
    point3D operator/(float scalar) const;
};

point3D operator+(point3D p,  directional_vector v){
    return point3D(p.x + v.x, p.y + v.y, p.z + v.z);
}
point3D operator-(point3D p,  directional_vector v){
    return point3D(p.x - v.x, p.y - v.y, p.z - v.z);
}

std::array<directional_vector, 2> create_viewport_vectors(directional_vector v);

segment_vector cross_product(const directional_vector& v1, const directional_vector& v2);
float magnitude_of_segment_vector(const segment_vector& v);

#endif