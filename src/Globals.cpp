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