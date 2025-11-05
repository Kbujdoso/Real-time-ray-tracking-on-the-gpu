#include "Geometry.h"
#include "math.h"
#include "Globals.h"

point3D::point3D() : x(0), y(0), z(0) {}
point3D::point3D(float x_val, float y_val, float z_val) {
    x = x_val;
    y = y_val;
    z = z_val;
}

segment_vector::segment_vector() : p1(point3D()), p2(point3D()){}

segment_vector::segment_vector(point3D p1_val, point3D p2_val){
    p1 = p1_val;
    p2 = p2_val;
    dx = p1.x - p2.x;
    dy = p1.y - p2.y;
    dz = p1.z - p2.z;
}

directional_vector segment_vector::normalize_vector(){
    float dx = p2.x - p1.x;
    float dy = p2.y - p1.y;
    float dz = p2.z - p1.z;

    float magnitude = std::sqrt(dx*dx + dy*dy + dz*dz);
    if (magnitude != 0){
        dx = dx / magnitude;
        dy = dy / magnitude; 
        dz = dz / magnitude;
    }
    point3D p = point3D(dx , dy, dz);
    return directional_vector(p);
}

segment_vector segment_vector::multiply_segment_vector(float scalar){
    float x_temp = (p2.x - p1.x) * scalar + p1.x;
    float y_temp = (p2.y - p1.y) * scalar + p1.y;
    float z_temp = (p2.z - p1.z) * scalar + p1.z;
    point3D p3(x_temp, y_temp, z_temp);
    return segment_vector(p1, p3);
}

segment_vector segment_vector::add_vector(segment_vector v){
    float dx = (p2.x - p1.x) + (v.p2.x - v.p1.x);
    float dy = (p2.y - p1.y) + (v.p2.y - v.p1.y);
    float dz = (p2.z - p1.z) + (v.p2.z - v.p1.z);
    point3D p3 = point3D(p1.x + dx,p1.y + dy,p1.z+ dz);
    return segment_vector(p1, p3);
}





directional_vector::directional_vector() : x(0), y(0), z(0)   {}
directional_vector::directional_vector(point3D p){
    float magnitude = std::sqrt(p.x*p.x + p.y*p.y + p.z*p.z);
    if (magnitude != 0){
        x = p.x / magnitude;
    y = p.y / magnitude;
    z = p.z / magnitude;
} else {
    x = y = z = 0;
}
}

segment_vector directional_vector::multiply_directional_vector(float scalar){
    point3D p1 = point3D();
    point3D p2 = point3D(x * scalar, y * scalar, z * scalar);
    return segment_vector(p1, p2);
}
segment_vector cross_product(const directional_vector& v1, const directional_vector& v2){
    return (segment_vector(point3D(), point3D(
        v1.x*v2.z - v1.z*v2.y,
        v1.z*v2.x - v1.x*v2.z,
        v1.x*v2.y - v1.y*v2.x
    )));
}
float magnitude_of_segment_vector(const segment_vector& v){
    float dx = v.p2.x-v.p1.x;
    float dy = v.p2.y-v.p1.y;
    float dz = v.p2.z-v.p1.z;
    return std::sqrt(dx * dx + dy * dy + dz * dz);
}

std::array<directional_vector,2> create_viewport_vectors(const directional_vector& v){
    directional_vector helper;
    if (v.x < 0.9){
        helper = directional_vector(point3D(1, 0, 0));}
        else {
            helper = directional_vector(point3D(0, 1, 0));}
    segment_vector cross = cross_product(helper, v);
    directional_vector t1 = cross.normalize_vector();
    cross = cross_product(v, t1);
    directional_vector t2 = cross.normalize_vector();
    return {t1, t2};
}




point3D operator+(point3D p,  directional_vector v){
    return point3D(p.x + v.x, p.y + v.y, p.z + v.z);
}
point3D operator-(point3D p,  directional_vector v){
    return point3D(p.x - v.x, p.y - v.y, p.z - v.z);
}
point3D operator/(directional_vector v, float scalar){
    return point3D(v.x / scalar, v.y / scalar, v.z / scalar);
}
point3D operator*(point3D p, float scalar){
    return point3D(p.x * scalar, p.y * scalar, p.z *scalar);
}

float dot_product(const directional_vector& v1, const segment_vector& v2){
    return v1.x * v2.dx + v1.y * v2.dy + v1.z * v2.dz;
}
float dot_product(const segment_vector& v1, const segment_vector& v2){
    return v1.dx * v2.dx + v1.dy * v2.dy, v1.dz * v2.dz;
}
float dot_product(const directional_vector& v1, const directional_vector& v2){
    return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
}