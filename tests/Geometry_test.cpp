#include <gtest/gtest.h>
#include "Geometry.h"
#include <cmath>
TEST(normalize_vector, CorrectType) {
    segment_vector sv({0,0,0}, {1,0,0});
    auto result = sv.normalize_vector();
    static_assert(std::is_same_v<decltype(result), directional_vector>, "returns a directional vector");
}

TEST(normalize_vector, CorrectOutPut){
    
    segment_vector sv1({2,4,6}, {-2,1,6});
    auto dv1 = sv1.normalize_vector();
    EXPECT_NEAR(dv1.x, -0.8f, 1e-4);
    EXPECT_NEAR(dv1.y, -0.6f, 1e-4);
    EXPECT_NEAR(dv1.z, 0.0f, 1e-4);

    segment_vector sv2({0,0,0}, {5,0,0});
    auto dv2 = sv2.normalize_vector();
    EXPECT_NEAR(dv2.x, 1.0f, 1e-4);
    EXPECT_NEAR(dv2.y, 0.0f, 1e-4);
    EXPECT_NEAR(dv2.z, 0.0f, 1e-4);

    segment_vector sv3({0,0,0}, {0,-3,0});
    auto dv3 = sv3.normalize_vector();
    EXPECT_NEAR(dv3.x, 0.0f, 1e-4);
    EXPECT_NEAR(dv3.y, -1.0f, 1e-4);
    EXPECT_NEAR(dv3.z, 0.0f, 1e-4);

    segment_vector sv4({1,1,1}, {1,1,4});
    auto dv4 = sv4.normalize_vector();
    EXPECT_NEAR(dv4.x, 0.0f, 1e-4);
    EXPECT_NEAR(dv4.y, 0.0f, 1e-4);
    EXPECT_NEAR(dv4.z, 1.0f, 1e-4);
    
    segment_vector sv5({0,0,0}, {1,1,1});
    auto dv5 = sv5.normalize_vector();
    float diag = std::sqrt(3.0f);
    EXPECT_NEAR(dv5.x, 1.0f/diag, 1e-4);
    EXPECT_NEAR(dv5.y, 1.0f/diag, 1e-4);
    EXPECT_NEAR(dv5.z, 1.0f/diag, 1e-4);
    
    segment_vector sv6({-1,2,-3}, {2,-1,3});
    auto dv6 = sv6.normalize_vector();
    float dx = 2 - (-1);  
    float dy = -1 - 2;    
    float dz = 3 - (-3); 
    float mag = std::sqrt(dx*dx + dy*dy + dz*dz);
    EXPECT_NEAR(dv6.x, dx/mag, 1e-4);
    EXPECT_NEAR(dv6.y, dy/mag, 1e-4);
    EXPECT_NEAR(dv6.z, dz/mag, 1e-4);
}
TEST(multiply_segment_vector, CorrectType){
    segment_vector sv({1,1,1}, {2,2,2});
    auto result = sv.multiply_segment_vector(5);
    static_assert(std::is_same_v<decltype(result), segment_vector>);
}
TEST(multiply_segment_vector, CorrectOutPut){
    segment_vector sv({2,2,2}, {1,1,1});
    segment_vector result = sv.multiply_segment_vector(3);

    EXPECT_EQ(sv.p1.x, result.p1.x);
    EXPECT_EQ(sv.p1.y, result.p1.y);
    EXPECT_EQ(sv.p1.z, result.p1.z);

    EXPECT_EQ(result.p2.x, -1);
    EXPECT_EQ(result.p2.y, -1);
    EXPECT_EQ(result.p2.z, -1);
}


TEST(directional_vector, Consturctor){
    directional_vector dv1 = directional_vector(point3D(4,3,0));
    ASSERT_EQ(dv1.x, 0.8f);
    ASSERT_EQ(dv1.y, 0.6f);
    ASSERT_EQ(dv1.z, 0.0f);

    directional_vector dv2 = directional_vector();
    ASSERT_EQ(dv2.x, 0.0f);
    ASSERT_EQ(dv2.y, 0.0f);
    ASSERT_EQ(dv2.z, 0.0f);
}

TEST(multiply_directional_vector, CorrectType){
    directional_vector dv = directional_vector(point3D(4,3,0));
    auto result = dv.multiply_directional_vector(5);
    static_assert(std::is_same_v<decltype(result), segment_vector>);
}

TEST(multiply_directional_vector, CorrectOutPut){
    directional_vector dv = directional_vector(point3D(4,3,0));
    auto sv = dv.multiply_directional_vector(5);

    EXPECT_EQ(sv.p1.x, 0.0f);
    EXPECT_EQ(sv.p1.y, 0.0f);
    EXPECT_EQ(sv.p1.z, 0.0f);

    EXPECT_EQ(sv.p2.x, 4.0f);
    EXPECT_EQ(sv.p2.y, 3.0f);
    EXPECT_EQ(sv.p2.z, 0.0f);
}

TEST(cross_product, CorrectType){
    auto dv1 = directional_vector(point3D(4,3,0));
    auto dv2 = directional_vector(point3D(0,3,4));
    auto result = cross_product(dv1, dv2);
    static_assert(std::is_same_v<decltype(result), segment_vector>);
}

