#ifndef GLOBAL_H
#define GLOBAL_H
#include "Geometry.h"
const directional_vector X_AXIS = directional_vector(point3D(1, 0, 0));
const directional_vector Y_AXIS = directional_vector(point3D(0, 1, 0));
const directional_vector Z_AXIS = directional_vector(point3D(0, 0, 1));
float degree_to_radiant(float degree);
float tone(float x);
#endif