#include "Surface.h"
#include "Color.h"

Surface::Surface(Color val_color, float val_shinness, float val_reflectivity){
    color = val_color;
    shinness = val_shinness;
    reflectivity = val_reflectivity;
}
Surface::Surface(){}

Color Surface::Surface_color(){
    return color;
}
float Surface::Shinness(){
    return shinness;
}
float Surface::Reflectivity(){
    return reflectivity;
}