TEST(cross_product, CorrectOutPut){
    auto dv1 = directional_vector(point3D(1,0,0));
    auto dv2 = directional_vector(point3D(0,1,0));
    auto sv = cross_product(dv1, dv2);

    EXPECT_EQ(sv.p1.x, 0.0f);
    EXPECT_EQ(sv.p1.y, 0.0f);
    EXPECT_EQ(sv.p1.z, 0.0f);

    EXPECT_EQ(sv.p2.x, 0.0f);
    EXPECT_EQ(sv.p2.y, 0.0f);
    EXPECT_EQ(sv.p2.z, 1.0f);
}


TEST(cross_product, OrthogonalVectors) {
    directional_vector a({1,0,0});
    directional_vector b({0,1,0});
    auto result = cross_product(a, b); 

    EXPECT_NEAR(result.p2.x, 0.0f, 1e-5);
    EXPECT_NEAR(result.p2.y, 0.0f, 1e-5);
    EXPECT_NEAR(result.p2.z, 1.0f, 1e-5); 
}

TEST(cross_product, ParallelVectors) {
    directional_vector a({1,0,0});
    directional_vector b({2,0,0});
    auto result = cross_product(a, b);

    EXPECT_NEAR(result.p2.x, 0.0f, 1e-5);
    EXPECT_NEAR(result.p2.y, 0.0f, 1e-5);
    EXPECT_NEAR(result.p2.z, 0.0f, 1e-5);
}

TEST(cross_product, AntiParallelVectors) {
    directional_vector a({1,0,0});
    directional_vector b({-1,0,0});
    auto result = cross_product(a, b);

    EXPECT_NEAR(result.p2.x, 0.0f, 1e-5);
    EXPECT_NEAR(result.p2.y, 0.0f, 1e-5);
    EXPECT_NEAR(result.p2.z, 0.0f, 1e-5);
}

TEST(cross_product, RandomVectors) {
    directional_vector a({1,2,3});
    directional_vector b({4,5,6});
    auto result = cross_product(a, b).normalize_vector();

    EXPECT_NEAR(result.x, -0.408248f, 1e-5);
    EXPECT_NEAR(result.y, 0.816497f, 1e-5);
    EXPECT_NEAR(result.z, -0.408248f, 1e-5);
}

TEST(cross_product, UnitVectors) {
    directional_vector a({0,0,1});
    directional_vector b({0,1,0});
    auto result = cross_product(a, b);

    EXPECT_NEAR(result.p2.x, -1.0f, 1e-5);
    EXPECT_NEAR(result.p2.y, 0.0f, 1e-5);
    EXPECT_NEAR(result.p2.z, 0.0f, 1e-5);
}


TEST(magnitude_of_segment_vector, CorrectOutPut){
    segment_vector sv({2,3,6}, {5,7,6});
    float magnitude = magnitude_of_segment_vector(sv);
    EXPECT_EQ(magnitude, 5.0f);
}

TEST(create_viewport_vectors, CorrectMath) {
    directional_vector v(point3D(1, 0, 0));
    
    auto viewport_vectors = create_viewport_vectors(v);
    directional_vector t1 = viewport_vectors[0];
    directional_vector t2 = viewport_vectors[1];

    // Check they are perpendicular to original vector
    EXPECT_NEAR(dot_product(v, t1), 0.0f, 1e-5);
    EXPECT_NEAR(dot_product(v, t2), 0.0f, 1e-5);

    // Check they are perpendicular to each other
    EXPECT_NEAR(dot_product(t1, t2), 0.0f, 1e-5);
}




TEST(create_viewport_vectors, CorrectOutPut){
    directional_vector dv({1,0,0});
    auto result = create_viewport_vectors(dv);
    EXPECT_EQ(result[0].x, 0);
    EXPECT_EQ(result[0].y, 0);
    EXPECT_EQ(result[0].z, -1);
    EXPECT_EQ(result[1].x, 0);
    EXPECT_EQ(result[1].y, 1);
    EXPECT_EQ(result[1].z, 0);
}

TEST(operators, plus){
    point3D p({2,3,4});
    directional_vector dv({1,0,0});
    auto result = p + dv;
    EXPECT_EQ(result.x, 3);
    EXPECT_EQ(result.y, 3);
    EXPECT_EQ(result.z, 4);
}

TEST(operators, minus){
    point3D p({2,3,4});
    directional_vector dv({1,0,0});
    auto result = p - dv;
    EXPECT_EQ(result.x, 1);
    EXPECT_EQ(result.y, 3);
    EXPECT_EQ(result.z, 4);
}

TEST(operators, division){
    directional_vector dv({1,0,0});
    auto result = dv / 5;
    EXPECT_EQ(result.x, 0.2f);
    EXPECT_EQ(result.y, 0);
    EXPECT_EQ(result.z, 0);
}

TEST(operators, multiply){
    point3D p({2,3,4});
    auto result = p * 5;
    EXPECT_EQ(result.x, 10);
    EXPECT_EQ(result.y, 15);
    EXPECT_EQ(result.z, 20);  
}