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
    float dx; 
    float dy; 
    float dz;
        segment_vector();
        segment_vector(point3D p1, point3D p2);
        segment_vector add_vector(segment_vector v);       
        segment_vector multiply_segment_vector(float x);
        directional_vector normalize_vector();
        point3D add_vector_to_point(segment_vector v);
        segment_vector abs_vector();
    };
    
struct directional_vector{
    float x;
    float y; 
    float z;
    explicit directional_vector();
    explicit directional_vector(point3D p);
    segment_vector multiply_directional_vector(float x);
};

point3D operator+(point3D p, directional_vector v);
point3D operator-(point3D p, directional_vector v);
point3D operator/(directional_vector v, float scalar);
point3D operator/(point3D p, float scalar);
point3D operator*(point3D p, float scalar);
point3D operator*(directional_vector v, float scalar);
point3D operator+(point3D p1, point3D p2);
point3D operator-(point3D p1, point3D p2);
std::array<directional_vector, 2> create_viewport_vectors(const directional_vector& v);

segment_vector cross_product(const directional_vector& v1, const directional_vector& v2);
float dot_product(const directional_vector& v1, const segment_vector& v2);
float dot_product(const segment_vector&v1, const segment_vector& v2);
float dot_product(const directional_vector& v1, const directional_vector& v2);
float magnitude_of_segment_vector(const segment_vector& v);

directional_vector calculate_direction();
#endif